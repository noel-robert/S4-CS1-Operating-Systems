// Experiment 9 - Page Replacement Algorithm(FIFO)

#include <stdio.h>
#include <stdlib.h>

int main() {
	int frames, pages, pageFaults=0, hits=0, refString[100];
	// input pages, reference string, frames
	printf("Input no. of pages "); scanf("%d", &pages);
	printf("Input reference String ");	for(int i=0; i<pages; i++) {scanf("%d", &refString[i]);}
	printf("Input no. of frames "); scanf("%d", &frames);

	int temp[frames];
	for(int i=0; i<frames; i++) {
		temp[i] = -1;
	}

	int index=0;
	for(int i=0; i<pages; i++) {
		int flag = 0;	// flag=0 means refString[i] not there in temp[]
		
		// find if refString[i] is present in temp[]
		for(int j=0; j<frames; j++) {
			if(refString[i] == temp[j]) {
        flag = 1; hits++;
				break;
			}
		}

		// if not present, store refString[i] in required position 
		if(flag == 0) {
			pageFaults++;
			temp[(index++)%frames] = refString[i];
		}

		for(int i=0; i<frames; i++) printf("%d ", temp[i]);
		printf("\n");
	}
	printf("Page Faults = %d\n", pageFaults);
	printf("Hits = %d\n", hits);
	
	return -1;
}