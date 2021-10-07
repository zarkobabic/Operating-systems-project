/*
 * pcb.cpp
 *
 *  Created on: Sep 11, 2021
 *      Author: OS1
 */

#include "thread.h"
#include "pcb.h"
#include "idle.h"


////////////INICIJALIZACIJA STATICKIH GLOBALNIH PPROMENLJIVIH /////////

ID PCB::IDD = 0;
volatile PCB* PCB::running = 0;
volatile ListPCB* PCB::globalList = new ListPCB();

////////////////////////////////////////////////////////////////////////



PCB::PCB(Thread* mine, StackSize stackSize, Time timeSlice){

	 this->timeSlice = timeSlice;
	 id = ++IDD;
	 myThread = mine;
	 state = INITIALIZING;
	 waitingList = new ListPCB();
	 timeToWait = 0;
	 wakeWithSignal = 0;

	 //////////////////////INICIJALIZACIJA STEKA TEK NAPRAVLJENE NITI //////////////////////////////////

	 if(stackSize > (1<<16-1)){stackSize = 1<<16-1;}////MAX VELICINA STEKA 64KB(2^16)

	 stackSize = stackSize / sizeof(unsigned);
	 stack = new unsigned[stackSize];



	 //psw sa setovanim I - I bit je bit na poziciji 9
	 stack[stackSize - 1] = 0x200;


#ifndef BCC_BLOCK_IGNORE
    //CS pa IP na steku
	 stack[stackSize - 2] = FP_SEG(&wrapper);
	 stack[stackSize - 3] = FP_OFF(&wrapper);

    //inicijalizacija sp-a i ss-a kao pointer na steku iza napakovanih registara
    // ax(-4), bx(-5), cx(-6), dx(-7), es(-8), ds(-9), si(-10), di(-11), bp(-12)

	 sp = FP_OFF(stack + stackSize - 12);
	 ss = FP_SEG(stack + stackSize - 12);

    bp = sp;
#endif
}
/////////////////////////////////////////////////////////////////////////////////////////////////////


PCB::~PCB(){
		waitToComplete();
		Timer::lock();
		((ListPCB*)(PCB::globalList))->remove(getId());
		delete waitingList;
		delete stack;
		Timer::unlock();
}


//sama sebe||zavrsena||idle
void PCB::waitToComplete(){
	Timer::lock();
		if(PCB::running == this || state == TERMINATING || state == INITIALIZING){
			Timer::unlock();
			return;
		}
		PCB::running->state = SUSPENDED;
		waitingList->append((PCB*)PCB::running);

		Timer::unlock();
		dispatch();
}

Thread* PCB::getThreadById(ID id){
	return (((ListPCB*)(PCB::globalList))->get(id))->myThread;
}

ID PCB::getId(){
	return this->id;
}

ID PCB::getRunningId(){
	 return PCB::running->id;
}

void PCB::wrapper(){
		 PCB::running->myThread->run();
		 Timer::lock();
		 PCB::running->state = TERMINATING;
		 if(PCB::running->waitingList) PCB::running->waitingList->freeWaiting();
		 Timer::unlock();
		 dispatch();
}


void PCB::callIdle(){
	PCB::running = Timer::idle->myPCB;

}

Thread* PCB::inicMain(){
	Thread * _main = new Thread();
	PCB::running = _main->myPCB;
	PCB::running->state = RUNNABLE;
	return _main;
}

