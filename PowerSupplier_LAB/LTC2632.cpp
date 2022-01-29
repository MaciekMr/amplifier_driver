/* 
* LTC2632.cpp
*
* Created: 07.11.2021 01:07:13
* Author: macie
*/

#include <avr/io.h>
#include "LTC2632.h"

// default constructor
LTC2632::LTC2632()
{
	//Initiate PIN for CS
	DDRD = (1<<CHIP_SELECT); // set as output pin
} //LTC2632

// default destructor
LTC2632::~LTC2632()
{
} //~LTC2632
