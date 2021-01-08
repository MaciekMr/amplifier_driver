/* 
* PWMSet.h
*
* Created: 01.01.2021 20:43:12
* Author: macie
*/


#ifndef __PWMSET_H__
#define __PWMSET_H__

/*

The PWM frequency for the output can be calculated by the following equation:
f OCnxPWM = fclk_I/O/N*256

The N variable represents the prescale factor (1, 8, 64, 256, or 1024)


*/

#define PWM_CHANNELS 8
#define STEP_NUMBERS 32 //number of steps for pwm 

//PC6 - transistor T1
//PB0 - transistor T2
//PB2
//PB3

#define PWM_REG_B	DDRB
#define PWM_REG_C	DDRC
#define PWM_PORT_B	PORTB
#define PWM_PORT_C	PORTC
#define PWM_PIN_B	PINB
#define PWM_PIN_C	PINC


#define PWM_O1	 PINC6
#define PWM_O2	 PINB0
#define PWM_O3	 PINB4


class PWM_Channel 
{
protected:
	int id;	
	int_least8_t value; //defined step when the state of PWM shall be change i.e. 50% and 16 steps -> 8
	bool state;
	volatile uint8_t *channel_port;
	volatile uint8_t *channel_register;
	uint8_t channel_mask;
private: 
	 //define the pin for PWM
public:
	PWM_Channel(volatile uint8_t *port, uint8_t mask);
	PWM_Channel();
	void set_output(volatile uint8_t *, volatile uint8_t *, uint8_t);
	void set_step(const int_fast8_t &); //this function is called when the % of PWM is changed/reconfigured/ The value has to be between 0 - 100
	void call_up(uint8_t call_no);  //execute this function each time the interrupt from timer is triggered; based on pwm conf it will change the level of output
	
};


class PWMSet
	:public IDevice
{
//variables
public:
protected:
private:
	//std::hash_map<int_fast8_t, *PWM_Channel> pwm_map;
	uint8_t pwm_count;
	static PWMSet * pwmset;
	PWM_Channel pwm_channels[PWM_CHANNELS];
//functions
public:
	PWMSet(int_fast8_t channels);
	~PWMSet();
	void setValue(int_fast8_t new_value, uint8_t id);
	int_fast8_t getValue();
	void updatePWM();
	void setPWM(int_fast8_t channel, uint8_t volume); //will set up the % of PWM for given channel
	void callPWM(int_fast8_t call_no); //method executed by interrupt 
	void addchannel(volatile uint8_t *, volatile uint8_t *, uint8_t);
protected:
private:
	PWMSet( const PWMSet &c );
	PWMSet& operator=( const PWMSet &c );
public:
	static PWMSet * getpwm();
}; //PWMSet

#endif //__PWMSET_H__
