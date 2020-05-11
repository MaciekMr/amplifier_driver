/* 
* clock.cpp
*
* Created: 25.02.2020 22:41:27
* Author: Maciek
*/



#include <string.h>
#include "clock.h"

// default constructor
clock::clock()
{
	seconds = minutes = hours = days = 0;
} //clock

// default destructor
clock::~clock()
{
} //~clock


clock::clock(int sec, int msec)
	:seconds(sec), d_secs(msec) {
	
	minutes = hours = days = 0;
}

void clock::build_clock_from_sec(int sec, int ms) {

	//1. Check if the second = 60
	watch.clear();
	d_secs = ms;
	seconds = sec - (minutes*60 + hours*60*60 + days*24*60*60);
	if (seconds && !(seconds % 60)) {
		minutes++;
		seconds = 0;
	}

	if (minutes && !(minutes % 60)) {
		hours++;
		minutes = 0;
	}

	if (hours && !(hours % 24)) {
		days++;
		hours = 0;
	}

	//watch = days + ':' + (hours < 10 ? (0 + hours) : hours) + ':' + (minutes < 10 ? (0 + minutes) : minutes) +  ':' + (seconds < 10 ? (0 + seconds) : seconds) + ':' + d_secs;
	watch = watch + days;
	watch = watch + ":";
	
	if(hours < 10)
		watch = watch + "0";
	watch = watch + hours;
	watch = watch + ":";
	
	//watch = watch + (minutes < 10 ? "0" : "1");
	if(minutes < 10)
		watch = watch + "0";
	watch = watch + minutes;
	watch = watch + ":";
	//watch = watch + (seconds < 10 ? "0" : "1");
	if(seconds < 10)
		watch = watch + "0";
	watch = watch + seconds;
	watch = watch + ":" + d_secs;

}

char* clock::get_watch(int sec, int ms) {

	build_clock_from_sec(sec, ms);
	return (char*) (watch.getcontent());
}