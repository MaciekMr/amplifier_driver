/* 
* SPI_Master.cpp
*
* Created: 03.09.2020 20:00:12
* Author: Maciek
*/


#include "SPI_Master.h"
/*
SPCR 
     SPIE: SPI Interrupt Enable
	 SPE: SPI Enable
	 DORD: Data Order
	 MSTR: Master/Slave Select
	 CPOL: Clock Polarity
	 CPHA: Clock Phase
	 SPR1, SPR0: SPI Clock Rate Select 1 and 0

SPSR – SPI Status Register
     SPIF: SPI Interrupt Flag
	 WCOL: Write COLlision Flag
	 SPI2X: Double SPI Speed Bit
	 
SPDR – SPI Data Register

*/


// default constructor
SPI_Master::SPI_Master()
{
	
} //SPI_Master

// default destructor
SPI_Master::~SPI_Master()
{
} //~SPI_Master

void SPI_MasterInit(void)
{
	/* Set MOSI and SCK output, all others input */
	//DDR_SPI = (1<<DD_MOSI)|(1<<DD_SCK);
	/* Enable SPI, Master, set clock rate fck/16 */
	//SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0);
}
void SPI_MasterTransmit(char cData)
{
	/* Start transmission */
	//SPDR = cData;
	/* Wait for transmission complete */
	//while(!(SPSR & (1<<SPIF)))
	
}

void SPI_SlaveInit(void)
{
	/* Set MISO output, all others input */
	//DDR_SPI = (1<<DD_MISO);
	/* Enable SPI */
	//SPCR = (1<<SPE);
}
char SPI_SlaveReceive(void)
{
	/* Wait for reception complete */
	//while(!(SPSR & (1<<SPIF)))
	
	/* Return Data Register */
	//return SPDR;
}