

#define register_len 17

#include "port.h"

namespace nm_DS1267{
	
	class ds1267Port{
	
	public:
		pin_port pin1; //rst
		pin_port pin2; //clk
		pin_port pin3; //dq
		pin_port pin4; //cout - used to read the value, optional
	
		ds1267Port(pin_port p1, pin_port p2, pin_port p3);
		
	};


	class DS1267{

		protected:
		
		ds1267Port	ds_port;
		uc			uC_id;
		uc			volA_state;
		uc			volB_state;
		int	ds_register; //register has 17 bits (3 bytes)
		
		bool		writeData();
		void		buildregister();
		
	public:
		DS1267(ds1267Port ds);
		~DS1267();
		
		int readVol();
		bool writeVol();
		
		int getVol(int); //0 - get volA, 1 - get volB
		
		void resetuC();
		
		void downVol();
		
		bool incVol(uc , int val = 1); //0 - volA, 1 - volB, 2 - VolA&B; val - value to incr
		bool decVol(int );
		
	};
	
	
}

