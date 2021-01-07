/* 
* config_menu.cpp
*
* Created: 14.05.2020 22:10:10
* Author: Maciek
*/

#include <avr/io.h>
#include "Controller.h"
#include <string.h>
#include "list.h"
#include "config_menu.h"






// default constructor
config_menu::config_menu()
{
	current_level1_menu = 0;
	current_level2_menu = 0;
	current_level3_menu = 0;
	
	
	menu_element volume_val = {0, "", 0, 1,2,0, nullptr};
	menu_element volume_txt = {2, "Volume:", 0, 1,1,0, &volume_val};
		
	menu_element input_val_1 = {2, "Line1", 0, 1, 2, 0, &input_val};	
	menu_element input_val_2 = {2, "Line2", 0, 1, 2, 0, &input_val};	
	menu_element input_val_3 = {2, "Line3", 0, 1, 2, 0, &input_val};	
	menu_element input_val_4 = {2, "Line4", 0, 1, 2, 0, &input_val};	
	menu_element input_selection = {2, "Input:", 0, 1, 2, 0, &input_val};
	
	
	//menu[0] = 
	
} //config_menu

// default destructor
config_menu::~config_menu()
{
	
} 

void config_menu::switch_change_down()
{
	
} 

void config_menu::switch_change_up()
{
	
} 

void config_menu::switch_down()
{
	
} 

void config_menu::increment(){
	
}

void config_menu::decrement(){
	
	
}