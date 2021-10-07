/*
 * listKerS.cpp
 *
 *  Created on: Sep 23, 2021
 *      Author: OS1
 */

#include "ListKerS.h"
#include "node.h"
#include "global.h"
#include "listPCB.h"
#include "kerSem.h"
#include "SCHEDULE.H"

ListKerSem::ListKerSem(){
	head = 0;
	tail = 0;
}
ListKerSem::~ListKerSem(){
	Node* pom = head;
	while(pom){
		head = pom;
		pom = pom->next;
		delete head;
	}
	head = 0;
	tail = 0;
}

void ListKerSem::append(KernelSem* el){
	Node* newElem = new Node();
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

void ListKerSem::toBeggining(KernelSem* el){
	Node* newElem = new Node();
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

KernelSem* ListKerSem::get(ID id){
	Node* pom;
	if(head == 0) return 0;
	for(pom = head; pom; pom = pom->next){
		if(pom->info->getId() == id) return pom->info;
	}
	return 0;
}

void ListKerSem::remove(ID id){
	Node *pom, *prev = 0;
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
void ListKerSem::print(){
	Node* pom;
		for(pom = head; pom; pom = pom->next){
			cout<<"semafor "<< pom->info->getId()<<endl;

		}
		cout<<endl;
}
*/

void ListKerSem::freeIfDoneWaiting(){
	Elem* thisPCB;
	Node* thisSem;

	for(thisSem = Global::AllSem->head; thisSem;thisSem = thisSem -> next){

		for(thisPCB = thisSem->info->timeBlocked->head; thisPCB; ){
				thisPCB->info->timeToWait -=1;

				if(thisPCB->info->timeToWait == 0){
					thisPCB->info->state = READY;
					Scheduler::put(thisPCB->info);
					ID helper = (ID)thisPCB->info->id;
					thisPCB = thisPCB->next;
					((ListPCB*)thisSem->info->timeBlocked)->remove(helper);
					((ListPCB*)thisSem->info->blocked)->remove(helper);
					thisSem->info->incSem();
				}
				else{
					thisPCB = thisPCB->next;
				}
			}
	}
}







