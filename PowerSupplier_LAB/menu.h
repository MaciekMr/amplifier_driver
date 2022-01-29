/*
 * menu.h
 *
 * Created: 29.01.2022 17:02:58
 *  Author: macie
 */ 


#ifndef MENU_H_
#define MENU_H_


#define line_1 "Vs=      V=     "
#define line_2 "Is=      I=     "

//For power supply menu is simple
/*

Vs=xxxxxx  V=xxxxxxx - we will be able to set only Vs (Vset) V    value like 10.05  
Is=xxxxxx  I=xxxxxxx - we will be able to set only Is (Iset) mA   value 3000 
*/

class menu: public fasade
{
protected:
	uint8_t  menu_position;	//the menu has a tree view, here is a 0 or 1 - 0->V 1->I
	char	 line[lines_number][line_lenght]; //text to display on screen, we have 2 lines
static menu* object;	
public:
	menu();
	void set_value(uint8_t line_no, float value);
	void set_value(uint8_t line_no, int value);
	char* get_line(uint8_t line_no);
	void update(int_fast8_t dir);
static menu* get_object();
};



#endif /* MENU_H_ */