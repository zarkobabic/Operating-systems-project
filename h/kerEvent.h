/*
 * kerEvent.h
 *
 *  Created on: Sep 23, 2021
 *      Author: OS1
 */

#ifndef KEREVENT_H_
#define KEREVENT_H_
#include "pcb.h"
#include "IVTEntry.h"


typedef unsigned char IVTNo;

class Event;
class IVTEntry;

class KernelEv{
public:
	KernelEv(IVTNo ivtNo);
	~KernelEv();
	void wait();

protected:
	friend class IVTEntry;
	friend class Event;
	void signal();

public:
	PCB* parent;
	IVTEntry* myEntry;
	IVTNo number;
	int value;
	int blocked;
};




#endif /* KEREVENT_H_ */
