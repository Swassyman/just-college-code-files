//Haven't tested if it runs
//Does Compile with no error
#include<stdio.h>
int front = -1, rear = -1;
int isFull(int N){
	if(front == 0 && rear == N-1)
		return 1;
	else if(front == rear+1)
		return 1;
	return 0;
}
int isEmpty(){
	if(front == -1)
		return 0;
	return 1;
}
void enqueueFront(int* arr,int N, int item){
	if(isFull(N))
		printf("Dequeue Full\n");
	else if(front == -1 && rear == -1){
		front = 0;
		rear = 0;
		arr[front] = item;
	}
	else if(front == 0){
		front = N-1;
		arr[front] = item;
	}
	else
		arr[--front] = item;
}
void enqueueRear(int* arr, int N, int item){
	if(isFull(N))
		printf("Dequeue Full\n");
	else if(front == -1 && rear == -1){
		front = 0;
		rear = 0;
		arr[rear] = item;
	}
	else if(rear == N-1){
		rear = 0;
		arr[rear] = item;
	}
	else
		arr[++rear] = item;		
}
void dequeueFront(int* arr,int N){
	if(isEmpty()){
		printf("Deque Empty\n");
		return;
	}
	//int poppedElement = arr[front];
	if(front==rear){
		front = -1;
		rear = -1;
	}
	else if(front==N-1){
		front = 0;
	}
	else
		front++;
}
void dequeueRear(int* arr, int N){
	if(isEmpty()){
		printf("Dequeue Empty\n");
		return;
	}
	//int poppedElement = arr[rear];
	if(front == rear){
		front = -1;
		rear = -1;
	}
	else if(rear == 0){
		rear = N-1;
	}
	else
		rear--;
}
void display(int* arr, int N){
	if(front<rear){
		for(int i = front; i<=rear; i++)
			printf("%d", arr[i]);
	}
	else{
		for(int i = front; i<N; i++)
			printf("%d", arr[i]);
		for(int i = 0; i<=rear; i++)
			printf("%d", arr[i]);
	}
}
int main(){
	printf("Enter size of queue: ");
	int size;
	scanf("%d", &size);
	int S[size];
	int choice; 
	menu:
		printf("Enter the action you want to do:\n1 - Enter an integer\n2- Remove the top integer\n3- Display the deque\n4- Exit\n");
		scanf("%d",&choice);
		int insertionChoice, deletionChoice;
		switch(choice){
			case 1:
				menuInsertion:
					printf("1- Front Insertion\n2- Rear Insertion\n3- Go back\n");
					scanf("%d", &insertionChoice);
					printf("Enter number you want to add\n");
					int num;
					scanf("%d",&num);
					switch(insertionChoice){	
						case 1:
							enqueueFront(S, size, num);
							goto menuInsertion;
						case 2:
							enqueueRear(S, size, num);
							goto menuInsertion;
						case 3: goto menuInsertion;
						default:
							printf("ERR: Wrong Input\n");
							goto menuInsertion;
					}
				goto menu;
			case 2:
				menuDeletion:
					printf("1- Front Deletion\n2- Rear Deletion\n3- Go back\n");
					scanf("%d", &deletionChoice);
					switch(deletionChoice){	
						case 1:
							dequeueFront(S, size);
							goto menuDeletion;
						case 2:
							dequeueRear(S, size);
							goto menuDeletion;
						case 3: goto menuDeletion;
						default:
							printf("ERR: Wrong Input\n");
							goto menuDeletion;
					}
			case 3:
				display(S, size);
				goto menu;
			case 4:
				return 0;
			default:
				printf("ERR: Wrong Input\n");
				goto menu;
		}
	return 0;
}
