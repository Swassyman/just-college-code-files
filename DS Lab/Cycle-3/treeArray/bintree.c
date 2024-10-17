#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int calculateHeight(int* tree, int n) {
	int nodeCount = 0;
	//count number of nodes
	for(int i = 0; i<n; i++) {
		if(tree[i] != -999) nodeCount++;
	}

	return (int) log2(nodeCount + 1);
}
void display(int* tree, int n) {

	//print all data nodes
	for(int i = 0; i < n; i++) {
		if(tree[i] != -999) printf("%d ", tree[i]);
		else printf("null ");
	}
}

int main() {

	int n;
	printf("Enter number of nodes available in the tree: ");
	scanf("%d", &n);

	int* tree = (int*) malloc(n * sizeof(int));

	for(int i = 0; i < n; i++) {
		printf("Enter data for node %d: ", i + 1);	
		scanf("%d", &tree[i]);
	}

	while(1) {
		int choice;
		printf("1- Display Tree Level Order\n2- Height of The Tree\n");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				{	
					display(tree, n);
					printf("\n");
					break;
				}
			case 2:
				{
					printf("%d\n", calculateHeight(tree, n));
					break;
				}
			case 3:
				return 0;
		}	

	}


	return 0;
}