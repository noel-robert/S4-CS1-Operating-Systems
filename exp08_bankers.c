// Experiment 8
// Banker's Algorithm in C

#include <stdio.h>
int main() {

  int n, m, i, j, k;
  printf("Enter the process count: ");
  scanf("%d", &n);

  printf("Enter the resource count: ");
  scanf("%d", &m);

  int alloc[n][m], max[n][m], avail[m];

  for (int i = 0; i < n; i++) {
    printf("Input allocation for %d resources of P[%d]: ", m, i);
    for (int j = 0; j < m; j++) {
      scanf("%d", &alloc[i][j]);
    }
  }

  for (int i = 0; i < n; i++) {
    printf("Input max for %d resources of P[%d]: ", m, i);
    for (int j = 0; j < m; j++) {
      scanf("%d", &max[i][j]);
    }
  }

  printf("Input avail: ");
  for (int j = 0; j < m; j++) {
    scanf("%d", &avail[j]);
  }

  printf("\nAllocation Table\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", alloc[i][j]);
    }
    printf("\n");
  }
  printf("\nMax table\n");
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d ", max[i][j]);
    }
    printf("\n");
  }
  printf("\nAvail table\n");
  for (int j = 0; j < m; j++) {
    printf("%d ", avail[j]);
  }
  printf("\n\n");


	
  int finish[n], seq[n], ind = 0;
  for (k = 0; k < n; k++) {
    finish[k] = 0;
  }
	
  int need[n][m];
  for (i = 0; i < n; i++) {
    for (j = 0; j < m; j++)
      need[i][j] = max[i][j] - alloc[i][j];
  }
	
  int y = 0;
  for (k = 0; k < n; k++) {
    for (i = 0; i < n; i++) {
      if (finish[i] == 0) {
        int flag = 0;
        for (j = 0; j < m; j++) {
          if (need[i][j] > avail[j]) {
            flag = 1;
            break;
          }
        }

        if (flag == 0) {
          seq[ind++] = i;
          for (y = 0; y < m; y++)
            avail[y] += alloc[i][y];
          finish[i] = 1;
        }
      }
    }
  }

  int flag = 1;
  for (int i = 0; i < n; i++) {
    if (finish[i] == 0) {
      flag = 0;
      printf("The following system is not safe\n");
      break;
    }
  }

  if (flag == 1) {
    printf("Following is the Safe Sequence:\n");
    for (i = 0; i < n - 1; i++)
      printf("P%d -> ", seq[i]);
    printf("P%d\n", seq[n - 1]);
  }

  return (0);
}