/*
 * taskPool.h
 *
 *  Created on: Mar 26, 2013
 *      Author: sgp1000
 */

#ifndef TASKPOOL_H_
#define TASKPOOL_H_

#include <pthread.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <uuid/uuid.h>
#include "tasks.h"

extern const int CPU_COUNT;

struct taskHandle_t
{
	char m_taskID[37];
	pthread_t m_threadID;
};

class taskEntry_t
{
public:
	taskEntry_t();
	taskEntry_t(taskData_t& task);
	~taskEntry_t();

	taskEntry_t* getNext();
	taskEntry_t* getPrev();

	void setNext(taskEntry_t&);
	void setPrev(taskEntry_t&);

	int execute(pthread_t&);
	void* getResult();
private:
	taskData_t* m_task;
	taskEntry_t* m_next;
	taskEntry_t* m_prev;
};

class taskPool_t
{
public:
	taskPool_t();
	~taskPool_t();

	taskHandle_t addTask(taskData_t&);
	bool removeTask(taskHandle_t&);
	bool cancelTask(taskHandle_t&);
	int queryTask(taskHandle_t&);
	taskEntry_t* getHead();
	taskEntry_t* getTail();
	taskEntry_t* getNext();
	taskEntry_t* getPrev();
	bool run();

private:
	void initializePool();
	void generateUUID(char*);
	void* manageThreads(void*);
	void* dummyTask(void*);
	bool m_initialized;
	static int count;
	pthread_t m_managerThread;
	pthread_t* m_taskPool[24];
	taskEntry_t* m_currentTask;
	taskEntry_t* m_head;
	taskEntry_t* m_tail;
};

#endif /* TASKPOOL_H_ */
