/*
 * AmpDriver.cpp
 *
 * Created: 18.01.2019 20:21:23
 * Author : macie
 */ 

#define F_CPU 8000000UL //after update the fuses http://www.engbedded.com/fusecalc/


#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "port.h"
#include "configuration.h"
#include "interrupts.h"
#include "HD44780.h"
#include "DS1267.h"
#include "DG409.h"
#include "encoder.h"
#include "clock.h"
#include "LCD.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

using namespace nm_DS1267;
using namespace nm_DG409;
using namespace nm_encoder;


extern volatile long sec;
extern volatile long reaction;
extern volatile long seconds;

int day = 0,hrs = 0, min = 0, secs = 0, msecs = 0;

char up[5] = "UP  ";
char dw[5] = "DOWN";

//Configuration PIN for DS1267
pin_port u1(DDRA, PORTA, PINA, PINA0);
pin_port u2(DDRA, PORTA, PINA, PINA1);
pin_port u3(DDRA, PORTA, PINA, PINA2);

ds1267Port control(u1,u2,u3);
//End of configuration for DS1267

pin_port u4(DDRA, PORTA, PINA, PINA3);
pin_port u5(DDRA, PORTA, PINA, PINA4);

DG409 dg409(u4,u5);


/*
TIMER0_COMPA
TCMT0
OCR0A
OCR0B
TIFR0
TIMSK0
TCCR0B


f = fclc/(2*N*(1+OCR0A)) - N prescaller
*/


char * build_clock(int sec, int msec){
	
	//10 chars buffers
	int size = 14, len = 0, pos;
	char buff[size];
	char tmp[2];
	
	
	
	msecs = msec;
	
	if(sec == 60){
		
	    min++;
		sec = 0;
	}
	
	if(min == 60){
		
		hrs++;
		min = 0;
	}
	
	if(hrs == 24){
		
		day++;
		hrs = 0;
	}
	
	
	//00:00:00:00:0
	
	itoa(msecs, tmp, 10);
	len = strlen(tmp);
	pos = size - len;
	strncpy(tmp, &buff[pos], len);
	strncpy(":", &buff[--pos], 1);
	
	//seconds
	itoa(sec, tmp, 10);
	len = strlen(tmp);
	pos -= len;
	strncpy(tmp, &buff[pos], len);
	if(sec < 10)
		strncpy("0", &buff[--pos], 1);
	strncpy(":", &buff[--pos], 1);
	
	//minutes
	itoa(min, tmp, 10);
	len = strlen(tmp);
	pos -= len;
	strncpy(tmp, &buff[pos], len);
	if(min < 10)
	strncpy("0", &buff[--pos], 1);
	strncpy(":", &buff[--pos], 1);
	
	//hours
	itoa(hrs, tmp, 10);
	len = strlen(tmp);
	pos -= len;
	strncpy(tmp, &buff[pos], len);
	if(hrs < 10)
	strncpy("0", &buff[--pos], 1);
	strncpy(":", &buff[--pos], 1);
	
	//days
	itoa(day, tmp, 10);
	len = strlen(tmp);
	pos -= len;
	strncpy(tmp, &buff[pos], len);
	
	
	return(buff);
	
}


