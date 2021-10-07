/*
 * kerSem.cpp
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */


#include "kerSem.h"
#include "listPCB.h"
#include "SCHEDULE.H"
#include "declare.h"
#include "global.h"

ID KernelSem::IDDD = 0;

KernelSem::KernelSem(Semaphore* s, int init){
	blocked = new ListPCB();
	timeBlocked = new ListPCB();
	mySem = s;
	value = init;
	id = ++IDDD;
}

KernelSem::~KernelSem(){
	delete blocked;
	delete timeBlocked;
	Global::AllSem->remove(id);
}

int KernelSem::wait(Time maxTimeToWait = 0){
	Timer::lock();
	if(--value < 0){
				PCB::running->timeToWait = maxTimeToWait;
				PCB::running->state = SUSPENDED;
				PCB::running->wakeWithSignal = 0;
				((ListPCB*)blocked)->append((PCB*)PCB::running);
				if(maxTimeToWait){
					((ListPCB*)timeBlocked)->append((PCB*)PCB::running);
				}
				Timer::unlock();
				Timer::dispatch();
	}
	else {Timer::unlock(); return 1;}
	return PCB::running->wakeWithSignal;
}

void KernelSem::signal(){

	Timer::lock();
	if(++value <= 0){
			PCB* deblocked = ((ListPCB*)blocked)->takefirst();
			ID idpom = deblocked->id;
			deblocked->state = READY;
			deblocked->wakeWithSignal = 1;
			((ListPCB*)blocked)->remove(idpom);
			if(deblocked->timeToWait != 0) ((ListPCB*)timeBlocked)->remove(idpom);
			deblocked->timeToWait = 0;
			Scheduler::put(deblocked);
		}
	Timer::unlock();
}

void KernelSem::incSem(){
	value = value + 1;
}

int KernelSem::val() const{
	return value;
}

ID KernelSem::getId(){
	return id;
}


