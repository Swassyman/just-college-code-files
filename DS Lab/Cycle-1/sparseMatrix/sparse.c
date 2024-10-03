#include<stdio.h>
void display( int*rows, int arr[][3] ){
	printf("\n");
	for(int i = 0; i<=(*rows); i++){
		for(int j = 0; j<3; j++){
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
}
void init(int* rows, int* cols,int* count, int arr[][3]){
	arr[0][0] = *rows;
	arr[0][1] = *cols;
	arr[0][2] = *count;
}
void inputMatrix(int* rows, int* cols, int* count, int arr[][3]){
	init(rows, cols, count, arr);
	for(int k = 1; k<=*count; k++){
		printf("Enter row: ");
		scanf("%d", &arr[k][0]);
		printf("Enter column: ");
		scanf("%d", &arr[k][1]);
		printf("Enter non Zero Element: ");
		int element;
		scanf("%d", &element);
		if(element==0){
			printf("Try again\n");
			k--;
			continue;
		}
		arr[k][2] = element;
	}
}
void transposeMatrix(int* rows, int* cols, int* count, int arr[][3], int A[][3]){
	init(rows, cols, count, A);
	int k = 1;
	for(int i = 0; i<*rows; i++){
		for(int j = 1; j<=*count; j++){
			if(arr[j][1]==i){
				A[k][0] = arr[j][1];
				A[k][1] = arr[j][0];
				A[k][2] = arr[j][2];
				k++;
			}
		}
	}
}
int main(){
	int rows, cols;
	printf("Size of array: ");
	scanf("%d %d", &rows, &cols);
	printf("Number of Non-Zero Elements: ");
	int nonZeros;
	scanf("%d", &nonZeros);
	if(nonZeros>(rows*cols)){
		printf("ERROR: TOO MANY ELEMENTS FOR ARRAY\n");
		return 0;
	}
	int sparseMatrix[nonZeros+1][3];
	inputMatrix(&rows, &cols, &nonZeros, sparseMatrix); 
	display(&nonZeros, sparseMatrix);
	int transSparse[nonZeros+1][3];
	transposeMatrix(&rows, &cols, &nonZeros, sparseMatrix, transSparse);
	display(&nonZeros, transSparse);
	return 0;
}
