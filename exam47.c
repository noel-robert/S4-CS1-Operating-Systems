// End Semester Exam, September 2022
// use pipe and fork. one process accepts array of data, another segregates it into odd and even numbers
// i wasn't able to do this fuckin' qn ;(

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	int fd[2], ret;
	pid_t pid;

	int n;
	printf("Input n: "); scanf("%d", &n); printf("\n");
	int arr[n], buf[n];

	ret = pipe(fd);
	pid = fork(); 
	if(ret < 0 || pid < 0) {printf("Error\n");}
	else if(pid == 0) {
		printf("Child process\n");

		printf("Input %d numbers: ", n);
		for(int i=0; i<n; i++) scanf("%d", &arr[i]);
		printf("\n");

		write(fd[1], &arr, sizeof(arr));
	}
	else {
		wait(NULL); 
		printf("Parent process\n");

		read(fd[0], &buf, sizeof(buf));
		int odd[n], even[n];
		int oddCount=0, evenCount=0;

		for(int i=0; i<n; i++) {
			if(buf[i]%2 == 0) {even[evenCount++] = buf[i];}
			else {odd[oddCount++] = buf[i];}
		}

		// printf("%d %d", oddCount, evenCount);
		// printf("\n%d", buf[0]);
		printf("Even numbers: "); for(int i=0; i<evenCount; i++) printf("%d ", even[i]); printf("\n");
		printf("Odd numbers: "); for(int i=0; i<oddCount; i++) printf("%d ", odd[i]); printf("\n");
	}

	return 0;
}