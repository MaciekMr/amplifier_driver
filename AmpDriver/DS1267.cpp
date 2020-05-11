


#include "DS1267.h"

namespace nm_DS1267{


	DS1267::DS1267(ds1267Port ds)
					:ds_port(ds){
	
		//set the volume to 0
		//default is 50%
		volA_state = 0;
		volB_state = 0;
		writeVol();
	
	}

	DS1267::~DS1267(){
	
		//setVolume to 0!
		
	}


	bool DS1267::writeData(){
	
		uc count = 0;
		int testregister = 1;
			
		//Set pins to outputmode
		ds_port.pin1.setMode(1);
		ds_port.pin2.setMode(1);
		ds_port.pin3.setMode(1);
		
		//Clear pins to 0
		ds_port.pin1.setValue(false);
		ds_port.pin2.setValue(false);
		ds_port.pin3.setValue(false);
	
		//start programming
		//1 - set RST to 1
	
		ds_port.pin1.setValue(true);
	
		//send the data
		//1. Set CLK to 1
		//2. Set the DQ to LSB bit of 17 bit
		// ST, volA, volB - b0 - stack (= 0)
		buildregister();
	
		for(; count < register_len ; count++){
			//DQ set to current bit of register (do AND with bit on given position
			//We need to send bits in LSB->MSB order
		
			if((testregister<<count) & ds_register){
				//if 1
				//set DQ to 1	
				ds_port.pin3.setValue(true);
			}else{
				//if 0
				//set DQ to 0;
				ds_port.pin3.setValue(false);
			}
			//Change CLK from low to high
			ds_port.pin2.setValue(true);
			//wait 5 ms
			//Change CLK from high to low
			ds_port.pin2.setValue(false);
		
		}
	
		int reg = readVol();
	
		if(reg == ds_register)
			return true;
		else
			return false;	
	
	}



	void DS1267::buildregister(){
	
		ds_register = 0x0; //set stack bit to 0
	
		ds_register |= volA_state << 1;
		ds_register |= volB_state << 9;
	
	}

	int DS1267::readVol(){
	
		return 0;
	}

	void DS1267::resetuC(){
	
	}

	ds1267Port::ds1267Port(pin_port p1, pin_port p2, pin_port p3)
		:pin1(p1),pin2(p2),pin3(p3){
				
	};


}

