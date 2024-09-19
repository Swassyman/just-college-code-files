#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
}Node;
void insertFront(Node** head,Node** last, int x){
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL){
		printf("Memory could not be allocated\n");
		return;
	}
	newNode->data = x;
	if(*head==NULL){
		newNode->next = newNode;
        *head = newNode;
        *last = newNode;
	}
	else{
		newNode->next = *head;
		*head = newNode;
		(*last)->next = *head;
	}
}
void insert(Node** head, Node** last, int pos, int x){
	Node* temp = *head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL){
		printf("Memory could not be allocated\n");
		return;
	}
	newNode->data = x;
	if(pos==1){
		insertFront(head, last, x);
		return;
	}	
	for(int i = 1; i<pos-1; i++){
		temp = temp->next;
	}
	newNode->next = temp->next;
	temp->next = newNode;
	if(newNode->next==NULL){
		*last = newNode;
	}
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
	Node* head = NULL, * newNode;
	Node* last->next = head;
	int x;
	printf("Enter data of first node");
	scanf("%d", &x);
	newNode = (Node*)malloc(sizeof(Node));
	if(newNode == NULL){
		printf("Memory could not be allocated\n");
		return 0;
	}
	newNode->data = x;
	newNode->next = last;
	menu:
	int choice;
	printf("1-Insertion\n2-Deletion\n3-Display\n4-Exit\n");
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
					insertFront(&head, &last, item);
					goto menu;
				case 2:
					int position;
					printf("At what position: ");
					scanf("%d", &position);
					if(position<=0){
						printf("Invalid Position");
						goto menu;
					}
					insert(&head, &last, position, item);
					goto menu;
			}
	}
	
	return 0;
}
