/*
 * list.h
 *
 * Created: 19.01.2019 23:25:18
 *  Author: macie
 */ 


#ifndef LIST_H_
#define LIST_H_

#include <stddef.h>
#include <stdlib.h>
#include <alloca.h>



#ifndef nullptr
	#define nullptr NULL
#endif

#define buffer_len 20

namespace nm_list {


	template <class T>
	class node {

		public:
		T data;
		node<T>* next;
		node<T>* prev;
	};


	template <class T>
	class list {

		private:
		T**        list_internal;
		size_t     size;
		T*         current;
		int		   block_num;
		public:
		list() {
			list_internal	= nullptr;
			current			= nullptr;
			size			= 0;
			block_num		= 1;

			//list_internal = new T*[buffer_len];
			list_internal =  (T**) alloca( sizeof(T*) *buffer_len);
		}

		~list() {
			//remove all elements one by one
			T* pos = list_internal[--size];
			
			while ((pos = pos->prev)){
				
				free(pos->next);
				//delete(pos->next);
			}
			free(list_internal);
			//delete(list_internal);
			
		}
		//TODO: add reallocation
		bool add(T element) {

			if (size == 20)
			return false;
			
			//list_internal[size] = new T;
			list_internal[size] = alloca(sizeof(T));
			*list_internal[size] = element;
			
			if (current != nullptr) {

				list_internal[size]->prev = current;
				current->next = list_internal[size];
				list_internal[size]->next = nullptr;
			}
			else {
				
				list_internal[size]->prev = nullptr;
				list_internal[size]->next = nullptr;
			}
			current = list_internal[size];
			size++;

			return true;
		}
		
		size_t getLenght() {

			return size;
		}

		T* getCurrent() {

			return current;
		}

		T* getNext() {

			if (current->next == nullptr)
			return nullptr;
			else
			return(current = current->next);
		}

		T* getPrev() {
			
			if (current->prev == nullptr)
			return nullptr;
			else
			return(current = current->prev);
		}
	};

};



#endif /* LIST_H_ */