/* 
* config_menu.h
*
* Created: 14.05.2020 22:10:10
* Author: Maciek
*/


#ifndef __CONFIG_MENU_H__
#define __CONFIG_MENU_H__


#define level_0_1_0  "Volume:"
#define level_1_0_0  "Menu"
#define level_1_1_0  "Input"
#define level_1_2_0  "CD:"
#define level_1_2_1  "Line:"
#define level_1_2_2  "Bluetooth:"
#define level_1_2_3  "Line2:"
#define level_2_1_0  "Status"
#define level_2_1_1  "Supply voltage 1"
#define level_2_1_2  "Supply voltage 2"
#define level_3_1_0  "Timer"
#define level_3_1_1  "Total time"
#define level_3_1_2  "Time today"

#define menu_back    "Back"

#define max_len      20  //maximum lenght of the string (LCD)
/*

Level1    Volume:      ->  Menu                                  Menu                              Menu ----------------------------> Volume

Level2    0dB (+/-)        Input ------------------------------> Status:-------------------------> Timer

Level3					   CD:->Line:->Bluetooth:->Line2:->Back  Supply volt1->Supply volt2->Back   Total time->Time today->Back

Level4

*/



/*

Menu:

Table:

[1][1][0] -> Volume
[1][2][0] -> -/+XXX dB

Push button-> jump to

[2][1][0] - Menu: Input /Action - push - select input/\ Rotate - change menu
[2][2][1] - Line1 ->Action push button //select and back up
[2][2][2] - Line2
[2][2][3] - Line3
[2][2][4] - Line4


[2][1][0] - Menu2: Info /Action - push - select input/\ Rotate - change menu
[2][2][1] - Supply voltage: XX V ->Action push button //select and back up
[2][2][2] - Supply current: XX A
[2][2][3] - Other1:  XX
[2][2][4] - Other2:  XX


Activity to do:
1. Present on LCD (set the text)
2. Set the device value


*/

struct menu_element{
	
	uint8_t type;  //type digit, string, menu (0,1,2)  (digit - increment the amount, string -> edit?, menu -> scroll left, right or select submenu
	char name[max_len];
	uint8_t val;
	
	uint8_t index_x, index_y, index_z;
	
	menu_element *submenu;  // if = null - no submenu
	
	};

class config_menu:
	public Controller
{
//variables
public:
protected:
	uint8_t current_level1_menu, current_level2_menu, current_level3_menu;  //index of three dimensional table
	menu_element  menu[];
	
	menu_element * find_elemen(uint8_t index_x, uint8_t index_y, uint8_t index_z);
private:

//functions
public:
	config_menu();
	~config_menu();
	
	void increment();
	void decrement();
	void switch_change_down();
	void switch_change_up();
	void switch_down();
	
protected:
	void scroll_menu(bool direction);
	void select_menu(); //react on switch push - if level1 is active -> jump to level2 -> then activate function


private:
	config_menu( const config_menu &c );
	config_menu& operator=( const config_menu &c );
	uint8_t  menu_pos[];	
}; //config_menu

#endif //__CONFIG_MENU_H__
