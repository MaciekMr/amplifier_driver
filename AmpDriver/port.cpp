/*
 * port.cpp
 *
 * Created: 19.01.2019 18:01:57
 *  Author: macie
 */ 

#include "DS1267.h"
#include <avr/io.h>

namespace nm_DS1267{

	pin_port::pin_port(uc dx,uc pox,uc pix,uc pi)
			:ddrx(dx),portx(pox),pinx(pix),pin(pi){
			
			
	}

	pin_port::pin_port(const pin_port & in_port){
		
		pin_port(in_port.ddrx, in_port.portx, in_port.pinx, in_port.pin);
	}

	/*
	* mode = 0 input
	* mode = 1 output
	*/

	void pin_port::setMode(uc mode){
	
		port_mode = mode;
		/*
		if(mode){
			//output
			ddrx  |= (1<<pinx);
			portx |= (0<<pinx);
		}else{
			//input
			ddrx  |= (0<<pinx);
			portx |= (1<<pinx); //Set up the pull-up resistor to avoid floating value
		} */
		
		if(mode){
			//output 
			ddrx  ^= (-1 ^ ddrx) & (1UL << pin); // set pin; 
			portx ^= (-0 ^ portx) & (1UL << pin); //|= (0<<pin); //default low
		}else{
			//input & pull_up
			MCUCR ^= (-0 ^ MCUCR) & (1UL << PUD); //PUD = 0 ;
			ddrx  ^= (-0 ^ ddrx) & (1UL << pin); // set pin;ddrx  |= (0<<pin);
			portx ^= (-1 ^ portx) & (1UL << pin); //portx |= (1<<pin); //Set up the pull-up resistor to avoid floating value		
		}
		
	}

	void pin_port::setValue(bool val){
	
		//Only if port_mode = 1 (output mode) we can set the value
		if(port_mode){
		
			pinx |= (val?(1<<pin):(0<<pin));
		}
	}

	uc pin_port::getValue(){
	
		 //uc test = ((pinx & (1<<pin))>>pin); //(PINB >> PINB1) & 1U;
		return((pinx >> pin) & 1U);	
	}
	
	uc pin_port::get_ddr_reg(){
		
		return(ddrx);
	}
	uc pin_port::get_port_reg(){
		
		return(portx);
	}
	uc pin_port::get_pinx_reg(){
		
		return(pinx);
	}
	uc pin_port::get_pin_pos(){
		
		return(pin);
	}
}