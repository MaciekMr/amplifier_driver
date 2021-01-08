/* 
* IDevice.h
*
* Created: 08.01.2021 17:18:31
* Author: macie
*/


#ifndef __IDEVICE_H__
#define __IDEVICE_H__


class IDevice
{
//functions
public:
	//virtual ~IDevice(){}
	virtual void setValue(int_fast8_t new_value, uint8_t id = 0) = 0;
	virtual int_fast8_t getValue() = 0;

}; //IDevice

#endif //__IDEVICE_H__
