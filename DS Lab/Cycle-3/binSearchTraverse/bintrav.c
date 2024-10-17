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

void preOrder(Node* root) {
	if(root == NULL) return;

	printf("%d ", root->val);
	preOrder(root->left);
	preOrder(root->right);
}

void postOrder(Node* root) {
	if(root == NULL) return;

	postOrder(root->left);
	postOrder(root->right);
	printf("%d ", root->val);
}

void inOrder(Node* root) {
	if(root == NULL) return;

	inOrder(root->left);
	printf("%d ", root->val);
	inOrder(root->right);
}

int main() {

	Node* root = NULL;

	while(1) {
		int choice;
		printf("1- Create tree\n2- Traverse\n3- Exit\n");
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
					int traverseChoice;
					printf("1- Preorder\n2- Inorder\n3- Postorder\n");
					scanf("%d", &traverseChoice);

					switch(traverseChoice) {
						case 1: {
							printf("Preorder: ");
							preOrder(root);
							printf("\n");
							break;
						}
						case 2: {
							printf("Inorder: ");
							inOrder(root);	
							printf("\n");
							break;
						}
						case 3:
							{
								printf("Postorder: ");
								postOrder(root);
								printf("\n");
								break;
							}
						default: break;
					}
				}
				default: break;
		}
	}
	return 0;
}