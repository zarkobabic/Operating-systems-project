/*
 * declare.h
 *
 *  Created on: Sep 23, 2021
 *      Author: OS1
 */

#ifndef DECLARE_H_
#define DECLARE_H_

int syncPrintf(const char *format, ...);
int userMain(int argc, char **argv);

#include "IVTEntry.h"


//Parametrizovani makro za pravljenje rutine i IVTEntrija
#define PREPAREENTRY(ivtNo, old)\
	void interrupt interrupt##ivtNo(...);\
	IVTEntry newEntry##ivtNo(ivtNo, interrupt##ivtNo);\
	void interrupt interrupt##ivtNo(...){\
		newEntry##ivtNo.sendSignalToEvent();\
		if(old) newEntry##ivtNo.callOld();\
	}



#endif /* DECLARE_H_ */
