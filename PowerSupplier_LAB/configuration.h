/*
 * configuration.h
 *
 * Created: 19.09.2018 22:25:21
 *  Author: Maciek
 */ 
#pragma once


//Project -> Toolchain -> AVR/GNU C Compiler -> Symbols
//Project -> Toolchain -> AVR/GNU C Compiler -> Symbols
//#define F_CPU 1000000UL
//#define F_CPU 4000000UL
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

extern char line1[];
extern char line2[];
extern char line3[];






#define HD44780_2_16 TRUE

//#define HD44780_4_20 TRUE




class Pin
{
	uint8_t pinNo;
	volatile uint8_t* portAddr;
	
public:
	Pin(uint8_t _pin, volatile uint8_t* _port):
		pinNo(_pin), portAddr(_port){};
		
	Pin & operator | (uint8_t)
	{
		
		return *this;	
	};
	Pin & operator & (uint8_t)
	{
		return *this;
	};
		
	void direction(bool dir)
	{
		//DDRX    //_SFR_IO8(0x01) has always address PORTx-1
		//value = 1 on given bit set as output 
		volatile uint8_t* ddr_addr = portAddr - 1;
		if(dir)
			*ddr_addr |= 1UL << pinNo;
		else
			*ddr_addr &= ~(1UL << pinNo);
	}
	
};


#ifdef HD44780_2_16

/*** For HD47740 2x16
*/
#define LCD_RS_DIR		DDRC
#define LCD_RS_PORT 	PORTC
#define LCD_RS			(1 << PC3)

#define C_LCD_RS        Pin(PC3, PORTC)

#define LCD_RW_DIR		DDRC
#define LCD_RW_PORT 	PORTC
#define LCD_RW			(1 << PC4)

#define C_LCD_RW        Pin(PC4, PORTC)

#define LCD_E_DIR		DDRC
#define LCD_E_PORT		PORTC
#define LCD_E			(1 << PC5)

#define C_LCD_E         Pin(PC5, PORTC)

#define LCD_DB4_DIR		DDRC
#define LCD_DB4_PORT	PORTC
#define LCD_DB4			(1 << PC6)

#define C_LCD_DB4       Pin(PC6, PORTC)

#define LCD_DB5_DIR		DDRC
#define LCD_DB5_PORT	PORTC
#define LCD_DB5			(1 << PC7)

#define C_LCD_DB5       Pin(PC7, PORTC)

#define LCD_DB6_DIR		DDRA
#define LCD_DB6_PORT	PORTA
#define LCD_DB6			(1 << PA6)

#define C_LCD_DB6       Pin(PA6, PORTA)

#define LCD_DB7_DIR		DDRA
#define LCD_DB7_PORT	PORTA
#define LCD_DB7			(1 << PA5)

#define C_LCD_DB7        Pin(PA5, &PORTA)

#define LINE_LEN		16

#endif

/**/

#ifdef HD44780_4_20


/**********************
* PC0 -> E
* PC1 -> RS
* PC2 -> D4
* PC3 -> D5
* PC4 -> D6
* PC5 -> D7
***************************/

#define LCD_RS_DIR		DDRC
#define LCD_RS_PORT 	PORTC
#define LCD_RS			(1 << PC1)

#define LCD_E_DIR		DDRC
#define LCD_E_PORT		PORTC
#define LCD_E			(1 << PC0)

#define LCD_DB4_DIR		DDRC
#define LCD_DB4_PORT	PORTC
#define LCD_DB4			(1 << PC2)

#define LCD_DB5_DIR		DDRC
#define LCD_DB5_PORT	PORTC
#define LCD_DB5			(1 << PC3)

#define LCD_DB6_DIR		DDRC
#define LCD_DB6_PORT	PORTC
#define LCD_DB6			(1 << PC4)

#define LCD_DB7_DIR		DDRC
#define LCD_DB7_PORT	PORTC
#define LCD_DB7			(1 << PC5)

#define LCD_RW_DIR		DDRC
#define LCD_RW_PORT 	PORTC
#define LCD_RW			(1 << PC6)

#define LINE_LEN		20

#endif

//Define PORT Direction PORTA 


/*
//Functios to configure PORTs
void PORTA_Conf(char ddra, char pina);
void PORTB_Conf(char ddrb, char pinb);
void TIMSK_conf(short timsk);

void set_pin(char direction, char pin);
*/


void initialise();

void lcd_initialise();
#endif /* CONFIGURATION_H_ */
