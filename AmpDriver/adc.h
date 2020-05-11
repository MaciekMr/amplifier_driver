/* 
* adc.h
*
* Created: 13.03.2020 19:21:40
* Author: Maciek
*/


#ifndef __ADC_H__
#define __ADC_H__


/********************************
* interrupt (vector no. 17)
*
*
*
********************************/

class adc
{
//variables
public:
protected:
private:

//functions
public:
	adc();
	~adc();
	void run_conversion(float);
	void set_adc_channel(char );
protected:
private:
	adc( const adc &c );
	adc& operator=( const adc &c );
	void initialise();
	void sleepnoisereduction(); //MCUCR - register SM2/SM1/SM0 - 0/0/1
	void powerconsumption(); //low, med, high
	
	
}; //adc

#endif //__ADC_H__
