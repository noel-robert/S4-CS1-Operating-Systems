// implementing CPU Scheduling Algorithm
// [Round Robin, preemptive]
// https://www.easycodingzone.com/2021/06/c-program-of-round-robin-scheduling.html
// examples - https://www.gatevidyalay.com/round-robin-round-robin-scheduling-examples/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

struct Process {
  int pno;            // process number
  int arrivalTime;    // time of arrival of a process
  int burstTime;      // burst time of a process
	int burstTimeRemaining;	// burst time remaining after each time quantum
  int turnAroundTime; // turn around time of the process
  int waitingTime;    // time the process waits
};
int *queue;	// ready queue
int front, rear;


void enque(int k) {
	if(front == -1)
		front = 0;
	
	rear = rear + 1;
	queue[rear] = k;
}

int deque() {
	int k;
	k = queue[front];
	front = front + 1;
	
	return k;
}

int main() {
	int n;
  printf("Input number of processes ");
  if (scanf("%d", &n) > 0) {} else {printf("Error in inputting");return -1;}
  printf("\n");

  struct Process process[n];
	queue = (int *) malloc(n * sizeof(int));	// initialize ready queue
	front = -1, rear = -1;
	int *exist = (int *) malloc(n * sizeof(int));

  // input data
  for (int i = 0; i < n; i++) {
    printf("Input arrival time for P%d ", i + 1);
    if (scanf("%d", &process[i].arrivalTime) > 0) {} else {printf("Error in inputting");return -1;}

    printf("Input burst time for P%d ", i + 1);
    if (scanf("%d", &process[i].burstTime) > 0) {} else {printf("Error in inputting");return -1;}

    printf("\n");
    process[i].pno = i + 1;
		process[i].burstTimeRemaining = process[i].burstTime;
		exist[i] = 0;
  }

	// input time quantum
	printf("Input time quantum ");
	int timeQuantum;
	if (scanf("%d", &timeQuantum) > 0) {} else {printf("Error in inputting");return -1;}
	printf("\n");

	// display inputted data
  printf("Inputted Data\n");
  printf("P[]\t\tAT\tBT\n");
  for (int i = 0; i < n; i++) {
    printf("P[%d]\t%d\t%d\n", process[i].pno, process[i].arrivalTime, process[i].burstTime);
  }
	printf("Time quantum = %d", timeQuantum);
  printf("\n\n");
	

	// calculations
	int completionTime = 0;
	enque(0);
	exist[0] = 1;
	double averageTurnAroundTime, averageWaitingTime; // avg TAT & WT

	while(front <= rear) {
		int p = deque();

		if(process[p].burstTimeRemaining >= timeQuantum) {
			process[p].burstTimeRemaining = process[p].burstTimeRemaining - timeQuantum;
			completionTime += timeQuantum;
		} else {
			completionTime += process[p].burstTimeRemaining;
			process[p].burstTimeRemaining = 0;
		}

		for(int i=0; i<n; i++) {
			if(exist[i]==0 && process[i].arrivalTime<=completionTime) {
				enque(i);
				exist[i] = 1;
			}
		}

		if(process[p].burstTimeRemaining == 0) {
			process[p].turnAroundTime = completionTime - process[p].arrivalTime;
			process[p].waitingTime = process[p].turnAroundTime - process[p].burstTime;

			averageTurnAroundTime += process[p].turnAroundTime;
			averageWaitingTime += process[p].waitingTime;
		} else {
			enque(p);
		}
	}
	averageTurnAroundTime = averageTurnAroundTime / n;
  averageWaitingTime = averageWaitingTime / n;



	printf("Output Data\n");
  printf("P[]\t\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    printf("P[%d]\t%d\t%d\t\n", process[i].pno, process[i].turnAroundTime,
           process[i].waitingTime);
  }
  printf("\n");

  // display avg. TAT & avg. WT
  printf("\nAverage TurnAroundTime = %lf", averageTurnAroundTime);
  printf("\nAverage WaitingTime = %lf", averageWaitingTime);
  printf("\n");

	return 0;
}