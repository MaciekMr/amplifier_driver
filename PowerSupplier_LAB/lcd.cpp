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
}

void lcd::refresh()
{
	strncpy(lcdline[0],((menu*)menu::get_object())->get_line(0),sizeof(char)*line_lenght);
	strncpy(lcdline[1],((menu*)menu::get_object())->get_line(1),sizeof(char)*line_lenght);
	
}

void lcd::draw_all()
{
	//print all lines
	for(int i = 0; i < lines_number; i++)
	{
		LCD_GoTo(0,i);
		LCD_WriteText(lcdline[i], line_lenght);
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

lcd* lcd::get_object()
{
	return pointer;
}