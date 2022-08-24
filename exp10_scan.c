// Experiment 10 - Disk Scheduling(SCAN)

#include <stdio.h>
#include <stdlib.h>

int main() {
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
		// right side
		for(int i=pos+1; i<n+2; i++)
			sum += abs(cpy[i-1] - cpy[i]);
		// back to other side(R->L)
		sum += abs(cpy[(n+2)-1] - cpy[pos-1]);
		// left side
		for(int i=pos-1; i>0; i--)
			sum += abs(cpy[i] - cpy[i-1]);
	}
	else {
		int pos = (n+2)-1;
		while(cpy[pos] > current)
			pos--;

		sum = abs(current - cpy[pos]);
		// left side
		for(int i=pos-1; i>0; i--)
			sum += abs(cpy[i] - cpy[i-1]);
		// to other side (L->R)
		sum += abs(cpy[0] - cpy[pos+1]);
		// right side
		for(int i=pos+1; i<n+2; i++)
			sum += abs(cpy[i-1] - cpy[i]);
	}

	printf("\nTotal distance moved by disk = %d\n", sum);
	
	return 0;
}