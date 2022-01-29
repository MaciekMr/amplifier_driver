//-------------------------------------------------------------------------------------------------
// Wyœwietlacz alfanumeryczny ze sterownikiem HD44780
// Sterowanie w trybie 4-bitowym bez odczytu flagi zajêtoœci
// z dowolnym przypisaniem sygna³ów steruj¹cych
// Plik : HD44780.c	
// Mikrokontroler : Atmel AVR
// Kompilator : avr-gcc
// Autor : Rados³aw Kwiecieñ
// ród³o : http://radzio.dxp.pl/hd44780/
// Data : 24.03.2007
//-------------------------------------------------------------------------------------------------


//#include "port.h"
#include "configuration.h"
#include "HD44780.h"

//using namespace nm_DS1267;

//-------------------------------------------------------------------------------------------------
//
// Funkcja wystawiaj¹ca pó³bajt na magistralê danych
//
//-------------------------------------------------------------------------------------------------

void _LCD_DataLine_Down()
{
	LCD_DB4_PORT  &= ~LCD_DB4;
	LCD_DB5_PORT  &= ~LCD_DB5;
	LCD_DB6_PORT  &= ~LCD_DB6;
	LCD_DB7_PORT  &= ~LCD_DB7;
}
//-------------------------------------------------------------------------------------------------
//
// Funkcja wystawiaj¹ca pó³bajt na magistralê danych
//
//-------------------------------------------------------------------------------------------------

	void _LCD_OutNibble(unsigned char nibbleToWrite)
	{
		if(nibbleToWrite & 0x01)
			LCD_DB4_PORT |= LCD_DB4;
		else
			LCD_DB4_PORT  &= ~LCD_DB4;

		if(nibbleToWrite & 0x02)
			LCD_DB5_PORT |= LCD_DB5;
		else
			LCD_DB5_PORT  &= ~LCD_DB5;

		if(nibbleToWrite & 0x04)
			LCD_DB6_PORT |= LCD_DB6;
		else
			LCD_DB6_PORT  &= ~LCD_DB6;

		if(nibbleToWrite & 0x08)
			LCD_DB7_PORT |= LCD_DB7;
		else
			LCD_DB7_PORT  &= ~LCD_DB7;
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Funkcja zapisu bajtu do wyœwietacza (bez rozró¿nienia instrukcja/dane).
	//
	//-------------------------------------------------------------------------------------------------
	void _LCD_Write(unsigned char dataToWrite)
	{
		LCD_E_PORT |= LCD_E; //Set line 'E' to '1'
		_LCD_OutNibble(dataToWrite >> 4);
		_delay_ms(0.3);
		LCD_E_PORT &= ~LCD_E; //Set line 'E' to '0'
		
		_LCD_DataLine_Down();
		LCD_E_PORT |= LCD_E;
		_LCD_OutNibble(dataToWrite);
		_delay_ms(0.3);
		LCD_E_PORT &= ~LCD_E; //Set line 'E' to low
		_delay_us(50);
		_LCD_DataLine_Down();
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Funkcja zapisu rozkazu do wyœwietlacza
	//
	//-------------------------------------------------------------------------------------------------
	void LCD_WriteCommand(unsigned char commandToWrite)
	{
		LCD_RS_PORT &= ~LCD_RS;  //set to low
		_LCD_Write(commandToWrite);
		_LCD_DataLine_Down();
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Funkcja zapisu danych do pamiêci wyœwietlacza
	//
	//-------------------------------------------------------------------------------------------------
	void LCD_WriteData(unsigned char dataToWrite)
	{
		LCD_RS_PORT |= LCD_RS; //set to high
		_LCD_Write(dataToWrite);
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Funkcja wyœwietlenia napisu na wyswietlaczu.
	//
	//-------------------------------------------------------------------------------------------------
	void LCD_WriteText(char * text)
	{
		while(*text)
		  LCD_WriteData(*text++);
		  
	}
	
	void LCD_WriteText(char * text, uint8_t len)
	{
		while(len--)
			LCD_WriteData(*text++);
		
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Funkcja ustawienia wspó³rzêdnych ekranowych
	//
	//-------------------------------------------------------------------------------------------------
	void LCD_GoTo(unsigned char x, unsigned char y)
	{
		/*
		* First line  0x00   00000000
		* Second line 0x40   01000000
		* Third line  0x14   00010100
		* Fourth line 0x54   01010100
		*/
		
		unsigned char addr = 0;
		
		switch(y){
			
			case 0: addr = 0x00; break;
			case 1: addr = 0x40; break;
			case 2: addr = 0x14; break;
			case 3: addr = 0x54; break;
		}
		
		LCD_WriteCommand(HD44780_DDRAM_SET | (x + addr));
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Funkcja czyszczenia ekranu wyœwietlacza.
	//
	//-------------------------------------------------------------------------------------------------
	void LCD_Clear(void)
	{
		LCD_WriteCommand(HD44780_CLEAR);
		_delay_ms(2);
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Funkcja przywrócenia pocz¹tkowych wspó³rzêdnych wyœwietlacza.
	//
	//-------------------------------------------------------------------------------------------------
	void LCD_Home(void)
	{
		LCD_WriteCommand(HD44780_HOME);
		_delay_ms(2);
	}
	//-------------------------------------------------------------------------------------------------
	//
	// Procedura inicjalizacji kontrolera HD44780.
	//
	//-------------------------------------------------------------------------------------------------
	void LCD_Initalize(void)
	{
		unsigned char i;
		LCD_DB4_DIR |= LCD_DB4; // Konfiguracja kierunku pracy wyprowadzeñ
		LCD_DB5_DIR |= LCD_DB5; //
		LCD_DB6_DIR |= LCD_DB6; //
		LCD_DB7_DIR |= LCD_DB7; //
		LCD_E_DIR 	|= LCD_E;   //
		LCD_RS_DIR 	|= LCD_RS;  //
		LCD_RW_DIR 	|= LCD_RW;  //
		_delay_ms(25); // oczekiwanie na ustalibizowanie siê napiecia zasilajacego
		//_delay_ms(15); // oczekiwanie na ustalibizowanie siê napiecia zasilajacego
		LCD_RS_PORT &= ~LCD_RS; // wyzerowanie linii RS
		LCD_E_PORT  &= ~LCD_E;  // wyzerowanie linii E
		LCD_RW_PORT &= ~LCD_RW;  // Set to write 

		for(i = 0; i < 3; i++) // trzykrotne powtórzenie bloku instrukcji
		{
		  LCD_E_PORT |= LCD_E; //  E = 1
		  _LCD_OutNibble(0x03); // tryb 8-bitowy
		  LCD_E_PORT &= ~LCD_E; // E = 0
		  _delay_ms(10); // czekaj 5ms
		  //_delay_ms(5); // czekaj 5ms
		}

		LCD_E_PORT |= LCD_E; // E = 1
		_LCD_OutNibble(0x02); // tryb 4-bitowy
		LCD_E_PORT &= ~LCD_E; // E = 0

		//_delay_ms(1); // czekaj 1ms 
		_delay_ms(5); // czekaj 1ms 
		//LCD_WriteCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 | HD44780_TWO_LINE | HD44780_4_BIT); // interfejs 4-bity, 2-linie, znak 5x7
		//LCD_WriteCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 |HD44780_FOUR_LINE | HD44780_4_BIT); 
		LCD_WriteCommand(HD44780_FUNCTION_SET | HD44780_FONT5x7 |HD44780_TWO_LINE | HD44780_4_BIT); 
		LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_OFF); // wy³¹czenie wyswietlacza
		LCD_WriteCommand(HD44780_CLEAR); // czyszczenie zawartosæi pamieci DDRAM
		
		//_delay_ms(2);
		_delay_ms(5);
		LCD_WriteCommand(HD44780_ENTRY_MODE | HD44780_EM_SHIFT_CURSOR | HD44780_EM_INCREMENT);// inkrementaja adresu i przesuwanie kursora
		LCD_WriteCommand(HD44780_DISPLAY_ONOFF | HD44780_DISPLAY_ON | HD44780_CURSOR_OFF | HD44780_CURSOR_NOBLINK); // w³¹cz LCD, bez kursora i mrugania
	}

	//-------------------------------------------------------------------------------------------------
	//
	// Koniec pliku HD44780.c
	//
	//-------------------------------------------------------------------------------------------------