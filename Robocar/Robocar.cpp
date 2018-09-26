#include <avr/pgmspace.h>
#include "LCD.h"
#include "Task.h"
#include "Timer.h"
#include "Wheel.h"
#include <avr/io.h>
#include "robocar_ll.h"
#define R_OCR OCR2B
#define L_OCR OCR2A

void test(){
	
	Servo::set(Servo::OPEN,0);
	Servo::set(Servo::UP1,2);
	Servo::set(Servo::UP2,3);
	Servo::delay100ms(10);
	Servo::set(Servo::RIGHT,1);
	Servo::slowclose();
	
}


static class maintask : public Task{
	public:
	maintask(void){
		stop=false;
	}
	private:
	bool stop;
	void task(void){
		if(((Wheel::getSensor())&0b1)!=0)
		{		DDRA|=_BV(2);
				PORTA|=_BV(2);
				Wheel::move(Wheel::STOP);
				stop=true;
		}else
		{	
				kerAppend(*this);
		}
	}
}usrTask;

int main(void) {
	
 	Servo::setInitialise();
	 Servo::delay100ms(10);
 	usrCall(usrTask);
	/*Wheel::move(Wheel::BACKWARD);
	Servo::delay100ms(10);
	usrCall(usrTask1);
	Wheel::move(Wheel::STOP);
 	test();
*/
/*	Wheel::move(Wheel::BACKWARD);
 	Servo::delay100ms(10);
	usrCall(usrTask1);
*/

/*	Servo::delay100ms(10);

	Wheel::set(70);
	Wheel::move(Wheel::BTURNRIGHT);
	Servo::delay100ms(10);
	Wheel::move(Wheel::BACKWARD);
	Servo::delay100ms(9);
	Wheel::move(Wheel::STOP);
	Servo::GG();	*/	
	//usrCall(usrTask2);
	
	while(1) {
		

		
	}
}

