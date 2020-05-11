/*
* string_c.cpp
*
* Created: 25.02.2020 23:05:01
* Author: Maciek
*/

#include <string.h>
#include "string_c.h"
#include <stdlib.h>


namespace string_{

	// default constructor
	string_c::string_c()
	{
		size = 0;
	} //string_c


	string_c::string_c(int size)
	:size(size)
	{
		//str_buffer = (char *)calloc(size, sizeof(char));
		memset(str_buffer, 0, size);
	} //string_c


	string_c::string_c(char* text) {

		size = strlen(text);
		//str_buffer = (char *)calloc(size, sizeof(char));;
		if(size > max_len)
			size = max_len;
		strncpy(str_buffer, text, size);
	} //string_c

	// default destructor
	string_c::~string_c()
	{
	  //delete(str_buffer);
	} //~string_c


	unsigned int string_c::get_lenght() {

		return size;
	}



	string_c& string_c::operator=(const string_c& c) {

		char len = c.size;
		if (len > max_len)
		len = max_len;
		strncpy(str_buffer, c.str_buffer, len); //copy text to buffer

		//remove this buffer
		//free(str_buffer);
		//create a new buffer
		//str_buffer = reinterpret_cast<char *>( calloc(c.size, sizeof(char)));
		//copy value to new buffer
		//strncpy(str_buffer, tmp_buff, c.size);
		//size = c.size;
		size = len;
		return(*this);
	}

	string_c& string_c::operator + (const string_c & inp) {

		//extend size of buffer for new characters

		int len = inp.size;

		//check the size of added string
		if(size + len > max_len)
			len = max_len - size;
	
	
		//add string
	
		strncpy(&str_buffer[size], inp.str_buffer, len);
	
		//char * tmp_buff;

		//tmp_buff = (char *) realloc(str_buffer, size + len);
	

		//if (tmp_buff) {

			//copy buffers
		//	strncpy(&tmp_buff[size], inp.str_buffer, inp.size);
		//}

		//delete buffer
		//free(str_buffer); -> not for realloc

		//str_buffer = tmp_buff;

		size += len;
	
		return(*this);
	}

	string_c& string_c::operator += (const string_c& c) {

		*this = *this + c;

		return (*this);
	}

	string_c& string_c::operator + (const int & digit) {

		char buff[4];

		itoa(digit, buff, 10);
	
		string_c c(buff);

		*this = *this + c;

		return (*this);
	}
	
	const char * string_c::getcontent(){
		
		return(str_buffer);
	}
	
	void string_c::clear() {

		memset(str_buffer, 0, max_len * sizeof(char));
		size = 0;
	}
}


