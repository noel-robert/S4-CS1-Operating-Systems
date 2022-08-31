// producer part of producer-consumer problem

/*
how to run producer-consumer??
1. in first terminal, run these commands
	gcc exp07_producer.c -lpthread -lrt -o prod
	./prod

2. in second termina, run these commands
	gcc exp07_consumer.c -o cons -lrt -lpthread
	./cons
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */

#define MAX_SIZE 5

struct shared{
	sem_t mutex, full, empty;
	char buffer[MAX_SIZE];
};

int main() {
	struct shared *ptr, *producer;

	int fd = shm_open("/shm", O_CREAT|O_RDWR, 0666);
	ftruncate(fd , sizeof(struct shared));
	ptr = mmap(NULL, sizeof(struct shared), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

	sem_init(&(ptr->mutex), 1, 1);
	sem_init(&(ptr->full), 1, 0);
	sem_init(&(ptr->empty), 1, MAX_SIZE);

	int index = 0, x, item = 0;
	while(1) {
		sleep(2);
		sem_getvalue(&(ptr->full), &x);

		if(x == MAX_SIZE) {
			printf("Buffer Overflow\n");
			return -1;
		}
		else {
			item++;

			sem_wait(&(ptr->mutex));
			sem_wait(&(ptr->empty));
			
			// produce
			ptr->buffer[index] = item; 
			printf("Producer produced %d\n", ptr->buffer[index]);
			index = (index+1)%MAX_SIZE;
			
			sem_post(&(ptr->full));
			sem_post(&(ptr->mutex));
		}
	}

	return -1;
}