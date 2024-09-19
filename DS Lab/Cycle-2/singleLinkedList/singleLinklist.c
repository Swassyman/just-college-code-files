#include<stdio.h>
#include<stdlib.h>
typedef struct Node{
	int data;
	struct Node* next;
}Node;
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
void deleteFront(Node** head){
	Node* ptr = *head;
	*head = (*head)->next;
	free(ptr);
}
void delete(Node** head, int pos){
	if((*head)->next == NULL){
		*head = NULL;
		return;
	}
	Node* temp = *head;
	for(int i = 1; i<pos-1; i++){
		temp = temp->next;
	}
	temp->next = temp->next->next;
}
void deleteEnd(Node** head){
	if((*head)->next == NULL){
		*head = NULL;
		return;
	}
	Node* temp = *head;
	Node* ptr;
	while(temp->next != NULL){
		ptr = temp;
		temp = temp->next;
	}
	ptr->next = NULL;
	temp= NULL;
	free(temp);
	
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
			if(head==NULL){
				printf("List is Empty - Operation cannot be performed\n");
				goto menu;
			}
			int deletionChoice;
			printf("1-At front\n2-Anywhere\n3-At end\n");
			scanf("%d", &deletionChoice);
			switch(deletionChoice){
				case 1:
					deleteFront(&head);
					goto menu;
				case 2:
					int position;
					printf("At what position: ");
					scanf("%d", &position);
					delete(&head, position);
					goto menu;
				case 3:
					deleteEnd(&head);
					goto menu;
			}
			goto menu;
		case 3: 
			display(head);
			goto menu;
	}
	return 0;
}
