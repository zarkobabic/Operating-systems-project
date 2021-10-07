/*
 * idle.h
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */

#ifndef IDLE_H_
#define IDLE_H_
#include "thread.h"

class Idle:public Thread{
public:
	virtual void run();
	Idle();
};



#endif /* IDLE_H_ */
