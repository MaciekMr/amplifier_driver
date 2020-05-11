/*
 * DG409.cpp
 *
 * Created: 19.01.2019 23:14:39
 *  Author: macie
 */ 

#include "port.h"
#include "DG409.h"

using namespace nm_DS1267;
using namespace nm_list;

namespace nm_DG409{

	DG409::DG409(const pin_port & in1, const pin_port & in2){
		
		dg409_config.line1 = in1;
		dg409_config.line2 = in2;
		//Always set to 00 first
		//Means first input
		//1. Set pins as output
		dg409_config.line1.setMode(true);
		dg409_config.line2.setMode(true);
		//2. Set Value to 00;
		dg409_config.line1.setValue(false);
		dg409_config.line2.setValue(false);
	
		//Now configure input with names (Names will be shown on the screen
		//We have 4 inputs
		//Input 1 - Line 1 - address 00
		//input_list[0].input_name[] = "Line 1\0";
		memset(input_list[0].input_name,0, name_len);
		strcpy(input_list[0].input_name, "Line 1");
		input_list[0].address_config = 0;
		//Input 2  Line 2 - adres 01
		//input_list[0].input_name[] = "Line 2\0";
		memset(input_list[1].input_name,0, name_len);
		strcpy(input_list[1].input_name, "Line 2");
		input_list[1].address_config = 1;
		//Input 3 - phono - address 10
		//input_list[2].input_name[] = "Phone\0";
		memset(input_list[2].input_name,0, name_len);
		strcpy(input_list[2].input_name, "Phone");
		input_list[2].address_config = 2;
		//Input 4 - DAC - address 11
		//input_list[3].input_name[] = "DAC\0";
		memset(input_list[3].input_name,0, name_len);
		strcpy(input_list[3].input_name, "DAC");
		input_list[3].address_config = 3;
	}

	DG409::~DG409(){
	
	}
	
	
	
	
};