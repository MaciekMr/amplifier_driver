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


class lcd: public fasade
{
private:
	char lcdline[lines_number][line_lenght]; // define th lcd size
	void init();
static lcd* pointer;
public:
	lcd();
	void refresh();	
	void update(int_fast8_t dir);
	void draw_all();
static lcd* get_object();
};



#endif /* LCD_H_ */