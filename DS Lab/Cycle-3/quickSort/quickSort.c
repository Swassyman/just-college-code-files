#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}
int partition(int* arr, int low, int high) {
	int i = low, j = high, pivot = low;

	while(i<j) {
		while(arr[i] <= arr[pivot] && i<high) i++; //find right position from left
		while(arr[j] > arr[pivot] && j>low) j--; //find right position from right

		if(i<j) {
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[j] , &arr[pivot]);
	return j;
}

void quickSort(int* arr, int low, int high) {
	
	if(low < high) {
		int j = partition(arr, low, high);
		quickSort(arr, low, j-1); //sort left side
		quickSort(arr, j+1, high); //sort right side
	}
}

void display(int arr[], int n) {
	
	for(int i = 0; i<n;i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

}

int main() {

	int n;
	printf("Enter number of elements present in array: ");
	scanf("%d", &n);

	int* arr = (int*)malloc(sizeof(int));

	printf("Enter elements: ");
	for(int i = 0; i<n;i++) {
		scanf("%d", &arr[i]);
	}

	while(1) {
		int choice;
		printf("1- Sort Array\n2- Display array\n");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				{
					quickSort(arr, 0, n-1);
					break;
				}
			case 2:
				{
					display(arr, n);
					break;
				}
			default: return 0;
		}
	}

	return 0;
}