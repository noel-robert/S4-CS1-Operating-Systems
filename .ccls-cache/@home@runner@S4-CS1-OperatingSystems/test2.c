// Adityan's qn - 11/08/2022

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main() {
	char str[200];
	fgets(str, sizeof(str), stdin);
	char vov[] = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
	
	pid_t pid;
	pid = fork();

	if(pid < 0) {
		printf("Error in process creation");
	} else if(pid == 0)	{	// child process
		int i = 0, count = 0;
		while(str[i] != '\0') {
			int j = 0;
			while(j < 14) {
				if(strcmp(&str[i], &vov[j]) == 0) 
					count++;
				j++;
			} i++;
			printf("vovel count = %d\n", count);
		}
	} else {	// parent process
		int i = 0, count = 0;
		char ch = ' ';
		while(str[i] != '\0') {
			if(str[i] == ' ' || str[i] == '\n' || str[i] == '\t') 
				count++;
			i++;
		}
		printf("word count = %d\n", count);
	}
	return 0;
}