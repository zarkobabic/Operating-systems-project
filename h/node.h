/*
 * node.h
 *
 *  Created on: Sep 22, 2021
 *      Author: OS1
 */

#ifndef NODE_H_
#define NODE_H_
#include "kerSem.h"

class Node{
public:
	KernelSem* info;
	Node* next;
	Node(){
		info = 0;
		next = 0;
	}
};



#endif /* NODE_H_ */
