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
	TCCR0B |= (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(0 << CS02)|(1 << CS01)|(0 << CS00); //Mode CTC, PreSCALER = 1024 (100Hz) -> 10ms
	OCR0B   = 4;//250-1; 100Hz
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
		
		/*	
		//set the input mode with pull_up 
		config.encoder_A.setMode(0);
		config.encoder_B.setMode(0);
		config.encoder_SW.setMode(0);
		
		
		*/
		//Read the initial values of encoder
		output_a		= (ENC_PORT>>ENC_PORT_A)&1U;    //config.encoder_A.getValue();
		output_b		= (ENC_PORT>>ENC_PORT_B)&1U;    //config.encoder_B.getValue();
		stable_port_sw	= (ENC_PORT>>ENC_PORT_SW)&1U;    //config.encoder_SW.getValue();
		//Set the initial value of encoder to 0
		
		temp_out_a = output_a;
		temp_out_b = output_b;
		
		
		encoder_value = 0;
		direction     = 0;
		_state        = 0; 
		encoder_pointer = this;
		
	}
	
	bool encoder::get_sw_state(){
	
		return stable_port_sw;	
	}
	
	
	//Sometimes the encoder can work on negative signals.
	//Then the signals has to be negative
	
	void encoder::read_encoder(){
		
		//Read the port A and port B values to temporary values
		/*
		stable_port_sw = config.encoder_SW.getValue();
		porta          = config.encoder_A.getValue();
		portb          = config.encoder_B.getValue();
		*/
		stable_port_sw	  = get_state(0);
		output_a          = get_state(1);
		output_b          = get_state(2);
		
		
		/*
		_state = get_cencoder_state();
		
		*//*
		If the porta != temp_port_a && portb == temp_port_b
		-- we have rotation started
		-- it is CW
		*/
		//Define the rotation direction
		//First check if the A is before B
		//Assuming the high level is no rotation
		
		//a and b -> 1,0
		/*
		if((_state & enc_1) &&
		  (_temp_state & enc_3)){
			  
			  direction = 0;
		  }
		  
		if((_state & enc_2) &&
		(_temp_state & enc_3)){
			  
			direction = 1;
		}
	
		if((_state & enc_2) &&
		(_temp_state & enc_3)){
			
			direction = 1;
		}
		
		if((_state & enc_0) &&
		(_temp_state & enc_1)){
				
			encoder_value--;
		}
		
		if((_state & enc_0) &&
		(_temp_state & enc_2)){
			
			encoder_value++;
		}
		
		*/
	
		//Check ccw
			
		if((output_a == 0 && temp_out_a == 1)
		&& (output_b == 1 && temp_out_b == 1)) {

			//Rotation begin
			direction = 0;
			//printf("Rotation cw begin:\n");

		}

		//Check cw
		if ((output_a == 1 && temp_out_a == 1)
		&& (output_b == 0 && temp_out_b == 1)) {

			//Rotation begin
			direction = 1;
			//printf("Rotation ccw begin:\n");
		}

		//Next round of ccw - both outs are equal
		if ((output_a == 0 && temp_out_a == 0)
		&& (output_b == 0 && temp_out_b == 1)) {
			
			//Now the output B is low
			encoder_value--;
			//printf("Rotation cw continue\n");
			
		}
		//move cw
		if ((output_a == 0 && temp_out_a == 1)
		&& (output_b == 0 && temp_out_b == 0)) {

			//Now the output A is low
			encoder_value++;
			//printf("Rotation ccw continue\n");
		}


		temp_out_a = output_a;
		temp_out_b = output_b;	
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
		
		/*
		__asm{
			
			in r16, ENC_PORT ;loading encoder port to r16
			in r17, 0
			in r17, (r16>>ENC_PORT_A)&0x01
						
		}*/
		
	}
	
	
	uint16_t encoder::get_encoder_value(){
		
		return(encoder_value);
	}
	
	encoder * encoder::get_encoder(){
		
		return(encoder_pointer);
		
	}
	
	uc encoder::get_cencoder_state(){
		
		uc _state_ = (((ENC_PORT>>ENC_PORT_A)&1U)<<1)|
					 (((ENC_PORT>>ENC_PORT_B)&1U));
		
		return(_state_);
	}
	
	uc encoder::get_button_state(){
		
		uc _state_ = ((ENC_PORT>>ENC_PORT_SW)&1U);
		
		return(_state_);
	}
	
	uc encoder::get_state(){
	
		return(_state);
	}
	
};