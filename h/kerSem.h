/*
 * kerSem.h
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#ifndef KERSEM_H_
#define KERSEM_H_


#include "listPCB.h"
#include "semaphor.h"



class KernelSem{
public:
	KernelSem(Semaphore* s, int init = 1);
	virtual ~KernelSem();
	virtual int wait (Time maxTimeToWait);
	virtual void signal();

	ID getId();
	int val () const; // Returns the current value of the semaphore
	Semaphore* mySem;
	volatile ListPCB* blocked;
	volatile ListPCB* timeBlocked;
	void incSem();

	ID id;
private:
 	int value;
 	static ID IDDD;
};



#endif /* KERSEM_H_ */
