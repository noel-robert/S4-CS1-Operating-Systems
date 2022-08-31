// Dining Philosopher problem

#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

sem_t chopstick[5];

void eat(int philosopher) { printf("Philosopher %d is eating\n", philosopher); }

void *philosopher(void *num) {
  int philosopher = *(int *)num;

  printf("Philosopher %d wants to eat\n", philosopher);
  sem_wait(&chopstick[philosopher]);
  sem_wait(&chopstick[(philosopher + 1) % 5]);

  eat(philosopher); sleep(2);
  printf("Philosopher %d has finished eating\n", philosopher);

  sem_post(&chopstick[(philosopher + 1) % 5]);
  sem_post(&chopstick[philosopher]);
}

int main() {
  int a[5];
  pthread_t tid[5];

  for (int i = 0; i < 5; i++) {
    sem_init(&chopstick[i], 0, 1);
  }

  for (int i = 0; i < 5; i++) {
    a[i] = i;
    // pthread_create(&tid[i], NULL, philosopher, (void*)&a[i]);
		pthread_create(&tid[i], NULL, philosopher, &a[i]);
  }

  for (int i = 0; i < 5; i++) {
    pthread_join(tid[i], NULL);
  }

  return 0;
}