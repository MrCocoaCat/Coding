#include <pthread.h>

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <queue>
#define ONE_SECOND 1000000
#define RANGE 10
#define PERIOD 2
#define NUM_THREADS 4 
using namespace std;
typedef struct 
{
	int capacity; //
	queue<int >qu;
	pthread_mutex_t lock; //
	pthread_cond_t space; //¿¿¿¿¿
	pthread_cond_t car;   //¿¿¿¿
} cp_t;
static void * car_in_handler(void *cp_in);
static void * car_out_handler(void *cp_in);
static void * monitor(void *cp_in);
static void initialise(cp_t *cp, int size);
//only using in this file
static int num;

int main(int argc, char *argv[]) 
{

	if (argc != 2) 
	{
		printf("Usage: %s carparksize\n", argv[0]);
		exit(1);
	}

	cp_t ourpark;//

	initialise(&ourpark, atoi(argv[1])); // 

	pthread_t car_in, car_out, m;  
	pthread_t car_in2, car_out2;

	pthread_create(&car_in, NULL, car_in_handler, (void *)&ourpark);  // ¿¿¿
//	pthread_create(&car_in2, NULL, car_in_handler, (void *)&ourpark); // ¿¿¿2

	pthread_create(&car_out, NULL, car_out_handler, (void *)&ourpark); // ¿¿¿
	pthread_create(&car_out2, NULL, car_out_handler, (void *)&ourpark); // ¿¿¿2 

//	pthread_create(&m, NULL, monitor, (void *)&ourpark);  // ´´½¨ÓÃÓÚ¼à¿ØÍ£³µ³¡×´¿öµÄÏß³Ì

	pthread_join(car_in, NULL);
	pthread_join(car_out, NULL);
	pthread_join(car_in2, NULL);
	pthread_join(car_out2, NULL);
//	pthread_join(m, NULL);

	exit(0);
}

static void initialise(cp_t *cp, int size) {

	cp->capacity = size;//
	pthread_mutex_init(&cp->lock, NULL); // ³õÊ¼»¯Í£³µ³¡µÄËø
	pthread_cond_init(&cp->space, NULL); // ³õÊ¼»¯ÃèÊöÍ£³µ³¡ÊÇ·ñÓÐ¿ÕÎ»µÄÌõ¼þ±äÁ¿
	pthread_cond_init(&cp->car, NULL); // ³õÊ¼»¯ÃèÊöÍ£³µ³¡ÊÇ·ñÓÐ³µµÄÌõ¼þ±äÁ¿
}

static void* car_in_handler(void *carpark_in) 
{

	cp_t *temp;
	temp = (cp_t *)carpark_in;//¿¿¿¿¿¿¿¿
	while (1) 
	{

		sleep(1);
		pthread_mutex_lock(&temp->lock);
		while (temp->qu.size() == temp->capacity)
		{
			pthread_cond_wait(&temp->space, &temp->lock);
		}
		cout<<"push:"<<num<<endl;
		temp->qu.push(num++);

		pthread_cond_signal(&temp->car);//¿¿¿wait¿¿¿¿¿¿
		pthread_mutex_unlock(&temp->lock);

	}
	return ((void *)NULL);

}

static void* car_out_handler(void *carpark_out) 
{

	cp_t *temp;
	temp = (cp_t *)carpark_out;
	while (1)
	{

		sleep(2);
		pthread_mutex_lock(&temp->lock);
		while (temp->qu.size() == 0)
		{
			pthread_cond_wait(&temp->car, &temp->lock);
		}
		cout<<"                pop:"<<temp->qu.front()<<endl;;
		temp->qu.pop();
		pthread_cond_signal(&temp->space);
		pthread_mutex_unlock(&temp->lock);

	}
	return ((void *)NULL);

}

static void *monitor(void *carpark_in) 
{

	cp_t *temp;
	temp = (cp_t *)carpark_in;

	while(1) 
	{
		sleep(PERIOD);

		pthread_mutex_lock(&temp->lock);
		cout<<"Number of cars in carpark: "<< temp->qu.size();
		pthread_mutex_unlock(&temp->lock);
	}

	return ((void *)NULL);
}
