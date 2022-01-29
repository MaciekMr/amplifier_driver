/*
 * int_fasade.h
 *
 * Created: 29.01.2022 12:27:32
 *  Author: macie
 */ 
#include <stdarg.h>
#include <stdio.h>
#include <avr/io.h>

#ifndef INT_FASADE_H_
#define INT_FASADE_H_

class fasade
{

public:
	virtual void update(int_fast8_t dir) = 0; //dir define the change 0 - for interrupt, 1 - increase, -1 - decrease
	
};



#endif /* INT_FASADE_H_ */