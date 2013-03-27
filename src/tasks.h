/*
 * tasks.h
 *
 *  Created on: Mar 26, 2013
 *      Author: sgp1000
 */

#ifndef TASKS_H_
#define TASKS_H_

struct taskData_t
{
	char* name;
	void* (*m_routine)(void*);
	void* routineParam;
	void* result;
};

struct routineParam_t
{
	char* msg;
	void* result;
};

struct routineParam2_t
{
	char* msg;
	int index;
	void* result;
};

void* taskFunc(void*);
void* taskFunc2(void*);

#endif /* TASKS_H_ */
