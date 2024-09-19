#include<stdio.h>
int comparisons  = 0;
int ind = 0;
int linearsearch(int a[], int size, int num){
	for(int i = 0; i<size;i++){
		if(a[i] == num){
			ind = i;
			return 1+i;
		}
		else comparisons++;
	}
	return 0;
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
	int elementToBeFound;
	printf("Enter the element to search for: ");
	scanf("%d", &elementToBeFound);
	if(linearsearch(arr, n, elementToBeFound))
		printf("Value found at position %d! (with %d comparisons)\n", ind, comparisons);
	else 
		printf("Value not found at position %d (with %d comparisons)\n", ind, comparisons);
}
