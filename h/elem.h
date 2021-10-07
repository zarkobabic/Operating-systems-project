/*
 * elem.h
 *
 *  Created on: Sep 11, 2021
 *      Author: OS1
 */

#ifndef ELEM_H_
#define ELEM_H_

class Elem{
public:
	PCB* info;
	Elem* next;
	Elem(){
		info = 0;
		next = 0;
	}
};

#endif /* ELEM_H_ */
