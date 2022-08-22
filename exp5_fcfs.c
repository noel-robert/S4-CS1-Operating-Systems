// implementing CPU Scheduling Algorithm
// [First Come First Serve, non preemptive]


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int n;
  printf("Input number of processes ");
  if (scanf("%d", &n) > 0) {} else { printf("Error in inputting"); return -1; }
	printf("\n");

	// declaring arrays
	int arrivalTime[n];
	int burstTime[n];

	// input data
	for(int i=0; i<n; i++) {
		printf("Input arrival time for P%d ", i+1);
		if (scanf("%d", &arrivalTime[i]) > 0) {} else { printf("Error in inputting"); return -1; }

		printf("Input burst time for P%d ", i+1);
		if (scanf("%d", &burstTime[i]) > 0) {} else { printf("Error in inputting"); return -1; }

		printf("\n");
	}

	// calculations
	int currentTime = 0;
	int turnAroundTime[n], waitingTime[n];	// store TAT & WT
	int processQueueEntryTime[n], processQueueExitTime[n];	// entry & exit from Gantt Chart
	double averageTurnAroundTime, averageWaitingTime;	// avg TAT & WT
	for(int i=0; i<n; i++) {
		// initializing....
		int offset;
		turnAroundTime[i] = -1;
		waitingTime[i] = -1;
		processQueueEntryTime[i] = -1;
		processQueueExitTime[i] = -1;
		
		if(arrivalTime[i] > currentTime) { offset = 0; }
		else { offset = currentTime - arrivalTime[i]; }

		// find entry and exit time to gantt chart
		processQueueEntryTime[i] = arrivalTime[i] + offset;
		processQueueExitTime[i] = arrivalTime[i] + burstTime[i] + offset;
		
		// calculate TAT & WT of processes
		turnAroundTime[i] = processQueueExitTime[i] - processQueueEntryTime[i] + offset;
		waitingTime[i] = offset;

		// update current time
		currentTime = processQueueExitTime[i];

		
		averageTurnAroundTime += turnAroundTime[i];
		averageWaitingTime += waitingTime[i];
	}
	
	// display inputted data
	printf("Inputted Data\n");
	printf("P[]\t\tAT\tBT\n");
	for(int i=0; i<n; i++) {
		printf("P[%d]\t%d\t%d\n", i+1, arrivalTime[i], burstTime[i]);
	}
	printf("\n");
	
	// display output data
	printf("Output Data\n");
	printf("P[]\t\tTAT\tWT\n");
	for(int i=0; i<n; i++) {
		printf("P[%d]\t%d\t%d\n", i+1, turnAroundTime[i], waitingTime[i]);
	}
	printf("\n");

	// display avg. TAT & avg. WT
	averageTurnAroundTime = averageTurnAroundTime/n;
	averageWaitingTime = averageWaitingTime/n;
	printf("\nAverage TurnAroundTime = %lf", averageTurnAroundTime);
	printf("\nAverage WaitingTime = %lf", averageWaitingTime);
  printf("\n");
	
	
	return 0;
}