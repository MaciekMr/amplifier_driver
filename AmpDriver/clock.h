/* 
* clock.h
*
* Created: 25.02.2020 22:41:28
* Author: Maciek
*/
#include <string.h>
#include <stdio.h>
#include "string_c.h"

using namespace std;
using namespace string_;



#ifndef __CLOCK_H__
#define __CLOCK_H__


class clock
{
//variables
public:
protected:
private:
	int days;
	int hours;
	int minutes;
	int seconds;
	int d_secs;

	string_c watch;
//functions
public:
	clock();
	~clock();
	clock(int sec, int msec);
	char* get_watch(int sec, int ms);
protected:
	
private:
	clock( const clock &c );
	clock& operator=( const clock &c );
	void build_clock_from_sec(int sec, int ms);
}; //clock



#endif //__CLOCK_H__







