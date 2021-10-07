/*
 * IVTEntry.h
 *
 *  Created on: Sep 23, 2021
 *      Author: OS1
 */

#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include "kerEvent.h"
#include "IVTEntry.h"

class KernelEv;
typedef unsigned char IVTNo;
typedef void interrupt (*pInterrupt)(...);


class IVTEntry{
public:
		//globalne stvari
		static IVTEntry* IVTEntryArray[256];
		static IVTEntry* getEntry(IVTNo ivtNo);

		//lokalne stvari
		IVTEntry(IVTNo ivtNo, pInterrupt newInt);
		~IVTEntry();

		IVTNo number;
		KernelEv* myEvent; //zvace signal nad ovim Eventom


		pInterrupt oldInt;
		void sendSignalToEvent();
		void callOld();
};

#endif /* IVTENTRY_H_ */
