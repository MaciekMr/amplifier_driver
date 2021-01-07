#pragma once

#define LCD_LEN 20

typedef unsigned char uc;

/*
Menu element creates the multilevel list of menu elements
each element reacts on button
Single class keeps the list of elements
and pass the method to current position of menu (execute the method of element)

*/


void config_menu();

class menu_element
{
protected:
	uc level; //0 - main level, 1 - sublevel (activate by click main level)
	uc index; //just to know the order

	/*Navigation*/
	menu_element* next; //forward menu
	menu_element* prev; //backward menu

	menu_element* down; // selected by button next level
	menu_element* top;    //selected by button level up
	/*Navigation*/

	/*Value string*/

	char text_value[LCD_LEN];

private:
	uc type; //0 - menu type - text (scroll to next), 1 - digit (scroll to increase/decrease value), 2 - edit??
	char name[LCD_LEN];
	int value; //if the menu has only digital value (modified by rolling encoder)

	//auto *pointer_to_driver;

public:
	menu_element(uc, uc, uc, char*, int);

	//Method to process messages
	menu_element* sw_change_high_low();
	menu_element* sw_change_low_high(); //finish the message to change button state (also could be select menu)
	menu_element* sw_low();
	menu_element* turn_cw(); //switch menu to right
	menu_element* turn_ccw(); //switch menu to left
	//int			  get_value();

	//Set the neighbvours

	void setnext(menu_element*);
	void setprev(menu_element*);
	void settop(menu_element*);
	void setdown(menu_element*);

	//get the item values, like name and value
	char* get_name();
	int   get_value(); //return value as int, if there is no neighbours-set the value, if we have neighbours - retunr the index
	char* get_string();
	//get the superior of menu
	menu_element* get_superior();
	menu_element* get_child();
	bool istop();

};

class menu {

protected:
	static
	menu* pointer;
	menu_element* first_menu; //mostly volume
	menu_element* current_menu;
	void		  LCD_update(); //set new values to LCD
public:
	menu(menu_element*);
	
	
	//Method to process messages
	void sw_change_high_low();
	void sw_change_low_high(); //finish the message to change button state (also could be select menu)
	void sw_low();
	void turn_cw(); //switch menu to right
	void turn_ccw(); //switch menu to left
	
	static
	menu* get_menu();
};