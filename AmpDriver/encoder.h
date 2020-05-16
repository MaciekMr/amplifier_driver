/*
 * encoder.h
 *
 * Created: 22.01.2019 23:36:26
 *  Author: macie
 */ 


#ifndef ENCODER_H_
#define ENCODER_H_

#define SCHMITT_NEG 1  //Used if inverting Schmitt gate is used

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
Encoder board can use schmitt trigger and negative schmitt trigger gate
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
	
	
	
	//Encoder has get two values
	// depends on the rotate (cw or ccw)
	// the values are present in opposite order
	// First, we need to assign pins to read encoder values
	// Both pins has to be set with pull-up
	
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
			static encoder * encoder_pointer;
			//static encoder* enc_tab[5];
			int16_t encoder_value;
			//Encoder port values to read
			uint8_t clicks;
			uint8_t direction;
			uint8_t en_state, en_temp_state;
			uint8_t sw_state, sw_tmp_state;
			//Here the encoder is reading and increasing/decreasing value based on logic
		public:
			//encoder(pin_port SW, pin_port A, pin_port B);
			encoder();
			~encoder();
			
			void read_encoder();
			void read_switch();
			uint16_t get_encoder_value();
						
			//Here we adding new encoder preconfigured to be able to use by timer interruption		
			static void add_encoder(encoder *);
			static encoder * get_encoder();
			void set_encoder_val();
			//bool get_sw_state(); // if high -> true, low -> false
		
			void set_method();
			//inline
			uc get_encoder_state();
			uc get_button_state();
			uc get_clicks();
			
			void increment_val();
			void decrement_val();
			void sw_change_down();
			void sw_change_up();
			void sw_down();
			
		};
}

#endif /* ENCODER_H_ */