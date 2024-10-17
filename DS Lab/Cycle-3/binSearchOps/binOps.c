#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
	struct Node* left;
	struct Node* right;
	int val;
}Node;

Node* newNode(int val) {
	Node* n = (Node*)malloc(sizeof(Node));	
	n->val = val;
	n->left = n->right = NULL;
	return n;
}

Node* insert(Node* root, int val) {
	if(root == NULL) {
		return newNode(val);
	}	
	if(val < root->val) {
		root->left = insert(root->left, val);	
	}
	else {
		root->right = insert(root->right, val);
	}
	return root;
}

Node* findMin(Node* root) {
	if(root == NULL) {	
		return NULL;
	}
	if(root->left == NULL) {
		return root;
	}
	return findMin(root->left);
}

Node* delete(Node* root, int val) {
	if(root == NULL) {	
		return root;
	}
	if(val < root->val) {
		root->left = delete(root->left, val);
	}
	else if(val > root->val) {
		root->right = delete(root->right, val);
	}
	else {
		if(root->left == NULL && root->right == NULL) {
			root = NULL;
			free(root);
		}
		else if(root->left == NULL) {
			Node* temp = root;
			root = root->right;
			free(temp);
		}
		else if(root->right == NULL) {
			Node* temp = root;
			root = root->left;
			free(temp);
		}
		else {
			Node* temp = findMin(root->right);
			root->val = temp->val;
			root->right = delete(root->right, temp->val);
		}
	}
	return root;
}

void sort(Node* root) {
	if(root == NULL) return;

	sort(root->left);
	printf("%d ", root->val);
	sort(root->right);
}

int noLeafNodes(Node* root) {
	if(root == NULL) {		
		return 0;
	}
	if(root->left == NULL && root->right == NULL) {
		return 1;
	}
	return noLeafNodes(root->left) + noLeafNodes(root->right);
}

int main() {

	Node* root = NULL;

	while(1) {
		int choice;
		printf("1- Insert\n2- Delete\n3- Sort\n4- Print Number of Leaf Nodes\n");
		scanf("%d", &choice);

		switch(choice) {
			case 1:
				{
					int val;
					while(1) {
						printf("Enter value or -1 to exit: ");
						scanf("%d", &val);
						if(val == -1) {
							break;
						}
						root = insert(root, val);
					}
					break;
				}
			case 2:
				{
					int val;
					printf("Enter value or -1 to exit: ");
					scanf("%d", &val);
					root = delete(root, val);
					break;
				}
			case 3:
				{
					sort(root);
					break;
				}
			case 4:
				{
					printf("%d\n", noLeafNodes(root));;
					break;
				}
			default: return 0;
		}	
	}
	return 0;
}
