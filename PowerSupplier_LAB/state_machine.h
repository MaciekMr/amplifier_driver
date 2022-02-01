/*
 * state_machine.h
 *
 * Created: 31.01.2022 18:59:40
 *  Author: macie
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

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


//State can have path forward and path reverse
//Assigned objects
//in case the state will be activated 
//state_machien will trigger object to set its state
//when the action will be triggered (like rotate encoder, interrupt, etc.) state_machine will call dedicated method

struct state
{
	state_e id;
	state* prev, *next, *up, *down;
	state_type type;
	void*  active_objects[10];	
};



class state_machine
{

protected:
	state states[STATES_NO];
	
public:
	state_machine();  //configure state flow
	void register_object(state_e state_id, void *);
};





#endif /* STATE_MACHINE_H_ */