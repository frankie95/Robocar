
#include <avr/pgmspace.h>
#include "Timer.h"
#include "robocar_ll.h"
#include "LCD.h"
#include "Wheel.h"
#include "ADC.h"
#include "eeprom.h"

#define S1 0b00000001
#define S2 0b01000000
#define S3 0b00000100
#define S4 0b00000010
#define ADCC 0b10111000
#define PERIOD 40

void S1Changed(char);	// handler functions
void S2Changed(char);
void S3Changed(char);
void S4Changed(char);

static unsigned int mod10(unsigned int *p) {
	unsigned int i = *p / 10;
	unsigned int j = *p - i * 10;
	*p = i;
	return j;
}
static void itos(unsigned int i, char *b, unsigned char digit) {	// integer to string
	b[digit-1] = mod10(&i) + '0';
	for (int k = digit-2; k >= 0; k--) b[k] = i ? mod10(&i) + '0' : ' ';
	if (i) b[0] = '*';
}
static void ctob(char c, char *b) {	// char to bit pattern
	for (int i = 7; i >= 0; i--)
	b[i] = c & _BV(7-i) ? '*' : '.';
}

static class Buttons : Timer {
public:
	int servoNumber=0;
	char bf1[17];
	char bf2[17];
    Buttons(void) {
		kP = 11;
		kI = 56;
		kD = 60;
		// 13, 63, 56,speed 100
		// 19, 63, 63 ,speed = 160
		// 24
		Wheel::setP(kP);
		Wheel::setI(kI);
		Wheel::setD(kD);
		Wheel::setSpeed(160);
		PIDselecter = 0;
		troggleState = false;
		for (int i = 0; i < 16; i++) bf1[i] = bf2[i] = ' ';
		speed = 5;
		
        count = PERIOD;
        state = LL::read541(LL::BUTTONS, 1);
        timer::add(*this);		//timer3 has to be already instantiated
		EEPROM::retore();
    }
private:
    char state;
	bool troggleState;
	unsigned char speed;
	int kP, kI, kD;
	int PIDselecter;
	int vrValue;
	int servo[4];
    void timeout(void) {

		
		//char str2[4] = {0};
		//str2[0] = 'x';
		//str2[1] = 'y';
		//str2[2] = '\0';
		//str2[3] = '\0';
		
		
        count = PERIOD;		//restore count
        char b = LL::read541(LL::BUTTONS, 1);
        char c = b ^ state;
		if ((ADCC&b)==ADCC)
		{		LCD::print(LCD::LINE2,Adc::getValue());
			Servo::set(5529+ADCH*78,servoNumber);
			servo[servoNumber]=5529+ADCH*78;
			}//else{ADCSRA = (0 << ADEN);}
		
        if (c) {
            state = b;
            if (S1 & c) S1Changed(S1 & b);
            if (S2 & c) S2Changed(S2 & b);
            if (S3 & c) S3Changed(S3 & b);
            if (S4 & c) S4Changed(S4 & b);
        }
    }


    void S1Changed(char c) {
        if (c) {
			if(troggleState == false){
				Wheel::setP(kP);
				Wheel::setI(kI);
				Wheel::setD(kD);
				Wheel::move(Wheel::BACKWARD);
			} else {
				Wheel::move(Wheel::STOP);
			}
			troggleState = !troggleState;
        }
    }



    void S2Changed(char c) {
        if (c) {
		EEPROM::retore();
		int* servoValue=EEPROM::getServo();
		for (int i=0;i<4;i++)
		{Servo::set(*(servoValue+i),i);
		}
			
        }
    }

    void S3Changed(char c) {
        if (c) {
			
			servoNumber++;
			if (servoNumber==4)
			{servoNumber=0;
			}
        }
    }

    void S4Changed(char c) {
        if (c) {
			int* servoValue=EEPROM::getServo();
			for (int i=0;i<4;i++)
			{*(servoValue+i)=servo[i];
			}
			EEPROM::save();
        }
    }

} buttons;

namespace Button{
	char * getBF1(){
		return buttons.bf1;
	}
	char * getBF2(){
		return buttons.bf2;
	}
	//int getServo(){return buttons.servoNumber;}
}