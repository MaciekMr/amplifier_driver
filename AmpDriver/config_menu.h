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


/*

Level1    Volume:      ->  Menu                                  Menu                              Menu ----------------------------> Volume

Level2    0dB (+/-)        Input ------------------------------> Status:-------------------------> Timer

Level3					   CD:->Line:->Bluetooth:->Line2:->Back  Supply volt1->Supply volt2->Back   Total time->Time today->Back

Level4

*/

class config_menu:
	public Controller
{
//variables
public:
protected:
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



private:
	config_menu( const config_menu &c );
	config_menu& operator=( const config_menu &c );
	uint8_t  menu_pos[];	
}; //config_menu

#endif //__CONFIG_MENU_H__
