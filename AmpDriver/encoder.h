/*
 * encoder.h
 *
 * Created: 22.01.2019 23:36:26
 *  Author: macie
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#define MAX_ENCODER_VAL 512


ISR(TIMER0_COMPB_vect);
void set_encoder_timer();


using namespace nm_DS1267;

namespace nm_encoder{
	
#define ENC_DATA_REG DDRB
#define ENC_PORT	 PINB
	
#define ENC_PORT_SW	 PINB1
#define ENC_PORT_A	 PINB2
#define ENC_PORT_B	 PINB3

/*
Encoder board can use shmitt trigger and schmitt trigger with not gate
The second case we need to check negative code of the encoder
To make the reading simpler
We read the direction
and second read when both pins are got the same state (mid state)
*/

	//first A than B
	#define enc_0  (uint8_t)0x00
	#define enc_1  (uint8_t)0x01
	#define enc_2  (uint8_t)0x02
	#define enc_3  (uint8_t)0x03
	
	
	
	//Encoder has two values
	// depends on the rotate (left-right)
	// the values has present in opposite order
	// First, we need to assign pins to read encoder values
	// Both pins has to be set with pull-up
	struct encoder_conf{
		
		pin_port	encoder_A;
		pin_port	encoder_B;	
		pin_port	encoder_SW;		
		
		};
	
	//Set the timer interrupt which will read the encoder
	// will read the data from pins
	
	//SREG register to enable global interrupts (bit 7)
	
	// GIMSK - not set for timer interrupt
	
	// TIMSK - bit 6 is set the OCIE1A interrupt, Overflow interrupt can be set 
	
	//TIFR - bits 6 and 5 are set when OCIE1(A|B) is happened
	
	//The timer can be prescalled  http://ww1.microchip.com/downloads/en/DeviceDoc/doc1477.pdf
	
	//TCCR0 - 
	
	//TCNT0
	
	//TCCR1A
	
	//TCCR1B
	
	//TCNT1
	
	//OCR1A
	
	//OCR1B
	
	//OCR1C
	
	class encoder{
		
		protected:
			encoder_conf config;
			static encoder * encoder_pointer;
			//static encoder* enc_tab[5];
			int16_t encoder_value;
			//Encoder port values to read
			uint8_t	output_a, temp_out_a;
			uint8_t	output_b, temp_out_b;
			bool stable_port_sw;
			
			uint8_t direction;
			uint8_t _state, _temp_state;
			
			
		public:
			encoder(pin_port SW, pin_port A, pin_port B);
			~encoder();
			uint16_t get_encoder_value();
			//Here the encoder is reading and increasing/decreasing value based on logic
			void read_encoder();
				
			//Here we adding new encoder preconfigured to be able to use by timer interruption		
			static void add_encoder(encoder *);
			static encoder * get_encoder();
			void set_encoder_val();
			bool get_sw_state(); // if high -> true, low -> false
		
			void set_method();
			
			uc get_state(uc pin); //0 - sw, 1 - A, 2 - B 
			
			uc get_cencoder_state();
			
			uc get_button_state();
			
			uc get_state();
		};
	
	
	
	
	
	
}




#endif /* ENCODER_H_ */