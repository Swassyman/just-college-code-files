#include <stdio.h>
#include <math.h>
#include <stdlib.h>


int calculateHeight(int* tree, int* n) {

	return (int) log2(*n + 1);
}

void create(int* tree, int i, int* n) {
	int x;
	printf("Enter data: ");
	scanf("%d", &x);
	if(x == -1) {
		tree[i] = -1;
		return;
	}
	else {
		tree[i] = x;
		(*n)++;
	}

	printf("Enter Left Child of %d: ", tree[i]);
	create(tree, 2*i + 1, n);

	printf("Enter Right Child %d: ", tree[i]);
	create(tree, 2*i + 2, n);
	return;
}

void display(int* tree, int* n) {
	//print all data nodes
	for(int i = 0, j = 0; j < *n; i++) {
		if(tree[i] != -1) {
			printf("%d ", tree[i]);
			j++; //increment only when non null node
		}
	}
}

int main() {

	int tree[50];
	for(int i = 0; i<50; i++) tree[i] = -1; //initialise all nodes as null
	int nodeCount = 0;
	while(1) {
		int choice;
		printf("1- Create Tree\n2- Display Tree Level Order\n3- Height of The Tree\n");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				{
					create(tree, 0, &nodeCount);
					break;
				}
			case 2:
				{	
					display(tree, &nodeCount);
					printf("\n");
					break;
				}
			case 3:
				{
					printf("Height of the tree: %d\n", calculateHeight(tree, &nodeCount));
					break;
				}
			default:
				return 0;
		}	

	}


	return 0;
}
                                                                                                     