#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int n;
	printf("Input number of elements to be inputted\n");
	scanf("%d", &n);

	int* A = (int*) malloc(sizeof(int));
	printf("Input %d elements\n", n);
	for(int i=0; i<n; i++)
		scanf("%d", &A[i]);

	pid_t pid;
	pid = fork();

	if(pid == -1)
		printf("Error\n");
	else if(pid == 0) {
		printf("\nChild Process\n");

		// sort in descending order
		for(int i=0; i<n-1; i++) {
			for(int j=0; j<n-1-i; j++) {
				if(A[j] < A[j+1]) {
					int temp = A[j];
					A[j] = A[j+1];
					A[j+1] = temp;
				}
			}
		}
	}
	else {
		wait(NULL);
		printf("\nParent Process\n");

		for(int i=0; i<n-1; i++) {
			for(int j=0; j<n-1-i; j++) {
				if(A[j] > A[j+1]) {
					int temp = A[j];
					A[j] = A[j+1];
					A[j+1] = temp;
				}
			}
		}
	}

	for(int i=0; i<n; i++)
		printf("%d ", A[i]);
	printf("\n");

	return 0;
}