/*
 * R20.cpp
 *
 * Created: 12/2/2016 21:36:20
 *  Author: frank
 */ 
#include <avr/interrupt.h>
#include "robocar_ll.h"
#include "Task.h"
#include "LCD.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "Wheel.h"


static class R20 : public Task
{	public:
	R20(void){
		ADCSRA = (1 << ADEN)| // Enable ADC
		 (1 << ADIE) // Enable ADC interrupt
		| (0b111 << ADPS0); // clk/128
		ADMUX = (0b01 << REFS0) // Voltage Reference Selection: AVcc with external capacitor at AREF pin
		| (1 << ADLAR) // left adjusted
		| (0b0000 << MUX0); // Single Ended Input: ADC0
		ADCSRA |= (1 << ADSC);
		}
	private:
	char a[4];
	void r20_value(unsigned int input){
		
		a[3]='\0';
		
		if (input<10)
		{*(a)='0';
		 *(a+1)='0';
		 itoa(ADCH,a+2,10);
		}else if(input<100){
			*(a)='0';
			itoa(ADCH,a+1,10);
		}else{
			itoa(ADCH,a,10);}
		
		
	}
	void task(void){
		r20_value(ADCH);
	
		//Servo::set(5529+ADCH*65);
		//Wheel::settime((int)ADCL);
		
		LCD::print(LCD::LINE2, a);
		ADCSRA |= (1 << ADSC);

	}
} r20;

ISR(ADC_vect){
	isrAppend(r20);
}