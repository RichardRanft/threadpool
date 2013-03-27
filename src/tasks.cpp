/*
 * tasks.cpp
 *
 *  Created on: Mar 26, 2013
 *      Author: sgp1000
 */

#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include "tasks.h"

extern pthread_mutex_t mtex;

void* taskFunc(void* param)
{
	routineParam_t *pData = (routineParam_t*)param;
	pthread_mutex_lock(&mtex);
	std::cout << pData->msg << "\n";
	pthread_mutex_unlock(&mtex);
	char* returnMsg = (char*)("routineParam_t result");
	pData->result = (void*) returnMsg;
	int result = 50;
	return (void*)result;
}

void* taskFunc2(void* param)
{
	routineParam2_t *pData = (routineParam2_t*)param;
	pthread_mutex_lock(&mtex);
	std::cout << pData->msg << " : " << pData->index << "\n";
	pthread_mutex_unlock(&mtex);
	char* returnMsg = (char*)("routineParam2_t result");
	pData->result = (void*) returnMsg;
	int result = 90;
	return (void*)result;
}
