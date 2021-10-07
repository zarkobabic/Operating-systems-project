/*
 * listPCB.cpp
 *
 *  Created on: Sep 11, 2021
 *      Author: OS1
 */

#include "listPCB.h"
#include "SCHEDULE.H"


ListPCB::ListPCB(){
	head = 0;
	tail = 0;
}
ListPCB::~ListPCB(){
	Elem* pom = head;
	while(pom){
		head = pom;
		pom = pom->next;
		delete head;
	}
	head = 0;
}

void ListPCB::append(PCB* el){
	Elem* newElem = new Elem();
	newElem->info = el;
	newElem->next = 0;

	if(!head){
		head = newElem;
		tail = newElem;
	}
	else{
		tail->next = newElem;
		tail = newElem;
	}
}

void ListPCB::toBeggining(PCB* el){
	Elem* newElem = new Elem();
	newElem->info = el;
	newElem->next = 0;

	if(!head){
		head = newElem;
		tail = head;
	}
	else{
		newElem->next = head;
		head = newElem;
	}
}

PCB* ListPCB::get(ID id){
	Elem* pom;
	if(head == 0) return 0;
	for(pom = head; pom; pom = pom->next){
		if(pom->info->getId() == id) return pom->info;
	}
	return 0;
}

void ListPCB::remove(ID id){
	Elem *pom, *prev = 0;
	for(pom = head; pom; pom = pom->next){
		if(pom->info->getId() == id){


			if(pom == head){
				if(pom->next == 0){
					delete pom;
					head = 0;
					tail = 0;
					return;
				}
				else{
					head = pom->next;
					delete pom;
					return;
				}
			}
			else{
				prev->next = pom->next;
				if(pom == tail) tail = prev;
				delete pom;
				return;
			}
		}
		prev = pom;
	}
}

/*
void ListPCB::print(){
	Elem* pom;
		for(pom = head; pom; pom = pom->next){
			cout<< pom->info->getId();
		}
		cout<<endl;
}*/

void ListPCB::freeWaiting(){
	Elem* pom;
	for(pom = head; pom ;pom = pom->next){
		if(pom->info->myThread == (Thread*)Timer::idle) continue;
		pom->info->state = READY;
		Scheduler::put(pom->info);
	}
}


/*PCB* ListPCB::getFromBeggining(){
	if(!head) return 0;
	Elem* pom = head;
	head = head->next;
	if(pom == tail) tail = head;
	return pom->info;
}*/

PCB* ListPCB::takefirst(){
	return head->info;
}

