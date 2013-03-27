//============================================================================
// Name        : testing01.cpp
// Author      : Richard Ranft
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <unistd.h>
#include <iostream>
#include <pthread.h>
#include <errno.h>
#include "testing01.h"
#include "tasks.h"

using namespace std;
pthread_mutex_t mtex;

int main() {
	int status = 0;
	pthread_mutex_init(&mtex, NULL);
	status = runThreads();
	pthread_mutex_destroy(&mtex);
	return status;
}

int runThreads()
{
	int status = 0;
	routineParam_t data1;
	data1.msg = (char*)("This is a routineParam struct");
	taskData_t* task1 = new taskData_t();
	task1->name = (char*)("Task1");
	task1->routineParam = (void*)&data1;
	task1->m_routine = taskFunc;

	routineParam2_t data2;
	data2.msg = (char*)("This is a routineParam2 struct");
	data2.index = 1;
	taskData_t* task2 = new taskData_t();
	task2->name = (char*)("Task2");
	task2->routineParam = (void*)&data2;
	task2->m_routine = taskFunc2;

	cout << "Starting tasks...\n";
	pthread_t thread1;
	status = execute(*task1, thread1);
	if (status == -1)
	{
		status = errno;
		cout << "Task1 failed : " << status << "\n";
		return status;
	}
	pthread_t thread2;
	status = execute(*task2, thread2);
	if (status == -1)
	{
		status = errno;
		cout << "Task2 failed : " << status << "\n";
		return status;
	}
	pthread_join(thread1, &task1->result);
	pthread_join(thread2, &task2->result);

	cout << "Task 1 result: " << (int)task1->result << "\n";
	cout << "Task 1 data result: " << (char*)data1.result << "\n";
	cout << "Task 2 result: " << (int)task2->result << "\n";
	cout << "Task 2 data result: " << (char*)data2.result << "\n";
	cout << "Completed tasks.\n";
	return status;
}

int execute(taskData_t& taskData, pthread_t& thread)
{
	int status = 0;
	//cout << "Executing task " << taskData.name << "\n";
	status = pthread_create(&thread, NULL, taskData.m_routine, taskData.routineParam);
	return status;
}
