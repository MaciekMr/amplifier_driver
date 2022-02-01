/*
 * state_machine.cpp
 *
 * Created: 31.01.2022 19:08:48
 *  Author: maciek
 */ 

#include "stdio.h"
#include "stdlib.h"
#include "state_machine.h"



state_machine::state_machine()
{
	//define the routing
	state state_1={WELCOME, nullptr, nullptr, nullptr, nullptr};
	state state_2={VOLTAGE, nullptr, nullptr, nullptr, nullptr};
	state state_3={CURRENT, nullptr, nullptr, nullptr, nullptr};
		
	state_1.prev = nullptr;
	state_1.next = &state_2;
	state_1.type = BRANCH;
	
	state_2.up = &state_3;
	state_2.down = &state_3;
	state_2.type = LEAF;
	
	state_3.up = &state_2;
	state_3.down = &state_2;
	state_3.type = LEAF;
}

void state_machine::register_object(state_e state_id, void *)
{
	
	
}