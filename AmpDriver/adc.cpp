/* 
* adc.cpp
*
* Created: 13.03.2020 19:21:40
* Author: Maciek
* http://mysinski.wieik.pk.edu.pl/MPUandMCU/ADC%20in%20ATMEGA32.pdf
*/

#include <avr/io.h>
#include "adc.h"

// default constructor
adc::adc()
{
} //adc

// default destructor
adc::~adc()
{
} //~adc


void adc::initialise(){
	
	//register SFIOR
	
	//ACSR 
	//Enable power to ADC - bit 7
	ACSR = (1<<ACD) | (1<<ACBG) | (0<<ACO) | (1<<ACI) | (1<<ACIE) | (1<<ACIC);
	TIMSK1 |= (1<<ICIE1);
	
	//prescale the clock - between 50kHz and 200kHz
	ADCSRA |= (1<<ADPS0) | (1<<ADPS1) |(1<<ADPS2); //divide by 128 (clock: i/e/ 8Mhz/128 -> 62500Hz 
	
	ADMUX |= (1<<REFS0) | (1<<REFS1); // Internal Vref 2,56 with external capacitor
	ADMUX |= (1<<ADLAR); //left adjust result
	
	
	ADCSRB |= (0<<ADTS2) | (0<<ADTS1) | (0<<ADTS0); //Free running mode for ADC
	
	//Select the ADC input
	//MUX4..0
	//ADMUX |= (1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0); //00000 - ADC0 , 00111 - ADC7 (single ended)
	
}
void adc::sleepnoisereduction(){ //MCUCR - register SM2/SM1/SM0 - 0/0/1

}

void adc::powerconsumption(){ //low, med, high
	
}

void adc::run_conversion(float vref = 2.5){
	
	ADCSRA |= (1<<ADEN);
	
	ADCSRA |= (1<<ADSC); //start conversion
	
	ADCSRA |= (1<<ADIE); //Enable ADC interrupt
	
	//ADIF is high after conversion
	//values are stored in ADCL and ADCH
	int value = (ADCH << 8) | ADCL;
	
	float voltage = 0;
	//Calculate the value in compare to Vref
	voltage = (value * 1024) / vref;
	
	
}


void adc::set_adc_channel(char adc_no){
	
	//ADMUX |= (1<<MUX4) | (1<<MUX3) | (1<<MUX2) | (1<<MUX1) | (1<<MUX0);
	ADMUX &= (1 << REFS1) | (1 << REFS0) | (0 << ADLAR) | (0<<MUX4) | (0<<MUX3) | (0<<MUX2) | (0<<MUX1) | (0<<MUX0); //reset register
	ADMUX |= adc_no; // sets the bits MUX4..0 - values from 0 to 7 (single ended)
		
}