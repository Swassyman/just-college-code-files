#include<stdio.h>
#include <stdlib.h>
typedef struct Node{
	int data;
	struct Node* next; 
}Node;
void createNode(Node** head, int item){
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->next = NULL;
	newNode->data = item;
	*head = newNode;
}
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
void display(Node* head){
	if(head == NULL){
		printf("List is Empty\n");
		return;
	}
	Node* temp;
	temp = head;
	while(temp!=NULL){
		printf("%d ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
void stackOps(int* top, int* len, Node** head){
	stackmenu:
		int stackChoice;
		printf("1- Push\n2- Pop\n3- Display\n");
		scanf("%d",&stackChoice);
		switch(stackChoice){
		case 1:
			int item;
			printf("Enter data to store\n");
			scanf("%d", &item);
			if(*top==(*len)-1){
				printf("Stack Overflow\n");
			}
			else if( *head==NULL){
				createNode(head, item);
				++(*top);
			}
			else{
				insertFront(head, item);
				++(*top);
			}
			goto stackmenu;
		case 2:
			if(*head==NULL || (*top)==-1){
				printf("Stack Underflow\n");
			}
			else{
				deleteFront(head);
				--(*top);
			}
			goto stackmenu;
		case 3:
			display(*head);
			goto stackmenu;
		default: return ;
	}
}
void queueOps(int* front, int* rear, int* len, Node** head){
	queuemenu:
		int queueChoice;
		printf("1- Enqueue\n2- Dequeue\n3- Display\n");
		scanf("%d", &queueChoice);
		switch(queueChoice){
		case 1:
			int item;
			printf("Enter data to store\n");
			scanf("%d", &item);
			if(*rear == (*len)-1)
				printf("Queue Full\n");
			else if(*front == -1 && *rear == -1){
				*front = 0;
				*rear = 0;
				createNode(head, item);
			}
			else{
				insertEnd(head, item);
				(*rear)++;
			}
			goto queuemenu;
		case 2:
			if(*front == -1 && *rear == -1)
				printf("Queue Empty\n");
			else if(*front == *rear){
				*front = -1;
				*rear = -1;
				deleteFront(head);
			}
			else{
				deleteFront(head);
				(*front)++;
			}
			goto queuemenu;
		case 3:
			display(*head);
			goto queuemenu;
		default: return ;
	}
}
void cqOps(int* front, int* rear, int* len, Node** head){
	cqmenu:
		int cqChoice;
		printf("1- Enqueue\n2- Dequeue\n3- Display\n");
		scanf("%d",&cqChoice);
		switch(cqChoice){
		case 1:
			int item;
			printf("Enter data to store\n");
			scanf("%d", &item);
			if( ((*rear)+1)%(*len) == (*front))
				printf("Queue Full\n");
			else if(*front == -1 && *rear == -1){
				*front = 0;
				*rear = 0;
				createNode(head, item);
			}
			else{
				insertEnd(head, item);
				*rear = ((*rear)+1)%(*len);
			}
			goto cqmenu;
		case 2:
			if(*front == -1 && *rear == -1)
				printf("Queue Empty\n");
			else if(*front == *rear){
				*front = -1;
				*rear = -1;
				deleteFront(head);
			}
			else{
				deleteFront(head);
				*front = ((*front)+1)%(*len);
			}
			goto cqmenu;
		case 3:
			display(*head);
			goto cqmenu;
		default: return;
		}
}
int main(){
	int topStack = -1;
	int frontQueue = -1, rearQueue = -1;
	int frontCQ = -1, rearCQ = -1;
	int stackLen, queueLen, cqLen;
	Node* headStack = NULL, * headQueue = NULL, * headCQ = NULL;
	
	printf("Enter length of Stack, Queue, Circular Queue\n");
	scanf("%d %d %d", &stackLen, &queueLen, &cqLen);
	mainmenu:
		int structChoice;
		printf("1- Stack\n2- Queue\n3- Circular Queue\n");
		scanf("%d", &structChoice);
		switch(structChoice){
		case 1:
			stackOps(&topStack, &stackLen, &headStack);
			goto mainmenu;
		case 2:
			queueOps(&frontQueue, &rearQueue, &queueLen, &headQueue);
			goto mainmenu;
		case 3:
			cqOps(&frontCQ, &rearCQ, &cqLen, &headCQ);
			goto mainmenu;
		default: return 0;
		}		
		return 0;
}