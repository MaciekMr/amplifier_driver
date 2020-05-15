/* 
* Controller.h
*
* Created: 15.05.2020 18:43:04
* Author: Maciek
*/


#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__


class Controller
{
//functions
public:
	virtual ~Controller(){}
	virtual void increment() = 0;
	virtual void decrement() = 0;
	virtual void switch_change_down() = 0;
	virtual void switch_change_up() = 0;
	virtual void switch_down() = 0;

}; //Controller

#endif //__CONTROLLER_H__
