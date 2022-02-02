/*
 * lcd.cpp
 *
 * Created: 29.01.2022 19:47:55
 *  Author: maciek
 */ 

#include <stdlib.h>
#include "stdio.h"
#include "string.h"
#include "HD44780.h"
#include "int_fasade.h"
#include "interrupts.h"
#include "states.h"
#include "lcd.h"
#include "menu.h"

lcd* lcd::pointer;

lcd::lcd()
{
	if(!pointer)
	{
		pointer = this;
		init();
		object_list::get_object()->add_object(pointer);
	}
}

void lcd::init()
{
	//Init physical layer of LCD
	LCD_Initalize();
	LCD_Clear();
	LCD_Home();
	isupdated = true;
}

void lcd::refresh()
{
	strncpy(lcdline[0],((menu*)menu::get_object())->get_line(0),sizeof(char)*line_lenght);
	strncpy(lcdline[1],((menu*)menu::get_object())->get_line(1),sizeof(char)*line_lenght);
	
}

void lcd::draw_all()
{
	//print all lines
	if(isupdated)
	{
		for(int i = 0; i < lines_number; i++)
		{
			LCD_GoTo(0,i);
			LCD_WriteText(lcdline[i], line_lenght);
		}
		isupdated = false;
	}	
}

void  lcd::update(int_fast8_t dir)
{
	//dir = 0 - coming from interrupt
	//prepare the lines
	refresh();
	//present on screen
	draw_all();
}

/*
New state will change the screen view
Based on state the specific action will be performed
for example. If the state will be set_v
the value will be updated based on provided number
the value will be injected into specific part of lcd
To set the value the method set value will be executed
but this is only for leaf type of state
*/
void lcd::change_state(state_main new_state)
{
	isupdated = true;
	switch(new_state.id)
	{
		case WELCOME:
				{
					welcome(new_state);
					break;
				};
		
	}
}

lcd* lcd::get_object()
{
	return pointer;
}



void lcd::welcome(state_main state)
{
	
	
}