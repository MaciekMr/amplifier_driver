/* 
* LCD.cpp
*
* Created: 08.05.2020 23:23:40
* Author: Maciek
*/

#include "avr/interrupt.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "DS1267.h"
#include "HD44780.h"
#include "LCD.h"



// default constructor
LCD::LCD()
{
	
	
} //LCD

// default destructor
LCD::~LCD()
{
} //~LCD

void LCD::refresh(){
	
	if(update[0]){
		
		LCD_GoTo(0,0);
		LCD_WriteText(lines[0]);
		update[0] = false;
	}
	if(update[1]){
		
		LCD_GoTo(0,1);
		LCD_WriteText(lines[1]);
		update[1] = false;
	}
	if(update[2]){
		
		LCD_GoTo(0,2);
		LCD_WriteText(lines[2]);
		update[2] = false;
	}
	if(update[3]){
		
		LCD_GoTo(0,3);
		LCD_WriteText(lines[3]);		
		update[3] = false;
	}
}

void LCD::set_line(uint8_t index, const char* line, uint8_t pos){
	
	clear_line(index);
	strncpy(&lines[index][pos], line, (20 - pos));
	update[index] = true;
	refresh();
}

void LCD::set_line(uint8_t index, int val, uint8_t pos){
	
	
	clear_line(index);
	itoa(val, digit, 10);
	strncpy(&lines[index][pos], &digit[0], strlen(digit));
	update[index] = true;
	refresh();
}

void LCD::clear_line(uint8_t index){
	
	strncpy(lines[index], "                    \0", 21);
}