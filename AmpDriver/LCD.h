/* 
* LCD.h
*
* Created: 08.05.2020 23:23:40
* Author: Maciek
*/

#define empty_line "                    "

#ifndef __LCD_H__
#define __LCD_H__

#define line_lenght 20
#define clean_line  "                    \0"


namespace LCD_DISPLAY {

	class LCD
	{
	//variables
	public:
	protected:
		static
		LCD* pointer;
	private:
		bool update[4]={false, false, false, false}; //per line
		uint8_t configuration; // 2 lines 16 chars or 4 lines 20 chars
		char  lines[4][line_lenght + 1]; 
		char digit[10];
	//functions
	public:
		LCD();
		~LCD();
		void refresh();
		void set_line(uint8_t, const char *, uint8_t pos = 0);
		void set_line(uint8_t, int , uint8_t pos = 0);
		static
		LCD* getlcd();
	protected:
	private:
		LCD( const LCD &c );
		LCD& operator=( const LCD &c );
		void clear_line(uint8_t, uint8_t, uint8_t pos = 0);
	}; //LCD
}
#endif //__LCD_H__
