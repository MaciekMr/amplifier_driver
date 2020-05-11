/*
 * INTERRUPTS.h
 *
 * Created: 17.02.2019 21:01:22
 *  Author: macie
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

/*

TIMSK0 - set the OCIEE0A - enable interrupt on compare 
TIFR0 - OCF0A - compare timer 0 with A
OCR0A - set the frequency of timer

Disable -> enable interrupts
sreg = SREG
_CLI();
SREG = sreg;




*/


//ISR(TIMER0_COMPA_vect);

ISR(TIMER1_COMPA_vect);

void timer_initialise();

class timer{
	
	protected:
	
	public:
	
		timer();
		
		void interrupt();
		
	static void timer_interrupt(void *);
	
	};



#endif /* INTERRUPTS_H_ */