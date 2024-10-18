#include<stdio.h>
#include<stdlib.h>

void insertSort(int* arr, int n) {

	for(int i = 1; i<n; i++) {
		int key = arr[i];
		int j = i-1;

		while(j>=0 && arr[j]>key) {
			arr[j+1] = arr[j];
			j = j-1;
		}
		arr[j+1] = key;
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
					insertSort(arr, n);
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