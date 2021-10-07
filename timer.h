/*
 * timer.h
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */

#ifndef TIMER_H_
#define TIMER_H_

class Thread;
class Idle;
//thread i idle

class Timer{
public:
	Timer();
	~Timer();
	static void dispatch();
	static void lock();
	static void unlock();
	static volatile Idle* idle;
protected:
	void inic();
	void restore();
};


#endif /* TIMER_H_ */
