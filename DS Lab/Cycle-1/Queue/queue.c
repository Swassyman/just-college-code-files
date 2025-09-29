#include <stdio.h>
int front = -1, rear = -1;
void enqueue(int a[],int n, int item){
	if(rear==n-1)
		printf("Queue Full");
	else if(front == -1 && rear == -1){
		front = 0; 
		rear = 0;
		a[rear] = item;
	}
	else
		a[++rear] = item;
}
void dequeue(int a[]){
	if(front == -1 && rear == -1)
		printf("Queue Empty");
	else if(front == rear){
		front = -1;
		rear = -1;
	}
	else
		front++;
}
void display(int a[]){
	for (int i = front; i<=rear; i++)
		printf("%d ", a[i]);
	printf("\n");
}
void main(){
	printf("Enter size of queue: ");
	int size;
	scanf("%d", &size);
	int S[size];
	int choice; 
	menu:
	printf("Enter the action you want to do:\n1 - Enter an integer\n2- Remove the top integer\n3- Display the stack\n4- Exit\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:
			printf("Enter number you want to add\n");
			int num;
			scanf("%d",&num);
			enqueue(S,size,num);
			goto menu;
		case 2:
			dequeue(S);
			goto menu;
		case 3:
			display(S);
			goto menu;
		case 4:
			return;
		default:
			printf("ERR: Wrong Input\n");
			goto menu;
	}
}
