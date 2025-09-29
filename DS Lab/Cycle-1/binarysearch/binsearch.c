#include<stdio.h>
int compares = 0;
int ind = 0;
void bubbleSort(int arr[], int size){
	for(int i = 0; i<size; i++){
		for(int j = 0; j<size-1; j++){
			if(arr[j]>arr[j+1]){
				int temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
			}
		}
	}
}
int binarySearchRecursive(int arr[], int key, int low, int high){
	if(low>high)
		return 0;
	int mid = (high+low)/2;
	if(arr[mid] == key){
			ind = mid;
			return 1;
		}
	else compares++;
	if(arr[mid] > key)
		return binarySearchRecursive(arr, key, low, mid-1);
	else
		return binarySearchRecursive(arr, key, mid+1, high);	
	return 0;
}
int binarySearchIterative(int arr[], int size, int key){
	int low = 0, high = size-1;
	while(low!=high){
		int mid = (low+high)/2;
		compares++;
		if(arr[mid] == key){
			ind = mid;
			return 1;
		}
		if(arr[mid] > key)
			high = mid-1;
		else
			low = mid+1;
	}
	return 0;
}
void main(){
	int n;
	printf("Enter size of array ");
	scanf("%d", &n);
	int a[n];
	printf("Enter elements into the array");
	for(int i = 0; i<n;i++){
		scanf("%d", &a[i]);
	}
	bubbleSort(a, n);
	int element;
	printf("Enter element to be found: ");
	scanf("%d", &element);
	int choice;
	menu:
	printf("Enter what method you want to search with:\n 1- Recursive\n 2- Iterative\n3- Exit\n");
	scanf("%d", &choice);
	switch(choice){
		case 1: 
				if(binarySearchRecursive(a, element, 0, n-1))
					printf("Element found at position %d! (with %d comparisons)\n", ind, compares);
				else
					printf("Element not found at position %d (with %d comparisons)\n", ind, compares);
				compares = 0;
				ind = 0;
				goto menu;
		case 2: 
				if(binarySearchIterative(a, n, element))
					printf("Element found at position %d! (with %d comparisons)\n", ind, compares);
				else
					printf("Element not found at position %d (with %d comparisons)\n", ind, compares);
				compares = 0;
				ind = 0;
				goto menu;
		case 3:
			return;
		default:
			printf("ERR: Wrong Input");
			goto menu;
	}
}
