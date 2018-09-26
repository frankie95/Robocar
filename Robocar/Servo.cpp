
#include <avr/interrupt.h>
#include "robocar_ll.h"
#include "Task.h"
#include "Wheel.h"
#include <avr/pgmspace.h>
#include "LCD.h"
#include "Task.h"
#include "Timer.h"
#include "Wheel.h"

namespace {

    class Servo: public Task {
    public:
        Servo(void) {
            DDRB |=_BV(7);
            OCR3B=13824;
            TIMSK3|=_BV(OCIE3B);
            channel=width[0]=width[1]=0;
            width[2]=width[3]=0;
            width[4]=width[5]=0;
            width[6]=width[7]=0;
        }

        unsigned int width[8];
        unsigned char channel;
		unsigned int name;
    private:
        void task(void) {
			
            channel++;
            LL::servoSetAddress(channel&=7);
            if(width[channel]) {
                OCR3B=width[channel];
                TCCR3A |=_BV(COM3B1);
            } else {
                OCR3B=13824;
                TCCR3A&=~_BV(COM3B1);
            }

        }

    } servo;
}


namespace {

	class Slowmove: public Task { 
		
		public:
		Slowmove(void) {
			_start=false;
		}
		void set(int channel,int num) {
			this->channel=channel;
			this->num=num;
			_start=true;
			count=0;
			
		}
		unsigned int channel, num,count;
		bool _start;
		private:
		void task(void) {
			count++;
			if (_start)
			{
			if (count==1000)
			{
			
			if (servo.width[channel]<num)
			{servo.width[channel]+=1;
			}
			if (servo.width[channel]>num)
			{servo.width[channel]-=1;
			}
			 
			
			count=0;
			//kerAppend(*this); 
			}
			if (servo.width[channel]=num)
			{_start=false;
			}
			}
		}
		

	 }slowmove;
}






namespace Servo{
	void delay100ms(int n){
		for (int i = 0; i<(n*400); i++)
		delayU(255);
	}
	void setname(int name){servo.name=name;}
	void setInitialise(int val){
		
		servo.width[3]=val;
		servo.width[0]=8000;
		servo.width[1]=MIDDLE;
		servo.width[2]=val-5000;
		delay100ms(10);

		set(0,1);
		set(0,0);
		set(0,2);
		set(0,3);
	}
	void set(enum servo_command a,int name){ servo.width[name]=a;}
	void set(int num,int name){
		servo.width[name]=num;

	}
	void set(int num){
		servo.width[servo.name]=num;
		
	}
	int getwidth(int a){
		return servo.width[a];
	}
	void slowclose(){
		delay100ms(10);
		set(DOWN1,2);
		delay100ms(10);
		set(DOWN2,3);
		delay100ms(10);
		while(servo.width[1]<Right2)
		{	servo.width[1]+=2;
			delayU(255);
		}
		while(servo.width[0]<CLOSE)
		{	servo.width[0]+=2;
			delayU(255);
		}
		
		delay100ms();
		set(UP1,2);
		set(UP2,3);
		delay100ms();
		delay100ms();
		delay100ms();
		set(LEFT,1);
		set(DOWN1,2);
		delay100ms();
		delay100ms();
		set(OPEN,0);
		
		
		
		
		
		
		
		
		
		
		
		
		
		delay100ms();



		
		
	}
	void slowclose1(){
		
		delay100ms(10);
		set(DOWN1,2);
		delay100ms(10);
		set(DOWN2,3);
		delay100ms(10);
		while(servo.width[1]<Right2)
		{	servo.width[1]+=2;
			delayU(255);
		}
		while(servo.width[0]<CLOSE)
		{	servo.width[0]+=2;
			delayU(255);
		}
set(UP1,2);
delay100ms(10);
set(UP2,3);
delay100ms(10);
		set(LEFT,1);
		while(servo.width[2]<DOWN1)
		{	servo.width[2]+=2;
			delayU(255);
		}
		while(servo.width[3]>DOWN2)
		{	servo.width[3]-=2;
			delayU(255);
		}
		
		
	}
	void second(){
		while(servo.width[0]>OPEN)
		{	servo.width[0]-=2;
			delayU(255);
		}	
	}
	
	void GG(){
		
		set(14000,1);
		set(DOWN1,2);
		set(DOWN2,3);
		delay100ms(10);
		set(OPEN,0);
		
		
		
	}
	
	
}


ISR(TIMER3_COMPB_vect) {
    isrAppend(servo);
	// isrAppend(slowmove);
}
