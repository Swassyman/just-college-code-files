#include <stdio.h>
#include <stdlib.h>

void merge(int* A, int* B, int low, int mid, int high) {
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        if (A[i] <= A[j]) B[k++] = A[i++];
        else B[k++] = A[j++];
    }

    if(i>mid) {
    	while (j <= high) {
        	B[k++] = A[j++];
    	}
    } else {
    	while (i <= mid) {
        	B[k++] = A[i++];
    	}
    }
    

    for (i = low; i <= high; i++) {
        A[i] = B[i];
    }
}


void mergeSort(int* arr, int* res, int low, int high) {
		if(low >= high) return;

		int mid = (high+low)/2;

		mergeSort(arr, res, low, mid);
		mergeSort(arr, res, mid+1, high);
		merge(arr, res, low, mid, high);
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
	int* res = (int*)malloc(sizeof(int));

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
					mergeSort(arr, res, 0, n-1);
					break;
				}
			case 2:
				{
					display(res, n);
					break;
				}
			default: return 0;
		}
	}

	return 0;
}