/*
 * interrupts.h
 *
 * Created: 29.01.2022 12:25:05
 *  Author: macie
 */ 


#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_


void configure();
void add_object(void *);
void update_all(); //call method update for each object
void externall_call();
void interrupt_configure();

class object_list
{
protected:
	void* objects[10];  //list of all objects with fasade template
	uint8_t object_counter;
	static object_list* pointer;
public:
	object_list();
	void add_object(void*);
	void call_int(); //call interrupt method of object
	
	static object_list* get_object();
friend void externall_call();
friend void interrupt_configure();
};

#endif /* INTERRUPTS_H_ */