// Producer-Consumer Problem (not for lab)
// https://shivammitra.com/c/producer-consumer-problem-in-c/#

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

// maximum items a producer can produce or a consumer can consume
#define maxItems 5	

// size of buffer
#define bufferSize 5	

int in=0, out=0;
int buffer[bufferSize];
sem_t full, empty;
pthread_mutex_t mutex;


void *producer(void *pno) {
	int item;
	
	for(int i=0; i<maxItems; i++) {
		item = rand();
		sem_wait(&empty);
		pthread_mutex_lock(&mutex);
		buffer[in] = item;
		printf("Producer %d: Inseat item %d at %d\n", *((int *)pno), buffer[in], in);
		in = (in + 1)%bufferSize;
		pthread_mutex_unlock(&mutex);
		sem_post(&full);
	}
}

void *consumer(void *cno) {
	for(int i=0; i<maxItems; i++) {
		sem_wait(&full);
		pthread_mutex_lock(&mutex);
		int item = buffer[out];
		printf("Consumer %d: Remove item %d at %d\n", *((int *)cno), item, out);
		out = (out + 1)%bufferSize;
		pthread_mutex_unlock(&mutex);
		sem_post(&empty);
	}
}

int main() {
	pthread_t pro[5], con[5];
	pthread_mutex_init(&mutex, NULL);
	sem_init(&empty, 0, bufferSize);
	sem_init(&full, 0, 0);

	int a[5] = {1, 2, 3, 4, 5};

	for(int i=0; i<5; i++)
		pthread_create(&pro[i], NULL, (void *)producer, (void *)&a[i]);

	for(int i=0; i<5; i++)
		pthread_create(&con[i], NULL, (void *)consumer, (void *)&a[i]);

	for(int i=0; i<5; i++)
		pthread_join(pro[i], NULL);

	for(int i=0; i<5; i++)
		pthread_join(con[i], NULL);


	pthread_mutex_destroy(&mutex);
	sem_destroy(&empty);
	sem_destroy(&full);

	return 0;
}