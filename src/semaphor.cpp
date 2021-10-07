/*
 * semaphor.cpp
 *
 *  Created on: Sep 21, 2021
 *      Author: OS1
 */

#include "semaphor.h"
#include "timer.h"
#include "kerSem.h"
#include "global.h"

Semaphore::Semaphore(int init){
	Timer::lock();
	myImpl = new KernelSem(this, init);
	Global::AllSem->append(myImpl);
	Timer::unlock();
}

Semaphore::~Semaphore(){
	Timer::lock();
	delete myImpl;
	Timer::unlock();
}

int Semaphore::wait(Time maxTimeToWait){
	return myImpl->wait(maxTimeToWait);
}

void Semaphore::signal(){
	myImpl->signal();
}

int Semaphore::val() const{
	return myImpl->val();
}






