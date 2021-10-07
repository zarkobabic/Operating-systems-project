/*
 * event.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: OS1
 */
#include "event.h"
#include "kerEvent.h"
#include "timer.h"

Event::Event(IVTNo ivtNo){
	Timer::lock();
	myImpl = new KernelEv(ivtNo);
	Timer::unlock();
}

Event::~Event(){
	Timer::lock();
	delete myImpl;
	Timer::unlock();
}

void Event::wait(){
	myImpl->wait();
}

void Event::signal(){
	myImpl->signal();
}
