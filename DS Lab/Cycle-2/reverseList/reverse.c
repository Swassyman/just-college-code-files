#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
} Node;
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
void reverse(Node** head){
	Node* prev, * curr, * succ;
	prev = NULL;
	curr = *head;
	while(curr!=NULL){
		succ = curr->next;
		curr->next = prev;
		prev = curr;
		curr = succ;
	}
	*head = prev;
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
			printf("%d->", temp->data);
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
	printf("1-Insertion\n2-Reverse\n3-Display\n4-Exit\n");
	scanf("%d", &choice);
	switch(choice){
		case 1:
			int item;
			printf("Enter data ");
			scanf("%d", &item);
			int position;
			printf("At what position: ");
			scanf("%d", &position);
			if(position<=0){
				printf("Invalid Position");
				goto menu;
			}
			insert(&head, position, item);
			goto menu;
		case 2:
			reverse(&head);
			goto menu;
		case 3:
			display(head);
			goto menu;
		default: break;
	return 0;
	}
}
