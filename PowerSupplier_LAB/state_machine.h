/*
 * state_machine.h
 *
 * Created: 31.01.2022 18:59:40
 *  Author: macie
 */ 


#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_



//State can have path forward and path reverse
//Assigned objects
//in case the state will be activated 
//state_machien will trigger object to set its state
//when the action will be triggered (like rotate encoder, interrupt, etc.) state_machine will call dedicated method

struct state:public state_main
{
	state* prev, *next, *up, *down;
	void*  active_objects[10];	
};



class state_machine
{
private:
	state *current_node;
	state *pre_node;
protected:
	state states[STATES_NO];
	
public:
	state_machine();  //configure state flow
	void register_object(state_e state_id, void *);
	
	void turn_left();
	void turn_right();
	void switch_down();
};





#endif /* STATE_MACHINE_H_ */