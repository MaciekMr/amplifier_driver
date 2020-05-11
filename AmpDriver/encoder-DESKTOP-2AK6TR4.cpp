/*
 * encoder.cpp
 *
 * Created: 20.02.2019 20:12:43
 *  Author: maciek
 */ 

#include "avr/interrupt.h"
#include "port.h"
#include "encoder.h"


using namespace nm_DS1267;


/*******************************
* Idea of mechanical encoder is simple and based on cyclic testing 
* the encoder status, without occupying the interruption of uC.
* The best way is to test outputs of encoder every 10ms and apply the 
* gray code.
*
* 1. Set the 8 bit timer to 10ms
* 2. Use the interrupt function to check encoder
*
***********************************/


volatile long reaction = 0;


ISR(TIMER0_COMPB_vect){
	
	
	if(reaction++ > 1024)
		reaction = 0;
	
}


void set_encoder_timer(){
	
	TCCR0A  = 0x00;
	TCNT0   = 0x00;
	TCCR0B |= (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(0 << CS02)|(1 << CS01)|(1 << CS00); //Mode CTC, PreSCALER = 256 (100Hz)
	OCR0B   = 100;//250-1;
	TIFR1  |= (1<<OCF0B);
	TIMSK0 |= (1<<OCIE0B);
}

void set_encoder_pin(){

	//A is connected to PB4
	//B is connected to PB3
	//C is connected to GND

	pin_port encoder_a(DDRB,PORTB, PINB, PINB4);
	pin_port encoder_b(DDRB,PORTB, PINB, PINB3);
	
	//set the input mode with pull_up mode
	encoder_a.setMode(0);
	encoder_b.setMode(0);

}

void read_encoder_status(){

	//The values are read until the state reach:
	// 00 or 11 on A and B
	//We need to remember the statuses before that state
	// to recognise the direction 
	// in case:
	// A = 1 B = 0 and last status was A = 0 and B = 0 it CW (clock wise)
	// A = 0 B = 1 and last status was A = 1 and B = 1 it CW (clock wise)
	// A = 1 B = 0 and last status was A = 1 and B = 1 it CCW (counter clock wise)
	// A = 0 B = 1 and last status was A = 0 and B = 0 it CCW (counter clock wise)
	
	uint8_t stable_A;
	uint8_t stable_B;
	
	uint8_t temp_A;
	uint8_t temp_B;
	
	//First for initialisation read the port A and B
	//stable_A = encoder_a.getValue();
	//stable_B = encoder_b.getValue();
	
	//Now read the values temp for each timer interrupt
	//and replace with stable until it will reach value 00 or 11
}

namespace nm_encoder{

	//config.encoder_A(DDRB,PORTB, PINB, PINB4);
	//config.encoder_B(DDRB,PORTB, PINB, PINB3);

	encoder::encoder(pin_port A, pin_port B){
	
		config.encoder_A = A;
		config.encoder_B = B;
			
		//set the input mode with pull_up 
		config.encoder_A.setMode(0);
		config.encoder_B.setMode(0);
		
		//Read the initial values of encoder
		stable_port_a = config.encoder_A.getValue();
		stable_port_b = config.encoder_B.getValue();
		
		//Set the initial value of encoder to 0
		encoder_value = 0;
	
	}
	
	void encoder::read_encoder(){
		
		volatile uint8_t porta, portb;
		//Read the port A and port B values to temporary values
		
		porta = config.encoder_A.getValue();
		portb = config.encoder_B.getValue();
		
		//The values are reading until get value 00 or 11 
		if(porta != portb){
			
			//encoder is rotating
			//copy values to temp
			temp_port_a = porta;
			temp_port_b = portb;
			
		}else{ //new value is established
			
			//Now we need to find the correct rotation direction
			//based on last stable values of ports
			if(stable_port_a == 0 && stable_port_b == 0 && porta == 1 && portb == 1){
				
				//We have a change state of encoder
				//Now check the direction
				if(temp_port_a == 0 && temp_port_b == 1){
					
					//Direction CCW, decrement the value
					if(encoder_value > 0)
						encoder_value--;
				}else{
					//TODO: ensure there is no more possibilities, like temp and por are equal
					//Direction CW, increment the value
					if(encoder_value < MAX_ENCODER_VAL)
					encoder_value++;
				}
				
				stable_port_a = porta;
				stable_port_b = portb;
				
			}
			if(stable_port_a == 1 && stable_port_b == 1 && porta == 0 && portb == 0){
				
				//We have a change state of encoder
				//Now check the direction
				if(temp_port_a == 0 && temp_port_b == 1){
					
					//Direction CW, decrement the value
					if(encoder_value < MAX_ENCODER_VAL)
					encoder_value++;
					
					}else{
					
					//Direction CCW, increment the value
					if(encoder_value > 0)
					encoder_value--;
				}
				
				stable_port_a = porta;
				stable_port_b = portb;
				
			}
			
			//Set temp values to keep history
			temp_port_a = porta;
			temp_port_b = portb;
			
		}
		
	}
};