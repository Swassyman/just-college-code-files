#include <stdio.h>
#include <stdlib.h>

void fifo(int pages[], int n, int frameSize) {
	int memory[frameSize];
	int front = 0;
	int pageFaults = 0;

	for(int i = 0; i < frameSize; i++) {
		memory[i] = -1;
	}

	for(int i = 0; i < n; i++) {
		int currPage = pages[i];
		int found = 0;

		for(int j  = 0; j < frameSize; j++) {
			if(memory[j] == currPage) {
				found = 1;
				break;
			}
		}

		if(!found) {
			pageFaults++;
			memory[front] = currPage;
			front = (front+1) % frameSize;
		}	
	}

	printf("Page Faults: %d\nPage Hits: %d\n", pageFaults, n-pageFaults);
}

void lru(int pages[], int n, int frameSize) {
	int memory[frameSize];
	int recentlyUsed[frameSize];
	int pageFaults = 0;

	for(int i = 0; i < frameSize; i++) {
		memory[i] = -1;
		recentlyUsed[i] = 0;
	}

	for(int i = 0; i < n; i++) {
		int found = 0;
		int currPage = pages[i];

		for(int j = 0; j<frameSize; j++) {
			if(memory[j] == currPage) {
				found = 1;
				recentlyUsed[j] = i+1;
				break;
			}
		}

		if(!found) {
			pageFaults++;

			int lruInd = 0;
			int min = recentlyUsed[0];
			for(int j = 0; j<frameSize; j++) {
				if(min > recentlyUsed[j]) {
					min = recentlyUsed[j];
					lruInd = j;
				}
			}

			memory[lruInd] = currPage;
			recentlyUsed[lruInd] = i+1;
		}
	}
	printf("Page Faults: %d\nPage Hits: %d\n", pageFaults, n-pageFaults);
}

void lfu(int pages[], int n, int frameSize) {
	int memory[frameSize];
	int freq[frameSize];
	int time[frameSize];
	int pageFaults = 0;

	for(int i = 0; i<frameSize; i++) {
		memory[i] = -1;
		freq[i] = 0;
		time[i] = 0;
	}

	for(int i = 0; i<n; i++) {
		int currPage = pages[i];
		int found = 0; 

		for(int j = 0; j<frameSize; j++) {
			if(memory[j] == currPage) {
				found = 1;
				freq[j]++;
				time[j] = i;
				break;
			}
		}

		if(!found) {
			pageFaults++;

			int ind = 0;
			int minFreq = freq[0];
			int minTime = time[0];

			for(int j = 1; j<frameSize; j++) {
				if(memory[j] == -1) {
					ind = j;
					break;
				}

				if( freq[j] < minFreq) {
					minFreq = freq[j];
					minTime = time[j];
					ind = j;
				} else if(freq[j] == minFreq && time[j] < minTime) {
					minTime = time[j];
					ind = j;
				}
			}

			memory[ind] = currPage;
			freq[ind] = 1;
			time[ind] = i;
		}
	}

	printf("Page Faults: %d\nPage Hits: %d\n", pageFaults, n-pageFaults);
}

int main() {
	int n;
	printf("Enter number of pages: ");
	scanf("%d", &n);

	int pages[n];
	printf("Enter page reference sequence: ");
	for(int i = 0; i < n; i++) {
		scanf("%d", &pages[i]);
	}

	int frameSize;
	printf("Enter number of frames: ");
	scanf("%d", &frameSize);

	int choice;

	while(1) {
		printf("Menu\n");
		printf("1- FIFO\n");
		printf("2- LRU\n");
		printf("3- LFU\n");
		printf("4- Exit\n");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				fifo(pages, n, frameSize);
				break;
			case 2:
				lru(pages, n, frameSize);
				break;
			case 3:
				lfu(pages, n, frameSize);
				break;
			case 4:
				return 0;
			default: break;
		}
	}
	return 0;
}