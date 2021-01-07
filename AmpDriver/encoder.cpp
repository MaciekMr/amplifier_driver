/*
 * encoder.cpp
 *
 * Created: 20.02.2019 20:12:43
 *  Author: macie
 */ 

#include "avr/interrupt.h"
#include "port.h"
#include "menu_element.h"
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
	
	//Function executed 7kHz
	if(reaction++ > 100){
		
		reaction = 0;  //Refresh the screen 60Hz
	}
	nm_encoder::encoder *en = nm_encoder::encoder::get_encoder();
	en->read_encoder();
	en->read_switch();
}


void set_encoder_timer(){
	
	TCCR0A  = 0x00;
	TCNT0   = 0x00;
	TCCR0B |= (0<<FOC0A)|(0<<FOC0B)|(0<<WGM02)|(0 << CS02)|(1 << CS01)|(1 << CS00); //Mode CTC, PreSCALER = 64 -> 125kHz (base 8MHz)
	OCR0B   = 20;// trigerred every 20th time -> 6,25kHz
	TIFR1  |= (1<<OCF0B);
	TIMSK0 |= (1<<OCIE0B);
}

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


namespace nm_encoder{

	encoder * encoder::encoder_pointer;


	//encoder::encoder(pin_port SW, pin_port A, pin_port B)
	encoder::encoder(){
	
		MCUCR ^= (-0 ^ MCUCR) & (1UL << PUD); //PUD = 0 ;
		
		//set the input mode with pull_up 
		ENC_DATA_REG  ^= (-0 ^ ENC_DATA_REG) & (1UL << ENC_PORT_SW); // set pin;ddrx  |= (0<<pin);
		ENC_DATA_REG  ^= (-0 ^ ENC_DATA_REG) & (1UL << ENC_PORT_A);
		ENC_DATA_REG  ^= (-0 ^ ENC_DATA_REG) & (1UL << ENC_PORT_B);
		
		ENC_PORT ^= (-1 ^ ENC_PORT) & (1UL << ENC_PORT_SW);
		ENC_PORT ^= (-1 ^ ENC_PORT) & (1UL << ENC_PORT_A);
		ENC_PORT ^= (-1 ^ ENC_PORT) & (1UL << ENC_PORT_B);  //portx ^= (-1 ^ portx) & (1UL << pin);
		
		
		//Read the initial values of encoder
		
		en_state = get_encoder_state();
		sw_state = get_button_state(); //ENC_PORT>>ENC_PORT_SW)&1U;    //config.encoder_SW.getValue();
		//Set the initial value of encoder to 0
		
		sw_state = get_button_state();
		
		en_temp_state = en_state;
		sw_tmp_state = sw_state;
		
		encoder_value = 0;
		direction     = 0;
		clicks        = 0;
		encoder_pointer = this;
		
	}
		
	/*
	This method will read the button state
	and will execute 3 calls,
	depends on switch state:
	1. Switch change from UP-> DOWN
	2. Switch is DOWN
	3. Switch is change from DOWN-> UP
	
	*/
	
	void encoder::read_switch(){
		
		sw_state = get_button_state();
		
		if(sw_state != sw_tmp_state){
			
			if(sw_state == 0){
				//call sw_change_down()
				//call_sw_down();
				sw_change_down();
				sw_down();
			}else{
				//call sw_change_up();
				sw_change_up();
			}
			sw_tmp_state = sw_state;
		}
		
	}
	
	
	
	//Sometimes the encoder can work on negative signals.
	//Then the signals has to be negative
	
	void encoder::read_encoder(){
		
		//Read the port A and port B values to temporary values
		en_state	   = get_encoder_state();
		
		//Define the rotation direction
		//First check if the A is before B
		//Assuming the high level means no rotation
		//if state of encoder is changed
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
			en_temp_state = en_state;
	
		}

				
	}
	
	uint16_t encoder::get_encoder_value(){
		
		return(encoder_value);
	}
	
	encoder * encoder::get_encoder(){
		
		return(encoder_pointer);
		
	}
	
	 
	uc encoder::get_encoder_state(){
		
		uc _state_ = (((ENC_PORT>>(ENC_PORT_A-1))&2U)|  //check second bit (and 00000010)
		   		      ((ENC_PORT>>ENC_PORT_B)&1U));     // check last bit
		
		return(_state_);
	}
	
	uc encoder::get_button_state(){
		
		uc _state_ = (ENC_PORT>>ENC_PORT_SW)&1U;  //0 or 1
		
		#ifdef SCHMITT_NEG
			_state_ ^= 1U;
		#endif		
		
		return(_state_);
	}
		
	void encoder::increment_val(){
		
		encoder_value++;
		//call menu action
		menu* mn = menu::get_menu();
		mn->turn_cw();
	}
	
	void encoder::decrement_val(){
		
		encoder_value--;
		menu* mn = menu::get_menu();
		mn->turn_ccw();
	}
	
	void encoder::sw_down(){
		
		encoder_value = 0;
		menu* mn = menu::get_menu();
		mn->sw_low();
	}
	
	void encoder::sw_change_down(){
		
		//encoder_value = 0;
		menu* mn = menu::get_menu();
		mn->sw_change_high_low();
	}
	
	void encoder::sw_change_up(){
		
		clicks++;
		menu* mn = menu::get_menu();
		mn->sw_change_low_high();
	}
	
	uc encoder::get_clicks(){
		
		return(clicks);
	}
};