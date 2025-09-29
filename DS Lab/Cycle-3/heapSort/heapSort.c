#include <stdio.h>
#include <stdlib.h>

typedef struct Heap {
	int size;
	int heap[100];
} Heap;


void heapify(int arr[], int n, int i) {

	int largest = i;	
	int left = 2*i + 1;
	int right = 2*i + 2;

	if(left < n && arr[left] > arr[largest]) {
		largest = left;
	}

	if(right < n && arr[right] > arr[largest]) {
		largest = right;	
	}

	if(largest != i) {
		int temp = arr[i];
		arr[i] = arr[largest];
		arr[largest] = temp;
		heapify(arr, n, largest);
	}
}

void insert(Heap *h, int val) {
	if(h->size == 100) {
		printf("Overflow\n");
		return;
	}

	h->size++;
	int i = h->size - 1;
	h->heap[i] = val;

	while(i != 0 && h->heap[(i-1)/2] > h->heap[i]) { //comparing inserted value with parent node
		int temp = h->heap[i];
		h->heap[i] = h->heap[(i-1)/2];
		h->heap[(i-1)/2] = temp;
		i = (i-1)/2; //backtracking to previous parent node
	}
}

void buildMaxHeap(int arr[], int n) {
	
	for(int i = (n/2)-1; i>=0; i--) {
		heapify(arr, n, i);
	}	
}

void heapSort(int arr[], int n) {
	
	buildMaxHeap(arr, n);
	for(int i = n-1; i>=0; i--) {
		int temp = arr[i];
		arr[i] = arr[0];
		arr[0] = temp;

		heapify(arr, i, 0);
	}	
}

void display(int* tree, int* n) {
	//print all data nodes
	for(int i = 0, j = 0; j < *n; i++) {
		if(tree[i] != -1) {
			printf("%d ", tree[i]);
			j++; //increment only when non null node
		}
	}
	printf("\n");
}

int main() {
	int choice;
	Heap h;
	h.size = 0;

	while(1) {
		
		printf("1- Insert element\n2- Sort using Heap Sort\n3- Display\n");
		scanf("%d", &choice);	

		switch(choice) {
			case 1:
				{
					int val;
					printf("Enter value to be inserted: ");
					scanf("%d", &val);
					insert(&h, val);
					break;
				}
			case 2:
				{
					heapSort(h.heap, h.size);
					break;
				}
			case 3:
				{
					display(h.heap, &h.size);
					break;
				}
			default: return 0;	
		}
	}
	


}