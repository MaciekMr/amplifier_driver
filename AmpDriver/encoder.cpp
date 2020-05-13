/*
 * encoder.cpp
 *
 * Created: 20.02.2019 20:12:43
 *  Author: macie
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
	
	//Function executed each 10 ms
	if(reaction++ > 1024)
		reaction = 0;
	nm_encoder::encoder *en = nm_encoder::encoder::get_encoder();
	en->read_encoder();
}


void set_encoder_timer(){
	
	TCCR0A  = 0x00;
	TCNT0   = 0x00;
	TCCR0B |= (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(0 << CS02)|(1 << CS01)|(1 << CS00); //Mode CTC, PreSCALER = 1024 (100Hz) -> 10ms
	OCR0B   = 20;//250-1; 100Hz
	TIFR1  |= (1<<OCF0B);
	TIMSK0 |= (1<<OCIE0B);
}

void set_encoder_pin(){
	
	//SW is connected to PB1
	//A  is connected to PB2
	//B  is connected to PB3
	
	pin_port encoder_sw(DDRB,PORTB, PINB, PINB1);
	pin_port encoder_a(DDRB,PORTB, PINB, PINB2);
	pin_port encoder_b(DDRB,PORTB, PINB, PINB3);
	
	
	//set the input mode with pull_up mode
	encoder_sw.setMode(0);
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
	
	//First for initialisation read the port A and B
	//stable_A = encoder_a.getValue();
	//stable_B = encoder_b.getValue();
	
	//Now read the values temp for each timer interrupt
	//and replace with stable until it will reach value 00 or 11
}

namespace nm_encoder{

	//config.encoder_A(DDRB,PORTB, PINB, PINB4);
	//config.encoder_B(DDRB,PORTB, PINB, PINB3);
	encoder * encoder::encoder_pointer;


	encoder::encoder(pin_port SW, pin_port A, pin_port B){
	
		/*
		config.encoder_SW = SW;
		config.encoder_A  = A;
		config.encoder_B  = B;
		*/
		
		MCUCR ^= (-0 ^ MCUCR) & (1UL << PUD); //PUD = 0 ;
		
		//set the input mode with pull_up 
		ENC_DATA_REG  ^= (-0 ^ ENC_DATA_REG) & (1UL << ENC_PORT_SW); // set pin;ddrx  |= (0<<pin);
		ENC_DATA_REG  ^= (-0 ^ ENC_DATA_REG) & (1UL << ENC_PORT_A);
		ENC_DATA_REG  ^= (-0 ^ ENC_DATA_REG) & (1UL << ENC_PORT_B);
		
		ENC_PORT ^= (-1 ^ ENC_PORT) & (1UL << ENC_PORT_SW);
		ENC_PORT ^= (-1 ^ ENC_PORT) & (1UL << ENC_PORT_A);
		ENC_PORT ^= (-1 ^ ENC_PORT) & (1UL << ENC_PORT_B);  //portx ^= (-1 ^ portx) & (1UL << pin);
		
		
		//Read the initial values of encoder
		
		en_state = get_cencoder_state();
		stable_port_sw	= (ENC_PORT>>ENC_PORT_SW)&1U;    //config.encoder_SW.getValue();
		//Set the initial value of encoder to 0
		
		sw_state = get_button_state();
		
		en_temp_state = (en_state>>2);
		sw_tmp_state = sw_state;
		
		encoder_value = 0;
		direction     = 0;
		encoder_pointer = this;
		
	}
	
	bool encoder::get_sw_state(){
	
		if(sw_state != sw_tmp_state)
			sw_change();
		return stable_port_sw;	
	}
	
	
	//Sometimes the encoder can work on negative signals.
	//Then the signals has to be negative
	
	void encoder::read_encoder(){
		
		//Read the port A and port B values to temporary values
		stable_port_sw = get_button_state();
		en_state	   = get_cencoder_state();
		
		/*
		If the porta != temp_port_a && portb == temp_port_b
		-- we have rotation started
		-- it is CW
		*/
		//Define the rotation direction
		//First check if the A is before B
		//Assuming the high level means no rotation
		
		
		


		//if state of encoderis changed
		if(en_state != en_temp_state){
			
	
			
			//cw direction
			if(en_state == enc_1){  //en_state -> 0001
			
				direction = 0;
			}
		
			//ccw rotation
			if(en_state == enc_2){   //en_state -> 0010
			
				direction = 1;
			}
		
#ifdef SCHMITT_NEG					
			
			if(direction == 0 && en_state == enc_3){ //en_state -> 0011
				decrement_val();
				direction = -1;
			}
		
			if(direction == 1 && en_state == enc_3){ //en_state -> 0011
			
				increment_val();
				direction = -1;
			}
#else
			
			if(direction == 0 && en_state == enc_0){ //en_state -> 0000
				decrement_val();
				direction = -1;
			}
						
			if(direction == 1 && en_state == enc_0){ //en_state -> 0000
				
				increment_val();
				direction = -1;
			}
#endif		
		}

		en_temp_state = en_state;		
	}
	
	
	
	
	
	uc  encoder::get_state(uc pin){
		
		
		switch(pin){
			
			case 0:
				return((ENC_PORT>>ENC_PORT_SW)&1U);
			case 1:
				return((ENC_PORT>>ENC_PORT_A)&1U);
			case 2:
				return((ENC_PORT>>ENC_PORT_B)&1U);
			default:
				return((((ENC_PORT>>ENC_PORT_A)&1U)<<1)|
						((ENC_PORT>>ENC_PORT_B)&1U));  //return gray code 00,01,10,11 
		}			
		
	}
	
	
	uint16_t encoder::get_encoder_value(){
		
		return(encoder_value);
	}
	
	encoder * encoder::get_encoder(){
		
		return(encoder_pointer);
		
	}
	
	inline 
	uc encoder::get_cencoder_state(){
		
		uc _state_ = ((((ENC_PORT>>ENC_PORT_A)&1U)<<1)|
					  (((ENC_PORT>>ENC_PORT_B)&1U)));
		return(_state_);
	}
	
	uc encoder::get_button_state(){
		
		uc _state_ = ((ENC_PORT>>ENC_PORT_SW)&1U);
		
		return(_state_);
	}
	
	uc encoder::get_state(){
	
		return(en_state);
	}
	
	
	void encoder::increment_val(){
		
		encoder_value++;
	}
	
	void encoder::decrement_val(){
		
		encoder_value--;
	}
	
	void encoder::sw_change(){
		
		encoder_value = 0;
	}
	
};