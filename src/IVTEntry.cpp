/*
 * IVTEntry.cpp
 *
 *  Created on: Sep 24, 2021
 *      Author: OS1
 */


#include "IVTEntry.h"
#include "DOS.H"
IVTEntry* IVTEntry::IVTEntryArray[256];

IVTEntry::IVTEntry(IVTNo ivtNo, pInterrupt newInt){

	number = ivtNo;
#ifndef BCC_BLOCK_IGNORE
	oldInt = getvect(number);
#endif
	IVTEntry::IVTEntryArray[number] = this;
#ifndef BCC_BLOCK_IGNORE
	setvect(number, newInt);
#endif
	myEvent = 0;

}

IVTEntry* IVTEntry::getEntry(IVTNo ivtNo){
	return IVTEntryArray[ivtNo];
}

IVTEntry::~IVTEntry(){
	IVTEntry::IVTEntryArray[number] = 0;
#ifndef BCC_BLOCK_IGNORE
	setvect(number, oldInt);
#endif
}

void IVTEntry::sendSignalToEvent(){
	if(myEvent != 0) myEvent->signal();
}

void IVTEntry::callOld(){
	oldInt();
}
