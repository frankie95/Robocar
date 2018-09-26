/*
 * ADC.cpp
 *
 * Created: 2/19/2016 3:30:11 PM
 *  Author: Student
 */ 

#include <avr/interrupt.h>
#include "ADC.h"
#include "Timer.h"
#include "Task.h"
#include <stdio.h>
#include <avr/io.h>
#include <stdlib.h>
#include "LCD.h"

namespace {
	class Test : Timer, public Task {
	public:
	char a[4];
		Test(void) {
			currentChannel = 0;
			start();
		}
		void setChannels(char channels){
			this->channels = channels;
			currentChannel = 0;
		}
		void start(){
			count = 40;
			timer::add(*this);
			//kerAppend(*this);
		}
		int getChannel(char channel){
			return data[channel];
		}
	private:
		char channels;
		
		int data[8], currentChannel;
		void timeout(void){
			count = 40;
			
			//kerAppend(*this);
			ADCSRA = (1 << ADEN) // Enable ADC
			| (1 << ADIE) // Enable ADC interrupt
			| (0b001 << ADPS0); // clk/128
			ADMUX = (0b01 << REFS0) // Voltage Reference Selection: AVcc with external capacitor at AREF pin
			| (1 << ADLAR) // left adjusted
			| (0); // Single Ended Input: ADCx
			ADCSRA |= (1 << ADSC); // Start conversion
		};
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
			
			data[0] = ADCH;
		}
		void setRegister(){
			ADCSRA = (1 << ADEN) // Enable ADC
			| (1 << ADIE) // Enable ADC interrupt
			| (0b001 << ADPS0); // clk/128
			ADMUX = (0b01 << REFS0) // Voltage Reference Selection: AVcc with external capacitor at AREF pin
			| (1 << ADLAR) // left adjusted
			| (currentChannel); // Single Ended Input: ADCx
			ADCSRA |= (1 << ADSC); // Start conversion
		}
	} adcObj;
}


ISR(ADC_vect){
	isrAppend(adcObj);
}


namespace Adc {
	char* getValue(){return adcObj.a;}
	void setChannels(char channels){
		adcObj.setChannels(channels);
	}
	void start(){
		adcObj.start();
	}
	int getChannel(char channel){
		return adcObj.getChannel(channel);
	}
}