#include <stdio.h>
#include <stdlib.h>
#define MAX 100

//implemented as array -> memory overhead (memory taken by system to do task than the memory taken by the task itself) is high
typedef struct Heap {
	int size; //size of heap
	int heap[MAX]; //values of each index 
} Heap;

void insert(Heap *h, int val) {
	if(h->size == MAX) {
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

void heapify(Heap *h, int i) {
	int smallest = i;
	int left = 2*i + 1;
	int right = 2*i + 2;

	if(left < h->size && h->heap[left] < h->heap[smallest]) smallest = left;
	if(right < h->size && h->heap[right] < h->heap[smallest]) smallest = right;

	if(smallest != i) {
		int temp = h->heap[i];
		h->heap[i] = h->heap[smallest];
		h->heap[smallest] = temp;
		heapify(h, smallest);
	}
	
}
void delete(Heap *h, int i) {
	
	if(i<0 || i>h->size) {
		printf("Out of Bounds");
		return;
	}

	h->heap[i] = h->heap[h->size-1];
	h->size--;
	heapify(h, 0);

}

void displayKthSmallestElement(Heap *h, int k) {

	//remove the smallest element
	//heapify it to find the next smallest element
	//repeat it k times to find the kth smal
	Heap tempHeap = *h;
    for (int i = 0; i < k; i++) {
        tempHeap.heap[0] = tempHeap.heap[tempHeap.size - 1];
        tempHeap.size--;
        heapify(&tempHeap, 0);
    }
    printf("%d\n", tempHeap.heap[0]);
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
		
		printf("1- Insert element\n2- Delete element\n3- kth Smallest Element\n4- Display\n");
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
					int ind;
					printf("Enter index i to be deleted: ");
					scanf("%d", &ind);
					delete(&h, ind);
					break;
				}
			case 3:
				{
					int k;
					printf("Enter k: ");
					scanf("%d", &k);
					displayKthSmallestElement(&h, k);
					break;
				}
			case 4:
				{
					display(h.heap, &h.size);
					break;
				}
			default: return 0;	
		}
	}
	


}
