// Experiment 9 - Page Replacement Algorithm(LRU)

#include <stdio.h>
#include <stdlib.h>

int main() {
	int frames, pages, pageFaults=0, hits=0, refString[100];
	// input pages, reference string, frames
	printf("Input no. of pages "); scanf("%d", &pages);
	printf("Input reference String ");	for(int i=0; i<pages; i++) {scanf("%d", &refString[i]);}
	printf("Input no. of frames "); scanf("%d", &frames);

	int temp[frames], age[frames];
	for(int i=0; i<frames; i++) {
		temp[i] = -1; age[i] = -1;
	}

	for(int i=0; i<pages; i++) {
		int flag = 0;	// flag=0 means refString[i] not there in temp[]
		int pos = 0;
		
		// find if refString[i] is present in temp[]
		for(int j=0; j<frames; j++) {
			if(refString[i] == temp[j]) {
        flag = 1; pos = j; hits++;
				break;
			}
		}

		// if present, make age[pos] -1
		if(flag == 1) {
			age[pos] = -1;
		} else {	
			// if not present, find new position to store refString[i]. 
			// pos will be having LRU with max age.
			int max = age[pos];
			for(int j=0; j<frames; j++) {
				if(age[j] > max) {
					max = age[j];
					pos = j;
				}
			}
			temp[pos] = refString[i];
			age[pos] = -1;
			pageFaults++;
		}
		
		// increment age
		for(int j=0; j<frames; j++) {
			age[j]++;
		}
		
	}
	printf("Page Faults = %d\n", pageFaults);
	printf("Hits = %d\n", hits);
	
	return -1;
}