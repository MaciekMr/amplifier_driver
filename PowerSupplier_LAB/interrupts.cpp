/*
 * CPPFile1.cpp
 *
 * Created: 29.01.2022 14:55:12
 *  Author: macie
 */ 

#include <stdarg.h>
#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "configuration.h"
#include <util/delay.h>
#include "int_fasade.h"
#include "states.h"
#include "lcd.h"
#include "interrupts.h"


uint_fast16_t data = 0;
uint_fast8_t  sec = 0;
uint_fast16_t seconds = 0;

object_list  obj_list;

void interrupt_configure()
{
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
		state_main state;
		state.id = VOLTAGE;
		lcd::get_object()->change_state(state);
	}
	
	externall_call(); //call each 100ms
	
}

void externall_call()
{
	
	((object_list*)object_list::get_object())->call_int();
	//pointer->call_int();
}


object_list* object_list::pointer;


object_list::object_list()
{
	pointer = this;
	object_counter = 0;
}

void object_list::add_object(void* pointer)
{
	objects[object_counter] = pointer;
	object_counter++;
}


void object_list::call_int()
{
	
	//data++;
	
	//System has to call all object with the same method
	//lcd::get_object()->update(0);
	
	for(int i = 0; i < object_counter; i++)
	{
		((fasade*)objects[i])->update(0);		
	}
	
}


object_list* object_list::get_object()
{
	return pointer;
}