#include <stdio.h>
#include <stdlib.h>

void fcfs() {
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
	}

	printf("\nTotal distance moved by disk = %d\n", sum);
}

void scan() {
	int start, end, current, prev;
	printf("Input starting and ending address of cylinders "); scanf("%d %d", &start, &end);
	printf("Input cylinder number of current request "); scanf("%d", &current);
	printf("Input cylinder number of previous request "); scanf("%d", &prev);

	int n;
	printf("Input no. of requests pending "); scanf("%d", &n);

	int req[n];
	printf("Input %d requests ", n);
	for(int i=0; i<n; i++) scanf("%d", &req[i]); 

	int cpy[n+2];
	cpy[0] = start, cpy[(n+2)-1] = end;
	// make new array
	for(int i=0; i<(n); i++) cpy[i+1] = req[i];
	// sort array
	for(int i=0; i<(n+2)-1; i++) {
		for(int j=0; j<(n+2)-i-1; j++) {
			if(cpy[j] > cpy[j+1]) {
				int temp = cpy[j]; cpy[j] = cpy[j+1]; cpy[j+1] = temp;
			}
		}
	}
	
	int sum;
	if(prev < current) {
		int pos = 0, i;									//*
		while(cpy[pos] < current)
			pos++;

		sum = abs(current - cpy[pos]);
		// right side
		for(i=pos+1; i<n+2; i++)
			sum += abs(cpy[i-1] - cpy[i]);
		// back to other side(R->L)
		sum += abs(cpy[(n+2)-1] - cpy[pos-1]);
		// left side
		for(i=pos-1; i>1; i--)						//*
			sum += abs(cpy[i] - cpy[i-1]);
	}
	else {
		int pos = (n+2)-1, i;								//*
		while(cpy[pos] > current)
			pos--;

		sum = abs(current - cpy[pos]);
		// left side
		for(i=pos-1; i>0; i--)
			sum += abs(cpy[i] - cpy[i-1]);
		// to other side (L->R)
		sum += abs(cpy[0] - cpy[pos+1]);
		// right side
		for(i=pos+1; i<(n+2)+1; i++)						// *
			sum += abs(cpy[i-1] - cpy[i]);
	}

	printf("\nTotal distance moved by disk = %d\n", sum);
}

void cscan() {
	int start, end, current, prev;
	printf("Input starting and ending address of cylinders "); scanf("%d %d", &start, &end);
	printf("Input cylinder number of current request "); scanf("%d", &current);
	printf("Input cylinder number of previous request "); scanf("%d", &prev);

	int n;
	printf("Input no. of requests pending "); scanf("%d", &n);

	int req[n];
	printf("Input %d requests ", n);
	for(int i=0; i<n; i++) scanf("%d", &req[i]); 

	int cpy[n+2];
	cpy[0] = start, cpy[(n+2)-1] = end;
	// make new array
	for(int i=0; i<(n); i++) cpy[i+1] = req[i];
	// sort array
	for(int i=0; i<(n+2)-1; i++) {
		for(int j=0; j<(n+2)-i-1; j++) {
			if(cpy[j] > cpy[j+1]) {
				int temp = cpy[j]; cpy[j] = cpy[j+1]; cpy[j+1] = temp;
			}
		}
	}

	int sum;
	if(prev < current) {
		int pos = 0;
		while(cpy[pos] < current)
			pos++;

		sum = abs(current - cpy[pos]);
		int i = pos+1;
		while(i != pos) {
			//printf("%d ", i);
			sum += abs(cpy[i-1] - cpy[i]);
			i = (i+1)%(n+2);
		}
		sum += (end - start);								//*
	}
	else {
		int pos = (n+2)-1;
		while(cpy[pos] > current)
			pos--;

		sum = abs(current - cpy[pos]);
		int i = pos-1;
		while(i != pos) {
			sum += abs(cpy[i-1] - cpy[i]);
			i = (i-1)%(n+2);
		}
		sum += (end - start);								//*
	}

	printf("\nTotal distance moved by disk = %d\n", sum);
	// for(int i=0; i<n+2; i++) printf("%d ", cpy[i]);
}

int main() {
	int choice;
	do {
		printf("1. FCFS\n");
		printf("2. SCAN\n");
		printf("3. C-SCAN\n");
		printf("4. ExitProgram\n");
		printf("Input choice ");
		scanf("%d", &choice);

		switch(choice) {
			case 1: fcfs(); break;
			case 2: scan(); break;
			case 3: cscan(); break;
			case 4: printf("ExitProgram"); break;
			default: printf("Wrong code inputted\n"); break;
		}
		printf("\n");
	} while(choice != 4);
	
	return  -1;
}

// Input starting and ending address of cylinders 0 4999
// Input cylinder number of current request 2150
// Input cylinder number of previous request 1805
// Input no. of requests pending 10
// Input 10 requests 2069 1212 2296 2800 544 1618 356 1523 4965 368