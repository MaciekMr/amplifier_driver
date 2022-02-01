/*
 * input_poll.h
 *
 * Created: 30.01.2022 16:32:57
 *  Author: macie
 */ 


#ifndef INPUT_POLL_H_
#define INPUT_POLL_H_

//This class will register all objects, which will request the update based on input (like encoder, click,, etc.)
//All inputs has register here and actions 
//Each event has to modify the actual action
//System has to be statefull
//And event will change the state and trigger the action

/*
For power supply 3 states can be recognised
1. Welcome
2. Vset
3. Iset

1. Welcome screen - shown by 3 seconds
It will automatically switch to state 2.
When clicked by encoder it will moved to state 3.
When clicked once again -> back to state 2.

rotate encoder will change a value under giving state

*/

#define ENC1_SW_DOWN   0x01
#define ENC1_SW_UP     0x02
#define ENC1_SW_CHG    0x03
#define ENC1_IN_UP     0x04  //turn left
#define ENC1_IN_DOWN   0x04  //turn right

/*
state map

1. -> 2. -> 3. -> 2.

For each state there is different menu to show and specific control, like sending command to device and get current value to show on screen


*/



class input_poll
{
	
protected:
	uint8_t current_consumer;
	uint8_t states[30];  //all available states
	void* event_destinations[5][10]; //For each event max 10 consumers
static input_poll* pointer;
public:
	input_poll();
	//Source register event and receive source_id;
	void register_event(uint8_t guid, uint8_t event_id);
	void register_consumer(void *, uint8_t event_id);
	
	void set_event(uint8_t id, uint8_t event);

static input_poll* get_object();	
	
};



#endif /* INPUT_POLL_H_ */