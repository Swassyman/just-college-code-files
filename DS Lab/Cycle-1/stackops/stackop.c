#include<stdio.h>
int top = -1;
void push(int a[],int n, int item){
	if(top==n-1)
		printf("Stack Overflow");
	else{
		a[++top] = item;
	}
}
int pop(int a[], int n){
	if(top==-1)
		printf("Stack Underflow");
	else{
		return a[top--];
	}
}
void display(int a[], int n){
	for(int i = top; i>=0;i--)
		printf("\n%d ",a[i]);
}
void main(){
	int n;    
	printf("Enter size of stack: ");
	scanf("%d", &n);
	int S[n];
	int choice; 
	menu:
	printf("Enter the action you want to do:\n1 - Enter an integer\n2- Remove the top integer\n3- Display last popped\n4- Display the stack\n5- Exit\n");
	scanf("%d",&choice);
	int lastPopped = 0;
	switch(choice){
		case 1:
			printf("Enter number you want to add\n");
			int num;
			scanf("%d",&num);
			push(S,n,num);
			goto menu;
		case 2:
			lastPopped = pop(S, n);
			goto menu;
		case 3:
			printf("Last popped: %d", lastPopped);
			goto menu;
		case 4:
			display(S, n);
			goto menu;
		case 5:
			return;
		default:
			printf("ERR: Wrong Input");
			goto menu;
	}
}
