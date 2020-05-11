/*
 * amplififer.h
 *
 * Created: 20.02.2019 00:49:20
 *  Author: macie
 */ 


#ifndef AMPLIFIFER_H_
#define AMPLIFIFER_H_

class amplifier{
	private:
		uint8_t		time_2_on; //seconds to start power
		uint8_t		volume_level; // always start from 0
		uint16_t	voltage[4]; //2 left and 2 right
	protected:
		bool power_up;
		void write_config();
	public:
		amplifier();
		~amplifier();
		void setTime(uint8_t);
		void increaseTime(uint8_t);
		uint8_t getTime2Start();
		void setVolume(uint8_t);
		void getVolume();
		
	};



#endif /* AMPLIFIFER_H_ */