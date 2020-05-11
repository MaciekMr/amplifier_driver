/*
 * interrupts.cpp
 *
 * Created: 18.02.2019 23:24:16
 *  Author: maciek
 * http://www.8bit-era.cz/arduino-timer-interrupts-calculator.html
 */ 

#include <avr/interrupt.h>
#include "interrupts.h"

volatile long sec = 0;

static uint16_t i = 0;

volatile long seconds = 0;


ISR(TIMER1_COMPA_vect){
	
	/*if(++i == 1)  // combined the i++ into this line
	{
		sec++;      // sec will need to be volatile
		// and you should handle overflow or use
		// a uint32_t to get 136 years before overflow
		i = 0;      // if you don't reset i, you'll only get 1 sec!
		
		if(sec > 7){ //prescaler 8MHz/1024 -> 7812,5 Hz
			seconds++;
			sec = 0;
		}
	}*/
	
	//sec = 0,1 second
	//seconds = 1 seconds
	
	if(++sec == 10){
		
		++seconds;
		sec = 0;
	}
	
}

/*
ISR(TIMER0_COMPB_vect)
{
	
	if(++i == 4000)  // combined the i++ into this line
	{
		sec++;      // sec will need to be volatile
		// and you should handle overflow or use
		// a uint32_t to get 136 years before overflow
		i = 0;      // if you don't reset i, you'll only get 1 sec!
		
		if(sec> 1024)
		sec = 0;
	}
}*/

void timer_initialise(){
	
	SREG   |= (1<<7); //Enable interrupts 
	
	/*
	TCCR0B |= (1<<CS02)||(0<<CS01)||(1<<CS00);
	TCNT0  |= 0xFF;
	OCR0B   = 250-1;
	TIMSK0 |= (1<<OCIE0B);// ||(1<<TOIE0);
	TIFR0  |= (1<<OCF0B);//||(1<<TOV0);
	*/
	
	//Set the TIMER1 - 16bits timer
	
	TCCR1A  = 0x00;
	TCNT1   = 0x00;
	TCCR1B |= (1<<WGM12)|(1 << CS12)|(0 << CS11)|(0 << CS10); //Mode CTC, PreSCALER = 256
	OCR1A   = 3125; //Overflow, when timer triggers the interrupt (every 0,1 sec)
	TIFR1  |= (1<<OCF1A);
	TIMSK1 |= (1<<OCIE1A);
	
	
}

timer::timer(){
	
	/* 
	  compares TCNT0 with OCR0A - set the flag OCF0A
	
	  TCCR0B -> CS02 CS01 CS00 -> prescaller 101 = 1024/100 ->256
	  
	  OCR0A - value to compare  8 bits 
	  
	  TIMSK0 - OCIE0A - enable interrupt on compare timer 0 output A
	  
	  TIFR0 - OCF0A - compare bit,  TOV0 - overflow bit
	  
	*/
	
}

void timer::interrupt(){
	
}

 void timer::timer_interrupt(void * _obj){
	
	reinterpret_cast<timer *>(_obj)->interrupt();
}