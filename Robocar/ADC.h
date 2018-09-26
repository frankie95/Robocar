/*
 * ADC.h
 *
 * Created: 2/19/2016 4:05:35 PM
 *  Author: Student
 */ 


#ifndef ADC_H_
#define ADC_H_


namespace Adc {
	void setChannels(char channels);
	void start();
	int getChannel(char channel);
	char* getValue();
}


#endif /* ADC_H_ */