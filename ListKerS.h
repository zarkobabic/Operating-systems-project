/*
 * ListKerS.h
 *
 *  Created on: Sep 23, 2021
 *      Author: OS1
 */

#ifndef LISTKERS_H_
#define LISTKERS_H_

#include "node.h"
#include "kerSem.h"

class ListKerSem{
public:
	Node *head, *tail;
	ListKerSem();
	~ListKerSem();
	void append(KernelSem* el);
	void toBeggining(KernelSem* el);
	void remove(ID id);
	KernelSem* get(ID id);
	void freeIfDoneWaiting();
	void print();
};



#endif /* LISTKERS_H_ */
