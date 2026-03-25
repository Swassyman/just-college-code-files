#include<stdio.h>

int front = -1, rear = -1;
int isEmpty(int a[], int n) {
	if(front == -1 && rear == -1) return 1;
	return 0;
}

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

int dequeue(int a[]){
	if(front == -1 && rear == -1) {
		printf("Queue Empty");
		return -1;
	}
	int vertex = a[front];
	if(front == rear){
		front = -1;
		rear = -1;
	}
	else
		front++;
	return vertex;
}

void addEdge(int numberOfNodes, int arr[][numberOfNodes], int x, int y) {
	arr[x][y] = 1;
	arr[y][x] = 1;
}

void bfs(
	 int numberOfNodes,  int matrix[][numberOfNodes], int visited[], int queue[]
	) {
		visited[0] = 1;
		enqueue(queue, numberOfNodes, 0);
		while(!isEmpty(queue, numberOfNodes)) {
			int vertex = dequeue(queue);
			printf("Node %d visited\n", vertex+1);
			
			for(int i = 0; i<numberOfNodes; i++) {
				if(matrix[vertex][i] == 1 && (!visited[i])) {
					enqueue(queue, numberOfNodes, i);
					visited[i] = 1;
				}	
			}
		
		}
		
}


int main() {
	int numberOfNodes = 0;
	printf("Enter number of nodes: ");
	scanf("%d", &numberOfNodes);

	int adjacencyMatrix[numberOfNodes][numberOfNodes];
	int visited[numberOfNodes];
	for(int i = 0; i<numberOfNodes; i++) {
		visited[i] = 0;
	}
	int queue[numberOfNodes];

	for(int i = 0; i<numberOfNodes; i++) {
		for(int j = 0; j<numberOfNodes; j++) {
			adjacencyMatrix[i][j] = 0;
		}
	}

	for(int i = 0; i<numberOfNodes; i++) {
		printf("Enter number of connected Nodes of node %d: ", i+1);
		int numberOfConnectedNodes = 0;
		scanf("%d", &numberOfConnectedNodes);

		for(int j = 0; j<numberOfConnectedNodes; j++) {
			printf("Enter connected node: ");
			int x = 0;
			scanf("%d", &x);
			x = x-1;
			addEdge(numberOfNodes, adjacencyMatrix, i, x);
		}
	}
	
	bfs(numberOfNodes, adjacencyMatrix, visited, queue);
}
