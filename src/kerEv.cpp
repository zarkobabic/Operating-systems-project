/*
 * kerEv.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: OS1
 */
#include "kerEvent.h"
#include "pcb.h"
#include "SCHEDULE.H"

KernelEv::KernelEv(IVTNo ivtNo){
	value = 0;
	parent = (PCB*)PCB::running;
	number = ivtNo;
	myEntry = IVTEntry::getEntry(number);
	myEntry->myEvent = this;
	blocked=0;
}

KernelEv::~KernelEv(){
}


void KernelEv::wait(){
	Timer::lock();
	if(PCB::running == parent){
		if(value==0){
			parent->state = SUSPENDED;
			blocked=1;
			Timer::unlock();
			Timer::dispatch();

		}
		else{
			value=0;
			Timer::unlock();
		}
	}
	else Timer::unlock();
}


void KernelEv::signal(){
	Timer::lock();
	if(blocked){
		parent->state=READY;
		Scheduler::put(parent);
		blocked=0;
		Timer::unlock();
		Timer::dispatch();
	}
	else{
		value = 1;
		Timer::unlock();
		//Timer::dispatch();
	}
}


