/*
 * pcb.h
 *
 *  Created on: Sep 11, 2021
 *      Author: OS1
 */

#ifndef PCB_H_
#define PCB_H_

class ListPCB;
class ListKerSem;

#include <iostream.h>
#include <dos.h>
#include "thread.h"
#include "listPCB.h"
#include "timer.h"

#define INITIALIZING 1
#define READY 2
#define SUSPENDED 3
#define RUNNABLE 4
#define TERMINATING 5



class PCB{

public:

	//GLOBALNI PODACI
 static volatile ListPCB* globalList;
 static volatile PCB* running;
 	////////////////

 ListPCB* waitingList;
 volatile ID id;
 static ID IDD;
 volatile Time timeSlice;
 Thread* myThread;
 Time timeToWait;
 volatile unsigned wakeWithSignal;

 unsigned* stack;
 volatile unsigned sp;
 volatile unsigned ss;
 volatile unsigned bp;

  volatile unsigned state;

public:
 void waitToComplete();
 static void callIdle();
 ID getId();
 static ID getRunningId();
 static Thread * getThreadById(ID id);
 virtual ~PCB();
 static Thread* inicMain();

 static void wrapper();

protected:
 friend class Thread;
 friend class Timer;
 PCB(Thread* mine, StackSize stackSize, Time timeSlice);
};

#endif /* PCB_H_ */
