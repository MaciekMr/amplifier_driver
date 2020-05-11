/*
 * DG409.h
 *
 * Created: 19.01.2019 23:11:22
 *  Author: macie
 */ 

#ifndef DG409_H_
#define DG409_H_

#include <string.h>
#include "list.h"

namespace nm_DG409{

#define name_len 8

using namespace nm_list;
using namespace nm_DS1267;	


	struct uc_address{
	public:
		pin_port line1;
		pin_port line2;
	};


	class record{
	public:	
		uc		address_config; //00,01,10,11 - the input will be changed like 00<->01<->10<->11<->00<->....
		char	input_name[name_len]; //Max input name len = 8 chars 
	};

	class DG409{
		
	private:
		//list< node<record> >	input_list;
		record			input_list[4];
		uc_address		dg409_config;
	protected:
		void changeInput();
		
	public:
		DG409(const pin_port &, const pin_port &);
		~DG409();
		void	nextInput();
		void	prevInput();
		char *	getInputName();
		
	};
	
}







#endif /* DG409_H_ */