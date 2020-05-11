/* 
* string_c.h
*
* Created: 25.02.2020 23:05:01
* Author: Maciek
*/


#ifndef __STRING_C_H__
#define __STRING_C_H__


namespace string_{

#define max_len 40

	class string_c
	{
		//variables
	public:
	protected:
		int size;
		char str_buffer[max_len];
		unsigned int lenght;
	private:

		//functions
	public:
		string_c();
		string_c(int size);
		string_c(char* text);
		~string_c();
		unsigned int get_lenght();
		string_c& operator + (const string_c &);
		string_c& operator=(const string_c& c);
		string_c& operator += (const string_c&);
		string_c& operator + (const int &);
		const char * getcontent();
		void clear();
	protected:

	private:
		string_c(const string_c& c);



	}; //string_c

}

#endif //__STRING_C_H__
