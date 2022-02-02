/*
 * menu.cpp
 *
 * Created: 29.01.2022 17:14:51
 *  Author: macie
 */ 
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "int_fasade.h"
#include "interrupts.h"
#include "states.h"
#include "lcd.h"
#include "menu.h"

//menu l_menu();

extern uint_fast16_t data;

menu* menu::object;

menu::menu()
{
	object = this;
	memset(line[0], 0, sizeof(char)*17);
	memset(line[1], 0, sizeof(char)*17);
	strncpy(line[0], line_1, sizeof(char)*16);
	strncpy(line[1], line_2, sizeof(char)*16);
	object_list::get_object()->add_object(object);
}

void menu::set_value(uint8_t line_no, float val)
{
	
	
}

void menu::set_value(uint8_t line_no, int value)
{
	
	//convert int to string
	char val[5];
	memset(val, 1, sizeof(char)*5);
	//memset(line[0], 0, sizeof(char)*16);
	//memset(line[1], 0, sizeof(char)*16);
	//Now put the value in correct place
	itoa(value, val, 10);
	if(line_no == 0)
	{
		strncpy(line[0], line_1, sizeof(char)*15);
		//strncpy(&line[0][3], val, sizeof(char)*5);
		for (uint8_t c = 0; c < strlen(val); c++)
			line[0][3 + c] = val[c];
		//copy the value into line
	}
	else
	{
		strncpy(line[1], line_2, sizeof(char)*15);
		//strncpy(&line[1][4], val, sizeof(char)*5);
		for (uint8_t c = 0; c < strlen(val); c++)
			line[1][3 + c] = val[c];
	}
	
	
	
	
}

char* menu::get_line(uint8_t line_no)
{
	if(line_no == 0)
		return line[0];
	else
		return line[1];	
}

void menu::update(int_fast8_t dir)
{
	set_value(0, (int)data);
}

menu* menu::get_object()
{
	return object;	
}