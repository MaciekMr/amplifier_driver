/*
 * lcd.h
 *
 * Created: 29.01.2022 19:47:21
 *  Author: maciek
 */ 


#ifndef LCD_H_
#define LCD_H_

#define line_lenght 16
#define lines_number 2

struct state_screen
{
	state_e  state;
	char  lines[lines_number][line_lenght];
};


class lcd: public fasade
{
private:
	bool isupdated;
	char lcdline[lines_number][line_lenght]; // define th lcd size
	void init();
static lcd* pointer;
public:
	lcd();
	void refresh();	
	void update(int_fast8_t dir);
	void draw_all();
	void change_state(state_main new_state);
static lcd* get_object();

//Methods to process states
public:
	void welcome(state_main state); 
};



#endif /* LCD_H_ */