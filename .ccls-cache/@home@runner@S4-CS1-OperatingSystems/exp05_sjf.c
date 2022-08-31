// implementing CPU Scheduling Algorithm
// [Shortest Job First, non preemptive]

#include <stdio.h>
#include <stdlib.h>

struct Process {
  int pno;            // process number
  int arrivalTime;    // time of arrival of a process
  int burstTime;      // burst time of a process
  int turnAroundTime; // turn around time of the process
  int waitingTime;    // time the process waits
};

int main() {
  int n;
  printf("Input number of processes ");
  if (scanf("%d", &n) > 0) {} else {printf("Error in inputting");return -1;}
  printf("\n");

  struct Process process[n];

  // input data
  for (int i = 0; i < n; i++) {
    printf("Input arrival time for P%d ", i + 1);
    if (scanf("%d", &process[i].arrivalTime) > 0) {} else {printf("Error in inputting");return -1;}

    printf("Input burst time for P%d ", i + 1);
    if (scanf("%d", &process[i].burstTime) > 0) {} else {printf("Error in inputting");return -1;}

    printf("\n");
    process[i].pno = i + 1;
  }

  // display inputted data
  printf("Inputted Data\n");
  printf("P[]\t\tAT\tBT\n");
  for (int i = 0; i < n; i++) {
    printf("P[%d]\t%d\t%d\n", process[i].pno, process[i].arrivalTime,
           process[i].burstTime);
  }
  printf("\n");

  // calculations
  for (int i=0; i<n; i++) {
    for (int j=i+1; j<n; j++) {
      if ((process[i].arrivalTime>process[j].arrivalTime) || 
				((process[i].arrivalTime==process[j].arrivalTime)&&(process[i].burstTime>process[j].burstTime))) {
        struct Process temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      } 
    }
  }

  int completionTime[n];
  int min = 1000, pos;
  completionTime[0] = process[0].arrivalTime + process[0].burstTime;
  for (int i = 1; i < n; i++) {
    for (int j = i; j < n; j++) {
      if (process[j].arrivalTime <= completionTime[i - 1]) {
        if (process[j].burstTime < min) {
          min = process[j].burstTime;
          pos = j;
        }
      }
    }
    struct Process temp = process[i];
    process[i] = process[pos];
    process[pos] = temp;

    min = 1000;
    completionTime[i] = completionTime[i-1] + process[i].burstTime;
  }

  double averageTurnAroundTime, averageWaitingTime; // avg TAT & WT
  for (int i = 0; i < n; i++) {
    process[i].turnAroundTime = completionTime[i] - process[i].arrivalTime;
    process[i].waitingTime = process[i].turnAroundTime - process[i].burstTime;

		averageTurnAroundTime += process[i].turnAroundTime;
		averageWaitingTime += process[i].waitingTime;
  }
	averageTurnAroundTime = averageTurnAroundTime / n;
  averageWaitingTime = averageWaitingTime / n;

  // display output data
	// so, first sort by arrival time
	for (int i=0; i<n; i++) {
    for (int j=i+1; j<n; j++) {
      if (process[i].arrivalTime>process[j].arrivalTime) {
        struct Process temp = process[i];
        process[i] = process[j];
        process[j] = temp;
      } 
    }
  }
  printf("Output Data\n");
  printf("P[]\t\tTAT\tWT\n");
  for (int i = 0; i < n; i++) {
    printf("P[%d]\t%d\t%d\n", process[i].pno, process[i].turnAroundTime,
           process[i].waitingTime);
  }
  printf("\n");

  // display avg. TAT & avg. WT
  printf("\nAverage TurnAroundTime = %lf", averageTurnAroundTime);
  printf("\nAverage WaitingTime = %lf", averageWaitingTime);
  printf("\n");

  return 0;
}