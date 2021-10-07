/*
 * hello.cpp
 *
 *  Created on: Apr 1, 2015
 *      Author: OS1
 */

#include <iostream.h>
#include "pcb.h"
#include "thread.h"
#include "listPCB.h"
#include "timer.h"
#include "idle.h"
#include "semaphor.h"
#include "kerSem.h"
#include "global.h"
#include "declare.h"

//void tick(){}  //obrisati posle

/*
#include <DOS.H>
#include <STDIO.H>
#include <STDARG.H>

int syncPrintf(const char *format, ...)
{
	int res;
	va_list args;
	asm cli
		va_start(args, format);
	res = vprintf(format, args);
	va_end(args);
	asm sti
		return res;
}
*/



///////vvvvvvvvvvvvvvvvvvvvvvvvvvvvvv

//////^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^









int main(int argc, char* argv[])
{
	//Pre maina kad se os inicijalizuje
	Timer* t = new Timer();

	int ret;

	//////////////////




	Thread* maine = PCB::inicMain();
	ret = userMain(argc, argv);




	////Global::AllSem;
	//PCB::globalList;
	///////////////////////////////////////////////////////////
	//Posle main kad se rade oslobadjanje globalnih struktura//
    ///////////////////////////////////////////////////////////

	delete maine;
	delete t;


	return ret;
}


