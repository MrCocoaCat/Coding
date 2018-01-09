#pragma once

#include<pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
class CMyLock
{
private:

    pthread_mutex_t mutex;
public:
	CMyLock()
	{
        pthread_mutex_init(&mutex, NULL);

	}
	~CMyLock()
	{
        pthread_mutex_destroy(&mutex);
	}
	void Lock()
	{
       pthread_mutex_lock(&mutex);
	}
	void UnLock()
	{
        pthread_mutex_unlock(&mutex);
	}
};