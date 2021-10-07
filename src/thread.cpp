/*
 * thread.cpp
 *
 *  Created on: Sep 11, 2021
 *      Author: OS1
 */

#include "thread.h"
#include "pcb.h"
#include "SCHEDULE.H"


//LISTA SVIH POKRENUTIH PROCESA

ListPCB* globalList = new ListPCB();



Thread::Thread(StackSize stackSize ,Time timeSlice){
	Timer::lock();
	myPCB = new PCB(this, stackSize,timeSlice);
	((ListPCB*)(PCB::globalList))->append(myPCB);
	Timer::unlock();
}

void Thread::start(){
	 //PROVERA DA SE NE POZOVE ZA ISTU NIT DVA PUTA START JER JE TO ONDA NEMOGUCE! START MOZE DA SE POZOVE SAMO PRE NEGO STO PREDJE U STANJE READY
	 Timer::lock();
	 if(myPCB->state == INITIALIZING){
	 myPCB->state = READY;
	 Scheduler::put(myPCB);
	 }
	 Timer::unlock();
}


Thread::~Thread(){
	delete myPCB;
	myPCB = 0;
}

ID Thread::getId(){
	return myPCB->getId();
}

ID Thread::getRunningId(){
	return PCB::getRunningId();
}

Thread* Thread::getThreadById(ID id){
	return PCB::getThreadById(id);
}


void dispatch (){
	Timer::dispatch();
}

void Thread::waitToComplete(){
	myPCB->waitToComplete();
}


