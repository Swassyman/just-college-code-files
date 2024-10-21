#include <stdio.h>
#include <stdlib.h>

void selectionSort(int arr[], int n) {

	for(int i = 0; i<n-1; i++)
		for(int j = i+1; j<n; j++)
			if(arr[i] > arr[j]) {
				arr[i] = arr[i] ^ arr[j];
				arr[j] = arr[i] ^ arr[j];
				arr[i] = arr[i] ^ arr[j];
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
					selectionSort(arr, n);
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