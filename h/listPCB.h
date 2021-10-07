/*
 * listPCB.h
 *
 *  Created on: Sep 11, 2021
 *      Author: OS1
 */

#ifndef LISTPCB_H_
#define LISTPCB_H_
#include "pcb.h"
#include "elem.h"


class ListPCB{
public:
	Elem *head, *tail;
	ListPCB();
	~ListPCB();
	void append(PCB* el);
	void toBeggining(PCB *el);
	void remove(ID id);
	PCB* get(ID id);
	void freeWaiting();
	PCB* getFromBeggining();
	PCB* takefirst();


	//obrisi posle samo za testiranje
	void print();
};



#endif /* LISTPCB_H_ */
