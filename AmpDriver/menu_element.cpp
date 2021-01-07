
#include <string.h>
#include <avr/io.h>
#include "list.h"
#include "lcd.h"
#include "menu_element.h"

using namespace LCD_DISPLAY;


/*
void config_menu(){
	
	//Volume
	menu_element menu1_0(0, 0, 0, "Volume:", 0);
	menu_element menu1_1(1, 0, 1, "dB", -60);
	
	//Input
	menu_element menu2_0(0, 1, 0, "Input:", 0);
	menu_element menu2_1(1, 1, 0, "Line1", 0);
	menu_element menu2_2(1, 1, 0, "Line2", 0);
	menu_element menu2_3(1, 1, 0, "Line3", 0);
	menu_element menu2_4(1, 1, 0, "Line4", 0);

	//Config
	menu_element menu3_0(0, 2, 0, "Info:", 0);
	menu_element menu3_1(1, 2, 0, "Line1", 0);
	menu_element menu3_2(1, 2, 0, "Line2", 0);
	


	//Navigation (Volume)
	menu1_0.setdown(&menu1_1);
	menu1_0.setnext(&menu2_0);
	menu1_0.setprev(&menu3_0);
	menu1_0.settop(nullptr);

	menu1_1.settop(&menu1_0);

	//Navigation (Input)
	menu2_0.setdown(&menu2_1);
	menu2_0.setnext(&menu3_0);
	menu2_0.setprev(&menu1_0);
	menu2_0.settop(nullptr);

	menu2_1.setdown(nullptr);
	menu2_1.setnext(&menu2_2);
	menu2_1.setprev(&menu2_4);
	menu2_1.settop(&menu2_0);

	menu2_2.setdown(nullptr);
	menu2_2.setnext(&menu2_3);
	menu2_2.setprev(&menu2_1);
	menu2_2.settop(&menu2_0);

	menu2_3.setdown(nullptr);
	menu2_3.setnext(&menu2_4);
	menu2_3.setprev(&menu2_2);
	menu2_3.settop(&menu2_0);


	menu2_4.setdown(nullptr);
	menu2_4.setnext(&menu2_1);
	menu2_4.setprev(&menu2_3);
	menu2_4.settop(&menu2_0);


	//Navigation (Config)
	menu3_0.setdown(&menu3_1);
	menu3_0.setnext(&menu1_0);
	menu3_0.setprev(&menu2_0);
	menu3_0.settop(nullptr);

	menu3_1.setdown(nullptr);
	menu3_1.setnext(&menu3_2);
	menu3_1.setprev(&menu3_2);
	menu3_1.settop(&menu3_0);

	menu3_2.setdown(nullptr);
	menu3_2.setnext(&menu3_1);
	menu3_2.setprev(&menu3_1);
	menu3_2.settop(&menu3_0);

	menu menu(&menu1_0);
}

*/

menu* menu::pointer;


menu* menu::get_menu(){
	
	return (pointer);
}

menu::menu(menu_element* item):
	first_menu(item){ //We set up to first menu and important one
	
	//first_item is as well the main controll
	//set it to modify it
	pointer = this;
	current_menu = first_menu->sw_change_low_high();
	LCD_update();
}


//Method to process messages
void menu::sw_change_high_low() {

}
void menu::sw_change_low_high() { //finish the message to change button state (also could be select menu)

	menu_element* item;
	item = current_menu->sw_change_low_high();
	
	if (item != nullptr)
		current_menu = item;

	LCD_update();
}
void menu::sw_low() {

}
/*
menu_element may point to new menu_element (if scrolled)
or new value (if the value is incremented/decremented)
(if the value is changed, the nullptr is returned)
*/
void menu::turn_cw() { //switch menu to right

	//execute the current_menu method
	menu_element* element = current_menu->turn_cw();
	if (element != nullptr) {
		//new menu_element is returned
		current_menu = element;
	}else{ 
	
		int value = current_menu->get_value();
	}

	//When it is done, then update LCD value
	//TODO: build a new string for line2 and line1
	//
	//
	//
	//
	LCD_update();
}

void menu::turn_ccw() { //switch menu to left

	menu_element* element = current_menu->turn_ccw();
	if (element != nullptr) {
		//new menu_element is returned
		current_menu = element;
	}
	else {

		int value = current_menu->get_value();
	}

	//When it is done, then update LCD value
	//TODO: build a new string for line2 and line1
	//
	//
	//
	//
	LCD_update();
}

void menu::LCD_update() {

	LCD* lcd = LCD::getlcd();

	//set the first line of lcd
	//line1 -> the name of top menu
	//line2 -> the name of submenu
	if (current_menu->istop()) {
		//We are on the top menu
		lcd->set_line(0, current_menu->get_name());
		lcd->set_line(1, current_menu->get_child()->get_string());
	}
	else {

		lcd->set_line(0, current_menu->get_superior()->get_name());
		lcd->set_line(1, current_menu->get_string());
	}
	
	//lcd->print_lcd();
}





//---------------------------Menu Element class------------------------------------
//----------------------------------------------------------------------------------

menu_element::menu_element(uc _level, uc _index, uc _type, char* _name, int _value) 
	:level(_level), index(_index), type(_type)/*, name(_name)*/, value(_value){

	strncpy(name, _name, LCD_LEN); //Copy text to element

	top = down = prev = next = nullptr;

}

menu_element* menu_element::sw_change_low_high()
{
	//this action will trigger two actions:
	//return the sub_menu(lower)
	//or if the sub_menu is = nullptr
	//trigger the new settings
	//Additionally checks if the current_menu is != first_menu

	if (down != nullptr) {

		return(down);
	}
	else {

		//There is no submenu
		//so we do the selection and go up

		//We need to apply new settings, like new input


		//Now return the upper menu
		return(top);
	}
}

menu_element* menu_element::turn_cw() {

	//Check it the right neighbour is not empty
	if (this->next != nullptr) {
		//return next menu
		return(this->next);
	}else{
		//check the type of the element and update value/increment value
		this->value++;
		return(nullptr);
	}

}

menu_element* menu_element::turn_ccw() {

	//Check it the right neighbour is not empty
	if (this->prev != nullptr) {
		//return next menu
		return(this->prev);
	}
	else {
		//check the type of the element and update value/increment value
		this->value--;
		return(nullptr);
	}

}

char* menu_element::get_name()
{
	return(name);
}

int menu_element::get_value() {

	if (next == nullptr) {

		return(value);
	}
	
}

char* menu_element::get_string()
{
	//char val[LCD_LEN];
	uc index = 0;
	if(next != nullptr)
		return name;
	else {

		//create value as char
		if (value > -1) {
			//add '+' at the begining
			text_value[0] = '+';
			index++;
		}
		char * ret = itoa(value, &text_value[index], 10);
		int len = strlen(ret) + index;
		strncpy(&text_value[len], name, (LCD_LEN - len));
		return(text_value);
	}
}

menu_element* menu_element::get_superior()
{
	return (top);
}

menu_element* menu_element::get_child()
{
	return(down);
}

bool menu_element::istop()
{
	if (top)
		return false;
	return true;
}

void menu_element::setnext(menu_element* item)
{
	next = item;
}

void menu_element::setprev(menu_element* item)
{
	prev = item;
}

void menu_element::settop(menu_element* item)
{
	top = item;
}

void menu_element::setdown(menu_element* item)
{
	down = item;
}
