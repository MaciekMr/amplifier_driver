/*
 * configuration.h
 *
 * Created: 19.09.2018 22:25:21
 *  Author: Maciek
 */ 
#pragma once


//Project -> Toolchain -> AVR/GNU C Compiler -> Symbols
#define F_CPU 8000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#ifndef CONFIGURATION_H_
#define CONFIGURATION_H_

extern char line1[];
extern char line2[];
extern char line3[];

extern volatile long sec;

//#define F_CPU 



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
