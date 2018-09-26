#include <avr/interrupt.h>
#include "Wheel.h"
#include "Task.h"
#include "robocar_ll.h"
#include <stdlib.h>
#include "Button.h"
#include "LineTrack.h"
#include "LCD.h"
#define R_OCR OCR2B
#define L_OCR OCR2A
#define L_COUNTER TCNT0
#define R_COUNTER TCNT1L

static unsigned int mod10(unsigned int *p) {
	unsigned int i = *p / 10;
	unsigned int j = *p - i * 10;
	*p = i;
	return j;
}
static void uitos(unsigned int i, char *b, unsigned char digit) {	// unsigned integer to string
	b[digit-1] = mod10(&i) + '0';
	for (int k = digit-2; k >= 0; k--) b[k] = i ? mod10(&i) + '0' : ' ';
	if (i) b[0] = '*';
}
static void itos(signed int i, char *b, unsigned char digit) {	// signed integer to string
	if(i<0){
		i = -i;
		b[0] = '-';
	} else {
		b[0] = '+';
	}
	uitos(i, &b[1], digit-1);
}
static void ctob(char c, char *b) {	// char to bit pattern
	for (int i = 7; i >= 0; i--)
	b[i] = c & _BV(7-i) ? '*' : '.';
}

namespace {
    enum _motor {B_DIR = 1, A_DIR = 2, FREE = 4, ON = 128};
    enum _TCCR2A {	A_CON = 0b10000011, B_CON = 0b00100011, DISCON = 0b11};
	
	class PIDcontrol {
	public:
		PIDcontrol(void){
			iTerm = lastInput = 0;	
		}
		int iTerm, lastInput;

		int process(int input, unsigned char kP, unsigned char kI, unsigned char kD, int iTermLimit){
			iTerm += input;
			iTerm = iTerm > iTermLimit ? iTermLimit : iTerm;
			iTerm = iTerm < -iTermLimit ? -iTermLimit : iTerm;
			int dTerm = input - lastInput;
			lastInput = input;
			return kP*input + iTerm/kI + kD*dTerm;
		}
	};
	
    class Timer2: public Task  {
        public:
			unsigned char L_speed_limit, R_speed_limit;
            unsigned char L_isr, R_isr, L_last, R_last, L_speed, R_speed;
            unsigned int L_count, R_count,speed;
            Timer2(void) {
                DDRD |= _BV(7);
                DDRD |= _BV(6);
                TCCR2A = DISCON;
                TCCR2B = 0b111;
                TCCR0B = TCCR1B = 7;
                ASSR &= ~_BV(AS2);
                move(Wheel::STOP);
                L_OCR = R_OCR = 128;
				choosesensor=0;
                TIMSK2 |= _BV(TOIE2);	// enable overflow interrupt
				speed=85;
				trackspeed = 5;
				/*kP = 8;
				kI = 20;
				kD = 10;*/
            }
            void move(unsigned char command) {
                if (command == Wheel::STOP) {
                    TCCR2A = DISCON;
                    LL::backMotorControl(ON);
                } else {
                    LL::backMotorControl((command & 0b11) | FREE | ON);
                    TCCR2A = (command & 0b11110000) | 0b11;
                }
            }
			
			int trackspeed;
			PIDcontrol speedPID, counterPID, steerPID;
			int kP, kI, kD,choosesensor;
			unsigned char midSensor,leftSensor;
			void task(void){
				
				//
				//-------------------------------------------------
				char *bf1 = Button::getBF1();
				char *bf2 = Button::getBF2();
				int L_output, R_output;
				
				midSensor = LL::read541(LL::FRONT, 30);
					
				
				
				int steerError = displacement(midSensor) - 8; // -7 to 7 
				
				leftSensor=LL::read541(LL::BACK, 30);
				char *sensor_print=new char;
				*(sensor_print+8)='\0';
				char temp=mirror(leftSensor);
				for (int i = 0; i < 8; ++i) {
					*(sensor_print+i)=((temp >> i) & 1)==1?'1':'0';
				}
				
				//itoa(pos[(int)sensor_value],sensor_print+8,10);
				LCD::print(LCD::LINE1, sensor_print);
				
				//	-7	: too right	-> turn left
				//	 7	: too left	-> turn right
				int steerOutput = steerPID.process(steerError, kP, kI, kD, 50*kI);
				ctob(mirror(midSensor), bf1);
				itos(steerError, &bf1[9], 2);
				itos(steerOutput, &bf1[11], 5);
				L_output = speed + steerOutput;
				R_output = speed - steerOutput;

				L_output = L_output > 255 ? 255 : L_output;
				L_output = L_output < 0 ? 0 : L_output;
				R_output = R_output > 255 ? 255 : R_output;
				R_output = R_output < 0 ? 0 : R_output;
				
				L_OCR = L_output;
				R_OCR = R_output;
			}

    }	timer2;
	
		 unsigned char L_isr, R_isr, L_last, R_last, L_speed, R_speed;
		 unsigned int L_count, R_count;
		 class UsrCountTask :public Task{
			 public:
			  char a[4];
			 void set(unsigned int count){
				 
				 firstEntry=true;
				 this->count=count;		 		 
			 }
			 bool firstEntry;
			 unsigned int count;
			 void task(void){			 
				 if(firstEntry){
					 L_count=R_count=0;
					 L_last=TCNT0;
					 R_last=TCNT1L;
					 firstEntry=false;
					 
					 
				 }
				
				 		a[3]='\0';
				 		
				 		if (count<10)
				 		{*(a)='0';
					 		*(a+1)='0';
					 		itoa(ADCH,a+2,10);
					 		}else if(count<100){
					 		*(a)='0';
					 		itoa(ADCH,a+1,10);
					 		}else{
				 		itoa(ADCH,a,10);}
				 		LCD::print(LCD::LINE1, a);
				 if(L_count+R_count+TCNT0+TCNT1L-L_last-R_last<count){
				
				 kerAppend(*this);
				 
				 }
				 else{
					 Wheel::move(Wheel::STOP);
					 
				 }
			 }

		 } usrCountTask;	
}

ISR(TIMER2_OVF_vect){
	L_isr = TCNT0;
	R_isr = TCNT1L;
	//L_COUNTER = 0;
	//R_COUNTER = 0;
	isrAppend(timer2);
}


namespace Wheel {
	
	void set(int speed){
		timer2.speed=speed;
	}
	char getSensor(){return timer2.leftSensor;}
	
	
	void setSpeed( int speed){
		timer2.trackspeed = speed;
	}
	
    void move(enum _command c) {
        timer2.move((unsigned char)c);
    }

	unsigned char getL_speed(){
		return timer2.L_speed;
	}
	
	unsigned char getR_speed(){
		return timer2.R_speed;
	}
	
	void setP(int P){	timer2.kP = P;	}
	void setI(int I){	timer2.kI = I;	}
	void setD(int D){	timer2.kD = D;	}
	void usrCount(unsigned int step){
		usrCountTask.set(step);
		usrCall(usrCountTask);		
	}
	
	void setPID(int p,int i,int d){
		setP(p);
		setI(i);
		setD(d);
	}
	
	
	
}
