/*
 * input_poll.cpp
 *
 * Created: 30.01.2022 18:32:41
 *  Author: maciek
 */ 
#include <stdarg.h>
#include <stdio.h>
#include "input_poll.h"


input_poll* input_poll::pointer;

input_poll::input_poll()
{
	pointer = this;
}

void input_poll::register_event(uint8_t guid, uint8_t event_id)
{
	
}

void input_poll::register_consumer(void *, uint8_t event_id)
{
	
}

void input_poll::set_event(uint8_t id, uint8_t event)
{
	
}

input_poll* input_poll::get_object()
{
	return (pointer);
}