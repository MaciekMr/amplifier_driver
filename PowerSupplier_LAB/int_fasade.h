/*
 * int_fasade.h
 *
 * Created: 29.01.2022 12:27:32
 *  Author: macie
 */ 


#ifndef INT_FASADE_H_
#define INT_FASADE_H_

class fasade
{

public:
	void update(int_fast8_t dir); //dir define the change 0 - for interrupt, 1 - increase, -1 - decrease
	
};



#endif /* INT_FASADE_H_ */