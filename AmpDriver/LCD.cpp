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

namespace LCD_DISPLAY {
	
	LCD * LCD::pointer;

	LCD::LCD()
	{
		pointer = this;	
		//clear_line(0,20);
		//clear_line(1,20);
		clear_line(2,20);
		clear_line(3,20);
		memset(lines[0], 0, line_lenght);
		memset(lines[1], 0, line_lenght);
		//memset(lines[2], 0, line_lenght);
		//memset(lines[3], 0, line_lenght);
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
	
		uc len = strlen(line) + pos;
		uc len2 = strlen(lines[index]);
		clear_line(index, len, pos);
		strncpy(&lines[index][pos], line, (line_lenght - pos - 1));
		if((len2 - len) > 0)
			strncpy(&lines[index][len], "          ", (len2 - len));
		update[index] = true;
		//refresh();
	}

	void LCD::set_line(uint8_t index, int val, uint8_t pos){
	
		itoa(val, digit, 10);
		uc len = strlen(digit);
		clear_line(index, len, pos);
		strncpy(&lines[index][pos], digit, len);
		update[index] = true;
		//refresh();
	}

	void LCD::clear_line(uint8_t index, uint8_t len, uint8_t pos){
	
		//System has to clean the line from pos to the end
		//without last char \0'
		strncpy(&lines[index][pos], &clean_line[pos], (line_lenght - pos));	
		memset(&lines[index][line_lenght], 0, 1);
	}	

	LCD* LCD::getlcd(){
	
		return(pointer);
	}

}