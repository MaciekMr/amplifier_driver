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
	
	//Encoder has two values
	// depends on the rotate (left-right)
	// the values has present in opposite order
	// First, we need to assign pins to read encoder values
	// Both pins has to be set with pull-up
	struct encoder_conf{
		
		pin_port	encoder_A;
		pin_port	encoder_B;		
		
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
			static encoder* enc_tab[5];
			uint16_t encoder_value;
			//Encoder port values to read
			uint8_t	stable_port_a;
			int8_t	stable_port_b;
			//temporary values to read by timer
			int8_t	temp_port_a;
			int8_t	temp_port_b;
			
		public:
			encoder(pin_port A, pin_port B);
			~encoder();
			uint16_t get_encoder_value();
			//Here the encoder is reading and increasing/decreasing value based on logic
			void read_encoder();
				
			//Here we adding new encoder preconfigured to be able to use by timer interruption		
			static void add_encoder(encoder *);
			static encoder * get_encoder(uint8_t);
		
		};
	
	
	
	
	
	
}

#endif /* ENCODER_H_ */