/*
 * port.h
 *
 * Created: 19.01.2019 23:13:24
 *  Author: macie
 */ 


#ifndef PORT_H_
#define PORT_H_

typedef unsigned char uc;

namespace nm_DS1267{

	class pin_port{
		public:
		 
		uc		ddrx;
		uc		portx;
		uc		pinx; //Register
		uc		pin;  //pin number 0-7
		protected:
		bool	port_mode;
	
		public:
		pin_port() {};
		pin_port(uc ,uc ,uc ,uc);
		pin_port(const pin_port &);
		void setMode(uc);
		//The configuration can be very specific. Every pin can be from different segment
		// ddrx select the segment and set in or out mode
		//portx enable the given port to R/W state (or disable)
		//pinx just select the pin to communication
		void setValue(bool);
		uc getValue();
		uc get_ddr_reg();
		uc get_port_reg();
		uc get_pinx_reg();
		uc get_pin_pos();
		
	};

}

#endif /* PORT_H_ */