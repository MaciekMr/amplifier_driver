/*
 * timer.h
 *
 * Created: 24.01.2019 22:53:17
 *  Author: macie
 */ 


#include "port.h"

#ifndef TIMER_H_
#define TIMER_H_

//SREG register to enable global interrupts (bit 7)

// GIMSK - not set for timer interrupt

// TIMSK - bit 6 is set the OCIE1A interrupt, Overflow interrupt can be set

//TIFR - bits 6 and 5 are set when OCIE1(A|B) is happened

//The timer can be prescalled  http://ww1.microchip.com/downloads/en/DeviceDoc/doc1477.pdf

//TCCR0 -

//TCNT0

//TCCR1A

//TCCR1B

//TCNT1

//OCR1A

//OCR1B

//OCR1C


//ISR(TIMER1_CMPA_vect)  to serve functionfor interrupt

struct registers{
	
	uc GIMSK_REG;
	uc TIMSK_REG;
	uc TIFR_REG;
	uc TCCR0_REG;
	uc TCNT0_REG;
	uc TCCR1A_REG;
	uc TCCR1B_REG;
	uc TCNT1_REG;
	uc OCR1A_REG;
	uc OCR1B_REG;
	uc OCR1C_REG;
	
	};


class timer{
	
	private:
	
		
	
	
	
	
	};


#endif /* TIMER_H_ */