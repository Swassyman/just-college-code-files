#include <stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
	}
Node;
void insertFront(Node** head, int x){
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL){
		printf("Memory could not be allocated\n");
		return;
	}
	newNode->data = x;
	newNode->next = *head;
	*head = newNode;
}
void insert(Node** head, int pos, int x){
	Node* temp = *head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL){
		printf("Memory could not be allocated\n");
		return;
	}
	newNode->data = x;
	if(pos==1){
		insertFront(head, x);
		return;
	}	
	for(int i = 1; i<pos-1; i++){
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
}
void insertEnd(Node** head, int x){
	Node* temp = *head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL){
		printf("Memory could not be allocated\n");
		return ;
	}
	newNode->next = NULL;
	newNode->data = x;
	while(temp->next != NULL){
		temp = temp->next;
	}
	temp->next = newNode;
}
void swap(Node** head, int x, int y){
	int countX = 1, countY = 1;
	if( x == y ) return;
	Node* prevX = NULL;
	Node * currX = *head;
	while( currX && countX != x){
		prevX = currX;
		currX = currX -> next;
		countX++;
	}

	Node* prevY = NULL, * currY = *head;
	while( currY && countY != y){
		prevY = currY;
		currY = currY -> next;
		countY++;
	}

	if( currX == NULL || currY == NULL ) return;

	if(prevX != NULL)
		prevX -> next = currY;
	else
		*head = currY;

	if (prevY != NULL)
		prevY -> next = currX;
	else
		*head = currX;

	prevY -> next = currX;

	Node* temp = currX -> next;
	currX -> next = currY -> next;
	currY -> next = temp;

}
void display(Node* head){
	if(head == NULL){
		printf("List is Empty\n");
		return;
	}
	Node* temp;
	temp = head;
	while(temp!=NULL){
		if(temp->next==NULL)
			printf("%d", temp->data);
		else
			printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
int main(){
	Node* temp;
	Node* head;
	Node* newNode;
	int x;
	printf("Enter data of first node: ");
	scanf("%d" ,&x);
	newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL){
		printf("Memory could not be allocated\n");
		return 0;
	}
	head = newNode;
	temp = head;
	newNode->data = x;
	newNode->next = NULL;
	menu:
	int choice;
	printf("1-Insertion\n2-Swap\n3-Display\n4-Exit\n");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			int insertionChoice;
			printf("1-At front\n2-Anywhere\n3-At end\n");
			scanf("%d", &insertionChoice);
			int item;
			printf("Enter the data: ");
			scanf("%d", &item);
			switch(insertionChoice){
				case 1:
					insertFront(&head, item);
					goto menu;
				case 2:
					int position;
					printf("At what position: ");
					scanf("%d", &position);
					if(position<=0){
						printf("Invalid Position");
						goto menu;
					}
					insert(&head, position, item);
					goto menu;
				case 3:
					insertEnd(&head, item);
					goto menu;
			}
		case 2:
			int posX, posY;
			printf("Enter position of swapping nodes:\n");
			scanf("%d %d", &posX, &posY);
			swap(&head, posX, posY);
			goto menu;
		case 3: 
			display(head);
			goto menu;
		default:
			goto menu;
	}
	return 0;
}