int main(void)
{
    /* Replace with your application code */
	//seconds = 0;
	
	LCD lcd;
	
	initialise();
	_delay_ms(20);
	
	LCD_Initalize();
	LCD_Clear();
	LCD_Home();
	
	
	//int a=0;
	//a = 1 << PA5;
	
	
	
	lcd.set_line(0, line1);
	lcd.set_line(1, line2);
	lcd.set_line(2, line3);
	//_delay_ms(3000);
	
	
	
	clock clock_;
	
	volatile uc state = 0, state1 = 0;
	/*
	DDRC  |= 0xFF;
	PORTC |= 0xFF;
	
	DDRA  |= 0xFF;
	PORTA |= 0xFF;
	
	DDRB  |= 0xFF;
	PORTB |= 0xFF;
	
	DDRD  |= 0xFF;
	PORTD |= 0xFF;
	*/
	
	//Initialise encoder
	pin_port encoder_sw(DDRB,PORTB, PINB, PINB1);
	pin_port encoder_a(DDRB,PORTB, PINB, PINB2);
	pin_port encoder_b(DDRB,PORTB, PINB, PINB3);
		
	encoder_sw.setMode(0);
	encoder_a.setMode(0);
	encoder_b.setMode(0);
		
	encoder enc(encoder_sw, encoder_a, encoder_b);
	
	//Enable interrupts
	timer_initialise();
	set_encoder_timer();
	//Set encoder pins 
	//PA5 - encoder right
	//PA6 - encoder left
	//PA7 - encoder button
	

	
	sei();
	char line[20] ="                   ";
	char line4[20]="Encoder:           ";
	
	//Set internal clock
	//http://www.engbedded.com/fusecalc?P_PREV=ATmega103&P=ATmega163&O_PARTSEL=Select&M_LOW_0x03=0x01&M_LOW_0x08=0x00&M_LOW_0x20=0x00&O_FEAT=Apply+feature+settings&B_SUT1=P&B_SUT0=P&B_CKSEL3=P&B_CKSEL2=P&B_CKSEL1=P&O_BITS=Apply+manual+fuse+bit+settings&V_LOW=C1&V_HIGH=D9&V_EXTENDED=FF&O_HEX=Apply+values&O_DEFAULT=Defaults
	//https://www.elecrom.com/configuring-avr-fuse-bits-for-clock-selection/
	// Set the fuses
	//memset(line, 32, 20);
	
	encoder *en = encoder::get_encoder();
	
		
    while (1) 
    {
		
		//Write the sec val to LCD
		//memset(line, 0x20, 20);
		//strcpy(line, line3); //copied 10 chars	
		/* Insert nop for synchronization*/ 
		//__no_operation(); 
		
		/* Read port pins */ 
		//portb = PINB; 
		//itoa(portb, &line1[12],4);
		
		//state = encoder_sw.getValue();
		
		state = (PINB >> PINB1) & 1U;
		state1 = encoder_sw.getValue();
		
		if(state){ //true
			itoa(1, &line1[12],10);
			itoa(state1, &line1[16],10);
		}else{
			itoa(0, &line1[12],10);
			itoa(state1, &line1[16],10);
		}
		lcd.set_line(0,line1);
		//LCD_GoTo(0,0);
		//LCD_WriteText(line1);
		
		//lcd.set_line(1, "                   ");
		//memset(&line2[0],32,20);
		
		//len = itoa(en->get_encoder_value(), &line2[0], 10);
		//lcd.set_line(1, line2, 2);
		
		lcd.set_line(1, en->get_encoder_value());
		//lcd.set_line(1, "              ", strlen(len)+1);
		//itoa(encoder_sw.get_port_reg(), &line2[4], 10);
		//itoa(encoder_sw.get_pinx_reg(), &line2[8], 10);
		//itoa(encoder_sw.get_pin_pos(), &line2[12], 10);
		//LCD_GoTo(0,1);
		//LCD_WriteText(line2);
		
		strncpy(&line[6], clock_.get_watch(seconds,sec), 12);
		//strncpy(clock_.get_watch(seconds,sec),&line[18],2);
		
		
		//memset(&line4[8], 0x20, 12);
		//itoa(reaction, &line4[10],10);
		
		//Set the line value based on SW of encoder
		
		if(en->get_state(0))
			strncpy(&line4[8], up, 4);
		else
			strncpy(&line4[8], dw, 4);
		
		itoa(en->get_state(), &line4[12], 6);
		
		lcd.set_line(2, line);
		lcd.set_line(3, line4);
		//LCD_GoTo(0,2);
		//LCD_WriteText(line);
		//LCD_GoTo(0,3);
		//LCD_WriteText(line4);		
    }
}

