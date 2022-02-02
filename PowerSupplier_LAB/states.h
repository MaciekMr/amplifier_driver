/*
 * states.h
 *
 * Created: 02.02.2022 21:14:26
 *  Author: macie
 */ 


#ifndef STATES_H_
#define STATES_H_


#define STATES_NO   3

#define STATE_1  WELCOME
#define STATE_2  VOLTAGE
#define STATE_3  CURRENT

//State type
//for branch we can scroll up,down
//When select we can move to next
//When leaf , there is no next, but we can set value when clicked

enum state_type
{
	BRANCH = 1,
	LEAF = 2
};

enum state_e
{
	WELCOME=0,
	VOLTAGE=1,
	CURRENT=2
};


struct state_main
{
	state_e id;
	state_type type;
};


#endif /* STATES_H_ */