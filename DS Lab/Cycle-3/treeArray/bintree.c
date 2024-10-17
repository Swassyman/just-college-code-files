#include <stdio.h>
#include <math.h>
#include <stdlib.h>


void create(int* tree, int i, int nodeCount) {
	if(tree[0] == -1) {
		printf("Enter data for root node: ");
		scanf("%d", &tree[0]);
	}

	int choice;
	printf("1- Add left child\n2- Add right child\n3- Add none\n");
	scanf("%d", &choice);	
	if(choice == 1) {
		printf("Enter data for left child: ");
		scanf("%d", &tree[2 * i + 1]);
		create(tree, 2 * i + 1, nodeCount);
		nodeCount++;
	}
	else if(choice == 2) {
		printf("Enter data for right child: ");
		scanf("%d", &tree[2 * i + 2]);
		create(tree, 2 * i + 2, nodeCount);
		nodeCount++;
	}
	else {
		tree[i] = -1;
	}
}

int calculateHeight(int* tree, int n) {

	return (int) log2(n + 1);;
}

void display(int* tree, int n) {

	//print all data nodes
	for(int i = 0; i < n;) {
		if(tree[i] != -1) {
			printf("%d ", tree[i]);
			i++;
		}
	}
}


int main() {

	int tree[50];
	tree[0] = -1;
	int nodeCount = 0;
	while(1) {
		int choice;
		printf("1- Create Tree\n2- Display Tree Level Order\n3- Height of The Tree\n");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				{
					create(tree, 0, nodeCount);
					break;
				}
			case 2:
				{	
					display(tree, nodeCount);
					printf("\n");
					break;
				}
			case 3:
				{
					printf("%d\n", calculateHeight(tree, nodeCount));
					break;
				}
			case 4:
				return 0;
		}	

	}


	return 0;
}