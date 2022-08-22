// // some errors

// #include <stdio.h>
// #include <stdlib.h>
// #include <sys/types.h>
// #include <sys/wait.h>
// #include <unistd.h>

// int main() {
//   int fd1[2], fd2[2], fd3[2]; // three pipes
//   int ret1, ret2, ret3;
//   int mesg[5], buf[5], buf1[5];

//   ret1 = pipe(fd1);
//   ret2 = pipe(fd2);
//   ret3 = pipe(fd3);

//   if (ret1 < 0 || ret2 < 0 || ret3 < 0) {
//     printf("Error in creating pipe\n");
//     return -1;
//   }

//   pid_t pid1;
//   pid1 = fork();
//   if (pid1 < 0) {
//     printf("Error in process creation\n");
//     return -1;
//   } else if (pid1 == 0) { // process2, child of process1

//     // read from first pipe and store in buf
//     read(fd1[0], buf, sizeof(buf));

//     // square elements in buf and store back to buf
//     for (int i = 0; i < sizeof(buf); i++)
//       buf[i] = buf[i] * buf[i];

//     // write buf to pipe2
//     write(fd2[1], buf, sizeof(buf));
//   } else if (pid1 > 0) { // process1, parent
//     printf("Input 5 elements\n");
//     for (int i = 0; i < 5; i++)
//       scanf("%d", &mesg[i]);
//     write(fd1[1], mesg, sizeof(mesg));
//     // wait(NULL);

//     pid_t pid2;
//     pid2 = fork();
//     if (pid2 < 0) {
//       printf("Error in process creation\n");
//       return -1;
//     } else if (pid2 == 0) { // process3, another child of process1
//       // read form pipe2, and store in buf1
//       read(fd2[0], buf1, sizeof(buf1));

//       // find sum of all elements in buf1 and store result to an array sum
//       // sum needs to be an array as second parameter of read() and write()
//       // should be pointer/array
//       int sum[1];
//       for (int i = 0; i < sizeof(buf1); i++)
//         sum[0] += buf1[i];

//       // write sum to pipe3
//       write(fd3[1], sum, sizeof(sum));
//     } else {
//       // do nothing
//     }

//     int s[1];
//     // read from pipe3 and store in s
//     read(fd3[0], s, sizeof(s));
//     // display the final sum
//     for (int i = 0; i < sizeof(s); i++)
//       printf("%d", s[i]);
//   }

//   return 0;
// }

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd1[2], fd2[2], fd3[2];
  int ret1, ret2, ret3; // for pipes 1, 2, 3
  pid_t pid1;
  int mesg[5], buf[5], buf1[5];

  ret1 = pipe(fd1);
  ret2 = pipe(fd2);
  ret3 = pipe(fd3);
  if (ret1 < 0 || ret2 < 0 || ret3 < 0) {
    printf("Error during pipe creation");
    return -1;
  }

  pid1 = fork(); // printf("%d", pid1);
  if (pid1 < 0) {
    printf("Error");
    return -1;
  } else if (pid1 == 0) {
    printf("Child 1\n");

    read(fd1[0], buf, sizeof(buf)); // read from pipe1

    for (int i = 0; i < 5; i++)
      buf[i] = buf[i] * buf[i];

    printf("\nSquared Numbers:\n");
    for (int i = 0; i < 5; i++)
      printf("%d\t", buf[i]);
    printf("\n\n");

    write(fd1[1], buf, sizeof(buf)); // write to pipe2
  } else if (pid1 > 0) {
    printf("Parent\n");

    printf("Input 5 numbers:\n");
    for (int i = 0; i < 5; i++)
      scanf("%d", &mesg[i]);

    write(fd1[1], mesg, sizeof(mesg)); // write to pipe1

		wait(NULL);
    // fork again
    pid_t pid2;
    pid2 = fork();
    if (pid2 < 0) {
      printf("Error");
      return -1;
    } else if (pid2 == 0) // 3rd process
    {
      printf("Child 2\n");
      printf("\nsumhereyy\n");
      int temp = read(fd2[0], buf1, sizeof(buf1)); // read from pipe2
      printf("\nsumherexx\n");

      int sum[5];
      for (int i = 0; i < 5; i++)
        sum[0] += buf1[i];

      write(fd3[1], sum, sizeof(sum)); // write to pipe3
      printf("\nsumhere\n");
    } else {
      // not necessary
      printf("Other\n");
      // wait(NULL);
      printf("some\n");
    }

    printf("back to parent\n");
    wait(NULL);
    int s[5];
    read(fd3[0], s, sizeof(s)); // read from pipe3
    printf("\nFinal sum of squared numbers: %d", s[0]);
    printf("\n\n ended\n");
  }

  return 0;
}