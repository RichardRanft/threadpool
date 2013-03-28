/*
 * taskPool.cpp
 *
 *  Created on: Mar 26, 2013
 *      Author: sgp1000
 */

#include "taskPool.h"

const int taskPool_getCPUCount()
{
	FILE *fp;
	char result[128];
	fp = popen("/bin/cat /proc/cpuinfo |grep -c '^processor'", "r");
	fread(result, 1, sizeof(result)-1, fp);
	fclose(fp);
	if(result[0] < 1)
		return 1;
	else
		return (const int)atoi(result);
}

// ----------------------------------------------------------------------------
// taskEntry_t
// ----------------------------------------------------------------------------
taskEntry_t::taskEntry_t()
{
	pthread_mutex_init(&m_entryLock, NULL);
	pthread_mutex_lock(&m_entryLock);
	m_prev = 0;
	m_next = 0;
	m_task = 0;
	pthread_mutex_unlock(&m_entryLock);
}

taskEntry_t::taskEntry_t(taskData_t& task)
{
	pthread_mutex_init(&m_entryLock, NULL);
	pthread_mutex_lock(&m_entryLock);
	m_task = &task;
	m_next = 0;
	m_prev = 0;
	pthread_mutex_unlock(&m_entryLock);
}

taskEntry_t::~taskEntry_t()
{
	pthread_mutex_lock(&m_entryLock);
	m_prev->m_next = m_next;
	m_next->m_prev = m_prev;
	m_next = 0;
	m_prev = 0;
	delete(m_task);
	pthread_mutex_unlock(&m_entryLock);
	pthread_mutex_destroy(&m_entryLock);
}

taskEntry_t * taskEntry_t::getNext()
{
	return m_next;
}

taskEntry_t* taskEntry_t::getPrev()
{
	return m_prev;
}

void taskEntry_t::setNext(taskEntry_t& entry)
{
	pthread_mutex_lock(&m_entryLock);
	m_next = &entry;
	pthread_mutex_unlock(&m_entryLock);
}

void taskEntry_t::setPrev(taskEntry_t& entry)
{
	pthread_mutex_lock(&m_entryLock);
	m_prev = &entry;
	pthread_mutex_unlock(&m_entryLock);
}

int taskEntry_t::execute(pthread_t& taskThread)
{
	int status = 0;

	return status;
}

// ----------------------------------------------------------------------------
// taskPool_t
// ----------------------------------------------------------------------------
extern int taskPool_t::count;

taskPool_t::taskPool_t()
{
	pthread_mutex_init(&m_taskLock, NULL);
	m_initialized = false;
	m_managerThread = 0;
	m_currentTask = 0;
	m_head = 0;
	m_tail = 0;
	count = 0;
}

taskPool_t::~taskPool_t()
{
	pthread_mutex_destroy(&m_taskLock);
}

void taskPool_t::initializePool()
{
	for(int i = 0; i < 24; i++)
	{
		pthread_t taskThread;
		m_taskPool[i] = &taskThread;
	}
}

taskHandle_t taskPool_t::addTask(taskData_t& data)
{
	taskEntry_t entry(data);
	if(m_head == 0)
	{
		entry.setPrev(entry);
		entry.setNext(entry);
	}
	else
	{
		entry.setPrev((*m_currentTask));
		entry.setNext((*m_head));
	}
	m_currentTask = &entry;

	taskHandle_t handle;
	generateUUID(handle.m_taskID);
	return handle;
}

void taskPool_t::generateUUID(char* buffer)
{
	uuid_t uuid;
	uuid_generate_random( uuid );
	uuid_unparse( uuid, buffer );
}

int taskPool_t::queryTask(taskHandle_t& handle)
{
	int status = 0;

	return status;
}

taskEntry_t* taskPool_t::getHead()
{
	return m_head;
}

taskEntry_t* taskPool_t::getTail()
{
	return m_tail;
}

taskEntry_t* taskPool_t::getNext()
{
	taskEntry_t* temp = m_currentTask->getNext();
	m_currentTask = temp;
	return m_currentTask;
}

taskEntry_t* taskPool_t::getPrev()
{
	taskEntry_t* temp = m_currentTask->getPrev();
	m_currentTask = temp;
	return m_currentTask;
}

bool taskPool_t::run()
{
	bool status = false;
	if (!m_initialized)
	{
		return status;
	}

	return status;
}

void* taskPool_t::manageThreads(void*)
{
	int status = 0;

	return (void*)status;
}

void* taskPool_t::dummyTask(void*)
{
	int status = 0;

	return (void*)status;
}
