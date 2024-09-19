#include<stdio.h>
int compares = 0;
void bubbleSort(int arr[], int size){
	for(int i = 0; i<size-1; i++){
		for(int j = 0; j<size-1; j++){
			if(arr[j]>arr[j+1]){
				int temp = arr[j+1];
				arr[j+1] = arr[j];
				arr[j] = temp;
				compares++;
			}
		}
	}
}
void display(int arr[], int size){
	for(int i = 0; i<size;i++){
		printf("%d ",arr[i]);
	}
	printf(" With %d iterations", compares);
}
void main(){
	int n;
	printf("Enter the size of the array: ");
	scanf("%d", &n);
	int arr[n];
	printf("Enter the values into the array\n");
	for(int i = 0; i<n;i++){
		scanf("%d",&arr[i]);
	}
	bubbleSort(arr, n);
	display(arr, n);
}                                                                                                                               
