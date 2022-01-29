/*
 * configuration.c
 *
 * Created: 30.09.2018 17:08:23
 *  Author: Maciek
 */ 

//#include "port.h"
#include "configuration.h"

//using namespace nm_DS1267;

char line1[20] = "Hello LCD          ";
//char line2[20] = "Dzien dobry        ";
char line2[20] = "                   ";
char line3[20] = "Inter--------------";



/*

void PORTA_Conf(char ddra, char pina)
{
	DDRA |= (1<<ddra);
	PINA |= (1<<pina);	
}

void PORTB_Conf(char ddrb, char pinb)
{
	DDRB |= (1<<ddrb);
	PINB |= (1<<pinb);
}

void TIMSK_conf(short timsk)
{
	TIMSK |= (1<<timsk);
}

void set_pin(char direction, char pin)
{
	if(direction)
		DDRB != (1<<DDB3);
	else
		DDRB != (0<<DDB3);		
	PINB &= (0<<pin);
	
}

*/
void initialise(){
	//set the bit JTD in MCUCR
	//To disable JTD programmig and enable PC5:2 port to communication
	//asm{
	//	ORI MCUCR, 0x0F;
	//}
	
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);
	MCUCR |= (1<<JTD);
	
	//C_LCD_DB7.operator |(1);
	
	//Pin pA(PINA0, &PORTA);
}
/*
void lcd_initialise(){
	
	
	* RS -> PC1
	* E  -> PC0
	* RW -> 
	* D4 -> PC2
	* D5 -> PC3
	* D6 -> PC4
	* D7 -> PC5
	
	pin_port lcd_rs(DDRC, PORTC, PINC, PINC1);
	pin_port lcd_e(DDRC, PORTC, PINC, PINC1);
	pin_port lcd_d4(DDRC, PORTC, PINC, PINC1);
	pin_port lcd_d5(DDRC, PORTC, PINC, PINC1);
	pin_port lcd_d6(DDRC, PORTC, PINC, PINC1);
	pin_port lcd_d7(DDRC, PORTC, PINC, PINC1);
}
*/