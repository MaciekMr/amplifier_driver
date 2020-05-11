/* 
* LCD.h
*
* Created: 08.05.2020 23:23:40
* Author: Maciek
*/

#define empty_line "                    "

#ifndef __LCD_H__
#define __LCD_H__


class LCD
{
//variables
public:
protected:
private:
	bool update[4]={false}; //per line
	uint8_t configuration; // 2 lines 16 chars or 4 lines 20 chars
	char  lines[4][20]; 
	char digit[20];
//functions
public:
	LCD();
	~LCD();
	void refresh();
	void set_line(uint8_t, const char *, uint8_t pos = 0);
	void set_line(uint8_t, int , uint8_t pos = 0);
protected:
private:
	LCD( const LCD &c );
	LCD& operator=( const LCD &c );
	void clear_line(uint8_t);
}; //LCD

#endif //__LCD_H__
