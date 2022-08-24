// Experiment 10 - Disk Scheduling(C-SCAN)

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
		int i = pos+1;
		while(i != pos) {
			printf("%d ", i);
			sum += abs(cpy[i-1] - cpy[i]);
			i = (i+1)%(n+2);
		}
		sum += end;
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
		sum += end;
	}

	printf("\nTotal distance moved by disk = %d\n", sum);
	for(int i=0; i<n+2; i++) printf("%d ", cpy[i]);
	return 0;
}