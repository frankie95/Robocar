/*
 * EEPROM.cpp
 *
 * Created: 3/30/2016 8:33:42 PM
 *  Author: Student
 */ 


#include <avr/interrupt.h>
#include "Task.h"
#include "eeprom.h"

struct EEDATA {
	int p,i,d;
	int servo[4];
}eedata;


namespace{
	class EEProm : public Task{
	public:
		EEProm(){restore();}
		bool save(){
			if(EECR & _BV(EEPE))
			return false;
			ptr=(char*)&eedata;
			count=sizeof(eedata);
			EEAR=0xfff;
			kerAppend(*this);
			return true;
		}	
		bool restore(){
			
			if(EECR&_BV(EEPE))
			return false;
			ptr=(char*)&eedata;
			count=sizeof(eedata);
			EEAR=0xfff;
			while(count--){
				EEAR++;
				EECR|=_BV(EERE);
				*ptr++=EEDR;
			}
			return true;
		}
		private:
		char *ptr;
		unsigned char count;
		void task(){
			if(EECR&_BV(EEPE)) return;
			if(count==0)return;
			EEAR++;
			EEDR=*ptr++;
			EECR|=_BV(EEMPE);
			EECR|=_BV(EEPE);
			count--;
			EECR|=_BV(EERIE);
		}	
	} ee;
}


ISR(EE_READY_vect){
	EECR&=~_BV(EERIE);
	isrAppend(ee);
}

namespace EEPROM {
	
	void savePID(int p,int i,int d){eedata.p=p,eedata.i=i,eedata.d=d;
	save();
	}
		int getP(){return eedata.p;}
		int getI(){return eedata.i;}
		int getD(){return eedata.d;}
		int* getServo(){return eedata.servo;} 
		bool retore(){return ee.restore();}
		bool save(){return ee.save();}
}