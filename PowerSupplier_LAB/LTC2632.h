/* 
* LTC2632.h
*
* Created: 07.11.2021 01:07:13
* Author: macie
*/

#include "stdint.h"

#ifndef __LTC2632_H__
#define __LTC2632_H__

#define CHIP_SELECT   PIND5

typedef unsigned char uc;




/*
Table 1. Command Codes
COMMAND*
C3 C2 C1 C0
0 0 0 0 Write to Input Register n
0 0 0 1 Update (Power-Up) DAC Register n
0 0 1 0 Write to Input Register n, Update (Power-Up) All
0 0 1 1 Write to and Update (Power-Up) DAC Register n
0 1 0 0 Power-Down n
0 1 0 1 Power-Down Chip (All DAC’s and Reference)
0 1 1 0 Select Internal Reference (Power-Up Reference)
0 1 1 1 Select External Reference (Power-Down Internal
Reference)
1 1 1 1 No Operation
*Command codes not shown are reserved and should not be used.
Table 2. Address Codes
ADDRESS (n)*
A3 A2 A1 A0
0 0 0 0 DAC A
0 0 0 1 DAC B
1 1 1 1 All DACs
* Address codes not shown are reserved and should not be used.

System has to send 24 bits  = 3 bytes

4 bits - command C3 C2 C1 C0
4 bits - address A3 A2 A1 A0
12 bits - data A11...A0
4 bits - allignment - not important

so the sequence:
Set voltage - DACA
011000000000000000000000 -> set internal reference
00000000xxxxxxxxxxxx0000 -> xxxx - value from 0 -> 1024
00010000xxxxxxxxxxxx0000 -> Update DACA value

Set the Ilim - DACB
011000010000000000000000 -> set internal reference
00000001xxxxxxxxxxxx0000 -> xxxx - value from 0 -> 1024
00010001xxxxxxxxxxxx0000 -> Update DACA value

caclulate the value 
DACA
2 last bytes
16 bits
0x0000
0x0010
0x0020
...
0x0FFF0
*/



struct serial_data
{
	uc command; //4-bits (MSB of byte)
	uc address; //4-bits LSB  (need to be cobine into 1 byte)
	uint16_t data; //12-bits data (MSB) + 4 any bits
	
	uc command_address = (command << 4)|(address);
};

class LTC2632
{
//variables
public:
protected:

private:

//functions
public:
	LTC2632();
	~LTC2632();
	void sendcommad();
protected:
private:
	LTC2632( const LTC2632 &c );
	LTC2632& operator=( const LTC2632 &c );

}; //LTC2632

#endif //__LTC2632_H__
