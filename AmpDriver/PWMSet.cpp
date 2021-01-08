/* 
* PWMSet.cpp
*
* Created: 01.01.2021 20:43:12
* Author: maciek
*/


#include <avr/interrupt.h>
#include "IDevice.h"
#include "PWMSet.h"

// default constructor
// class will keep 4 output separately configured
// by % of adjustment 

volatile long pwm_clock;
volatile long pwm_test;
/*
ISR(TIMER2_COMPB_vect){
	
	pwm_clock++;
	if(pwm_clock > (100* STEP_NUMBERS))
		pwm_clock = 0;
}
*/
ISR(TIMER2_COMPA_vect){
	
	//Function executed 6,25kHz
	//and having 16 gradients/steps 
	//the initial frequency will be 
	//6,25kHz / 16 = 400Hz - minimum for LED dimming
	//with 8MHz core clock
	
	pwm_clock++;
	
	if(pwm_clock > STEP_NUMBERS)
		pwm_clock = 0;
		
	PWMSet::getpwm()->callPWM(pwm_clock);
	
}

PWMSet* PWMSet::pwmset;

PWMSet::PWMSet(int_fast8_t channels)
{
	pwm_count = 0;
	pwmset = this;
	pwm_clock = 0;
	pwm_test  = 0;
	//Set the registers
	
	//Set the I/O of the PWM output - ports D4->D7
	//PORTD |= 
	//DDRD  |= (1<<DDD7)|(1<<DDD6)|(1<<DDD5)|(1<<DDD4);
	 
	//OCR0A = 128;
	// set PWM for 50% duty cycle 
	
	//TCCR0A |= (1 << COM0A1);
	// set none-inverting mode

	//TCCR0A |= (1 << WGM01) | (1 << WGM00);
	// set fast PWM Mode
	 
	//TCCR0A |= (1<<COM0A1) || (1<<COM0A0);
	//TCCR0B |= (1 << CS01);
	// set prescaler to 8 and starts PWM
	
	cli();
	TCCR2A |= (1<<WGM21);
	TCCR2B |= (1<<CS22) | (0<<CS21) | (1<<CS20); //prescaller 1/128 (8MHz -> 62,5kHz)
	TCNT2 = 0x00; //start point
	OCR2A = 0x11; //used to generate OC2B pin output;if selected - generate impuls every 10th time - 6,25kHz
	//ASSR = .... - used for external clock
	TIFR2 |= (1<<OCF2A); 
	TIMSK2 |= (1 << OCIE2A);//to select the interrupt mask register (vector) we are selecting ->COMPA is selected
	/*
	TCNT2 = 0x00; //timer/counter register
	TIMSK2 |=     //interrupt mask register
	OCR2A = 0x3E;   //register to compare
	TCCR2A |= (1 << WGM21); //Wlaczenie trybu CTC (Clear on compare match)
	TIMSK2 |= (1 << OCIE2A); //Wystapienie przerwania gdy zliczy do podanej wartosci
	TCCR2B |= (1 << CS21); //Ustawienie dzielnika na 64, po czym start
	*/
	//System shall operate on 16 bit timer to enable proper resolution for PWM
	//The frequency has to be 2^n for n bit resolution
	// for 256 bit resolution f=
	
	
	
	//////////////////////////Init channels output pins
	
	//0 - set the bit clear; 1 - set the pin high
	
	MCUCR ^= (-0 ^ MCUCR) & (1UL << PUD); //PUD = 0 ;  -- set global flag Pull UP to on - set to 0
	
	/*
	PWM_REG_B  ^= (-1 ^ PWM_REG_B)  & (1UL << PWM_O2);   // set the direction of the port PWM_O2 to output (set pin to 1 in register DDRx)
	PWM_PORT_B ^= (-0 ^ PWM_PORT_B) & (1UL << PWM_O2); // output port doesn't need a pull-up and has to be set to 0
	
	PWM_REG_B  ^= (-1 ^ PWM_REG_B) & (1UL << PWM_O3);
	PWM_PORT_B ^= (-0 ^ PWM_PORT_B) & (1UL << PWM_O3);
	
	PWM_REG_C  ^= (-1 ^ PWM_REG_C) & (1UL << PWM_O1);
	PWM_PORT_C ^= (-0 ^ PWM_PORT_C) & (1UL << PWM_O1);
	*/
	/////////////////////////////////////////////////////
	//////////Create PWM channels
	
	/*
	for (int_fast8_t count = 0; count < PWM_CHANNELS; count ++)
	{
		//pwm_map.insert(new 
		pwm_channels[count].set_output(&PORTB, PINC6);
	}
	*/
	sei();
		
} //PWMSet

// default destructor
PWMSet::~PWMSet()
{
} //~PWMSet


PWMSet * PWMSet::getpwm()
{
	return pwmset;	
}

void PWMSet::callPWM(int_fast8_t call_no)
{
	//pwm_test = call_no;
	//We will call each PWM_channel here
	//pwm_channels[0]->call_up(call_no);
	for (char i=0; i < pwm_count; i++)
	{
		pwm_channels[i].call_up(call_no);
	}
	
}

void PWMSet::addchannel(volatile uint8_t * pin_register, volatile uint8_t *port, uint8_t mask)
{
	pwm_channels[pwm_count++].set_output(pin_register, port, mask);
}


void PWMSet::setPWM(int_fast8_t channel, uint8_t volume)
{
	pwm_channels[channel].set_step(volume);
}

void PWMSet::setValue(int_fast8_t new_value, uint8_t id)
{
	pwm_channels[id].set_step(new_value);
}

int_fast8_t PWMSet::getValue()
{
	
	return 0;
}



PWM_Channel::PWM_Channel(volatile uint8_t *port, uint8_t mask)
{
	
	state = false;
	value = 0;
	channel_port = port;
	channel_mask = mask;

}



PWM_Channel::PWM_Channel()
{
	
	state = false;
	value = 0;
	
}

/*
	based on number od steps
	and % of PWM we need to calcualate the value when it shall be triggered
*/
void PWM_Channel::set_step(const int_fast8_t & vol)
{
	value = (vol*STEP_NUMBERS)/100;
}

void PWM_Channel::call_up(uint8_t call_no)
{
	//we need to check when the change pin up and down
	//the change shall be done only if pwm_val < 100%
	//if pwm_val = 0% -> pin down all time
	//when call_no - 0 -> pin up
	//when call_no = value -> pin down
	
	//pwm_test = call_no;
	
	if(value > 0 && value < STEP_NUMBERS)
	{
		
		if(call_no == 0)
		{
			//pin up
			*channel_port |= (1 << channel_mask); // Pin n goes high
		}
		if(call_no == value)
		{
			//pin down
			*channel_port &= ~(1 << channel_mask); // Pin n goes low
		}
	}else
	{
		(value==0)?(*channel_port &= ~(1 << channel_mask)):(*channel_port |= (1 << channel_mask));
	}
	
}

void PWM_Channel::set_output(volatile uint8_t * pin_register, volatile uint8_t *port, uint8_t mask)
{
	channel_register = pin_register;
	channel_port	 = port;
	channel_mask	 = mask;
	
	// Set the channel as output
	*channel_register  ^= (-1 ^ *channel_register) & (1UL << mask);
	*port ^= (-0 ^ *port) & (1UL << mask);
}

