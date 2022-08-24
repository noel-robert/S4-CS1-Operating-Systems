// Experiment 10 - Disk Scheduling(FCFS)

#include <stdio.h>
#include <stdlib.h>

int main() {
	int start, end, current;
	printf("Input starting and ending address of cylinders "); scanf("%d %d", &start, &end);
	printf("Input current address of cylinder "); scanf("%d", &current);

	int n;
	printf("Input no. of requests pending "); scanf("%d", &n);

	int req[n];
	printf("Input %d requests ", n);
	for(int i=0; i<n; i++) scanf("%d", &req[i]); 

	int sum = abs(req[0] - current);
	for(int i=1; i<n; i++) {
		sum += abs(req[i] - req[i-1]);
		printf("%d - %d = %d\n", req[i], req[i-1], sum);
	}
		

	printf("\nTotal distance moved by disk = %d\n", sum);
	return 0;
}