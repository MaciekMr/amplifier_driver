/*
 * button_conf.h
 *
 * Created: 22.01.2019 22:51:56
 *  Author: macie
 */ 


#ifndef BUTTON_CONF_H_
#define BUTTON_CONF_H_

using namespace nm_DS1267;	

//Controller has 4 buttons
//First is together with roller

//MCUCR register has to be set to pull-up - bit 6 set to 0 to enable pul-up

struct button{
	
	pin_port	button_port;
	bool		status;
	
	};








#endif /* BUTTON_CONF_H_ */