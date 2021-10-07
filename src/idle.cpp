/*
 * idle.cpp
 *
 *  Created on: Sep 20, 2021
 *      Author: OS1
 */
#include "idle.h"
#include "timer.h"

void Idle::run(){
	while(1);
}

Idle::Idle():Thread(defaultStackSize,1){
}
