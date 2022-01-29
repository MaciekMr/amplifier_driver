/*
 * PowerSupplier_LAB.cpp
 *
 * Created: 15.10.2021 00:11:20
 * Author : macie
 */ 


//#define F_CPU 8000000UL //after update the fuses http://www.engbedded.com/fusecalc/

#include <stdlib.h>
#include <avr/io.h>
#include "configuration.h"
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdio.h>
#include "avr/interrupt.h"
#include <string.h>
#include "interrupts.h"
#include "lcd.h"
#include "HD44780.h"


#define DDR_SPI DDRB
#define DD_MOSI PINB5
#define DD_SCK  PINB7

/*
void initialise(){
	//set the bit JTD in MCUCR
	//To disable JTD programmig and enable PC5:2 port to communication
	//asm{
	//	ORI MCUCR, 0x0F;
	//}
	
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);
}
*/

extern uint_fast16_t data;

void initialise_spi()
{
	/* Set MOSI and SCK output, all others input */
	DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	/* Enable SPI, Master, set clock rate fck/16 */
	SPCR0 = (1<<SPE0)|(1<<MSTR0)|(0<<SPR10)|(0<<SPR00)|(0<<CPOL0); //DORD0 - LSB or MSB, set as Master, SCK clock - fSCK/64 -> 8MHz/4 -> 2MHz
	SPSR0 = (1<<SPI2X0); //Double SPI speed clock x2 -> 4MHz
}

void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	SPDR0 = cData;
	/* Wait for transmission complete */
	while(!(SPSR0 & (1<<SPIF0)));
}
//port - point to PORT ID, like PORTB
// pin_no - point to the pin number like PINB5
void spi_write(volatile uint8_t *port, uint8_t pin_no, unsigned char numberOfBytes, unsigned char *byte)
{
	//CS = false;  //---set the CS to 0 - start transmission
	//Set the chip select pin to 0;
	//Get the current PORT value
	//uint8_t val = *port;
	//set the port to low
	*port ^= (1<<pin_no);
	while(numberOfBytes){
		SPI_MasterTransmit(*byte);
		byte++;
		numberOfBytes--;
	}
	//Revert chip select port to high
	//CS = true; //---set the CS to 1 - stop transmission
	*port ^= (1<<pin_no);
	
}
 
int main(void)
{
	char text1[LINE_LEN]; // = "Hello!!!!!";
	char text2[LINE_LEN]; // = "Hello!!!!!";
	memset(text1, 0, LINE_LEN);
	strncpy(text1, "Hello !!! World", 15);
	//memset(text2, 0, LINE_LEN);
	//strncpy(text2, "Welcome\\0", 7);
	//memset(&text, 0, 15);
	//strcpy(text = "Hello!!!!"
    //Replace with your application code
	initialise();
	_delay_ms(20);
	LCD_Initalize();
	LCD_Clear();
	LCD_Home();
	interrupt_configure();
	//LCD_GoTo(0,0);
	//LCD_WriteText(text1);
	//lcd_init();
	//lcd_clear();
	//lcd_on();
	//lcd_puts("Hello Home");
	
	
	
	//#define port_our PINA5
	
	//DDRA  ^= (-1 ^ DDRA) & (1UL << port_our); // set pin;
	//PORTA ^= (-0 ^ PORTA) & (1UL << port_our);
	
	char digit[5];
	
	memset(digit, 0, sizeof(char) * 5);
	
    while (1) 
    {
		
		LCD_GoTo(0,0);
	    LCD_WriteText(text1);
		_delay_ms(1);
		//LCD_GoTo(0,1);
		//LCD_WriteText(text2);
		//PORTA &= ~(1 << port_our); // PD0 goes low
		//_delay_ms(100);
		//PORTA |= (1 << port_our); // PD0 goes high
		//_delay_ms(100);
		
		//Set port DB4 - DB7 to high and low
		/*
		LCD_DB4_PORT &= ~(LCD_DB4);
		_delay_ms(100);
		LCD_DB4_PORT |= LCD_DB4;
		_delay_ms(10);
		*/
		itoa(data, digit, 10);
		LCD_GoTo(0,1);
		LCD_WriteText(digit);
		//data++;
    }
}


