/*
 * timer.cpp
 *
 *  Created on: Sep 19, 2021
 *      Author: OS1
 */


#include <iostream.h>
#include <dos.h>
#include "timer.h"
#include "pcb.h"
#include "SCHEDULE.H"
#include "idle.h"
#include "listKerS.h"
#include "global.h"


extern void tick();


unsigned volatile requested = 0;
unsigned volatile counter;
unsigned volatile tsp;
unsigned volatile tss;
unsigned volatile tbp;
unsigned volatile lockFlag = 1;

volatile Idle* Timer::idle = new Idle();

Timer::Timer(){
	inic();
}

Timer::~Timer(){
	restore();
	if(Timer::idle) delete Timer::idle;
}


unsigned volatile oldTimerOFF, oldTimerSEG; // stara prekidna rutina


void interrupt timer(){

	if (!requested) {

		tick();
		Global::AllSem->freeIfDoneWaiting();
		asm int 60h;
		if(PCB::running->timeSlice != 0){ //Timeslice 0 ima nit koja treba da se izvrsava beskonacno
			counter--;
		}
	}
	if (counter == 0 || requested) {
		if(lockFlag > 0){
			requested = 0;


			asm {
				// cuva sp
				mov tsp, sp
				mov tss, ss
				mov tbp, bp
			}

			PCB::running->sp = tsp;
			PCB::running->ss = tss;
			PCB::running->bp = tbp;







			if(PCB::running->state == RUNNABLE){ //
				PCB::running->state = READY;
				Scheduler::put((PCB*)PCB::running);
			}


			PCB::running= Scheduler::get();
			if(!PCB::running) PCB::callIdle();
			else PCB::running->state = RUNNABLE;


			tsp = PCB::running->sp;
			tss = PCB::running->ss;
			tbp = PCB::running->bp;


			counter = PCB::running->timeSlice;
			if(PCB::running->timeSlice == 0) counter = 1;

			asm {
				mov sp, tsp   // restore sp
				mov ss, tss
				mov bp, tbp;
			}
		}
		else requested = 1;
	}
}


void Timer::inic(){ // postavlja novu prekidnu rutinu
	asm{
			cli
			push es
			push ax

			mov ax,0   //  ; inicijalizuje rutinu za tajmer
			mov es,ax

			mov ax, word ptr es:0022h //; pamti staru rutinu
			mov word ptr oldTimerSEG, ax
			mov ax, word ptr es:0020h
			mov word ptr oldTimerOFF, ax

			mov word ptr es:0022h, seg timer	 //postavlja
			mov word ptr es:0020h, offset timer //novu rutinu

			mov ax, oldTimerSEG	 //	postavlja staru rutinu
			mov word ptr es:0182h, ax //; na int 60h
			mov ax, oldTimerOFF
			mov word ptr es:0180h, ax

			pop ax
			pop es
			sti
		}
}

void Timer::restore(){
	asm {
			cli
			push es
			push ax

			mov ax,0
			mov es,ax


			mov ax, word ptr oldTimerSEG
			mov word ptr es:0022h, ax
			mov ax, word ptr oldTimerOFF
			mov word ptr es:0020h, ax

			pop ax
			pop es
			sti
		}
}

void Timer::dispatch(){
	asm cli;
	requested = 1;
	timer();
	asm sti;
}

void Timer::lock(){
	lockFlag--;
}

void Timer::unlock(){
	lockFlag++;
	if(requested) dispatch();
}


