/*
 * testing01.h
 *
 *  Created on: Mar 26, 2013
 *      Author: sgp1000
 */

#ifndef TESTING01_H_
#define TESTING01_H_
#include "tasks.h"

extern void* taskFunc(void*);
extern void* taskFunc2(void*);
int runThreads();
int execute(taskData_t&, pthread_t&);

#endif /* TESTING01_H_ */
