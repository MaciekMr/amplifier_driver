/*
 * state_machine.cpp
 *
 * Created: 31.01.2022 19:08:48
 *  Author: maciek
 */ 

#include "stdio.h"
#include "stdlib.h"
#include "states.h"
#include "state_machine.h"



state_machine::state_machine()
{
	//define the routing
	state state_1; //={WELCOME, BRANCH, nullptr, nullptr, nullptr, nullptr};
	state state_2; //={VOLTAGE}; //, 2, nullptr, nullptr, nullptr, nullptr};
	state state_3; //={CURRENT}; //, 2, nullptr, nullptr, nullptr, nullptr};
	
	state_1.id = WELCOME;	
	state_1.prev = nullptr;
	state_1.next = &state_2;
	state_1.type = BRANCH;
	
	state_2.id = VOLTAGE;	
	state_2.up = &state_3;
	state_2.down = &state_3;
	state_2.type = LEAF;
	
	state_3.id = CURRENT;	
	state_3.up = &state_2;
	state_3.down = &state_2;
	state_3.type = LEAF;
	
	
	current_node = &state_1;
	pre_node	 = &state_2;
}

void state_machine::register_object(state_e state_id, void *)
{
	
	
}

//Change state to down
//It will select next->down, next->down->down, next->down->down->down
//Keep current node and current_pre_node 
//current_pre_node will be scrolled up/down
//when clicked current node = current_pre_node
//in case current_prenode = "back"
//current_node = current_node->prev
void state_machine::turn_left()
{
	
}
//change state to up
//It will select next->up, next->up->up, next->up->up->up
void state_machine::turn_right()
{
	
	
}

//change current state to new one 
//when scrolling
//Normally, we operate on current state
//and when turnig, just scroll the state without selection
//mostly for menu
//i.e.
//current menu config: up->bright, down->time
//so, the menu will show config:bright, after turning show time, 
//when click new state will be selected
//menu should always contains "back" option to move back in menu
/*
 menu tree
 -----(up)2.1
 1->(next)2
 ---(down)2.4


*/


void state_machine::switch_down()
{
	
	
}