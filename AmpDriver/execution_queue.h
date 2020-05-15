/* 
* execution_queue.h
*
* Created: 14.05.2020 21:56:51
* Author: Maciek
*/


#ifndef __EXECUTION_QUEUE_H__
#define __EXECUTION_QUEUE_H__


class execution_queue
{
//variables
public:
protected:
private:

//functions
public:
	execution_queue();
	~execution_queue();
	
	void execute();
protected:
private:
	execution_queue( const execution_queue &c );
	execution_queue& operator=( const execution_queue &c );

}; //execution_queue

#endif //__EXECUTION_QUEUE_H__
