#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int data;
	struct Node* prev;
	struct Node* next;
}Node;

Node* createNode(){
	Node* newNode = (Node*)malloc(sizeof(Node));

	//check for null alloc
	if (newNode == NULL) {
		printf("Memory cannot be allocated");
	}
	return newNode;
}

void insertFront(Node** head, int x) {
	Node* newNode = createNode();
	newNode -> data = x;

	//if list is empty
	if (*head == NULL){
		newNode -> next = NULL;
		newNode -> prev = NULL;
		*head = newNode;
		return;
	}

	//update newNode
	newNode -> next = *head;
	newNode -> prev = NULL;

	//update head
	(*head) -> prev = newNode;
	*head = newNode;
}

void insertAnywhere(Node** head, int x, int pos) {
	Node* newNode = createNode();
	newNode -> data = x;

	//check for invalid position
	if (pos <= 0) {
		printf("Invalid Position\n");
		free(newNode);
		return;
	}

	//if to insert at front
	if (pos == 1) {
		insertFront(head, x);
		return;
	}

	//loop till temp is before position
	Node* temp = *head;
	for(int i = 1; i<pos-1; i++){
		temp = temp->next;
		//if position is out of bounds
		if (temp == NULL) {
			printf("Out of Bounds\n");
			free(newNode);
			return;
	}
	}


	//updating newnode
	newNode -> next = temp -> next;
	newNode -> prev = temp;

	//updating surrounding nodes
	if(temp -> next != NULL) {
		temp -> next -> prev = newNode;
	}
	temp -> next = newNode;
}

void insertEnd(Node** head, int x) {
	Node* newNode = createNode();
	newNode -> data = x;

	//traverse till the end
	Node* temp = *head;
	while(temp -> next != NULL) {
		temp = temp -> next;
	}

	//updating newnode
	newNode -> next = NULL;
	newNode -> prev = temp;

	//updating temp node
	temp -> next = newNode;
}

void deleteFront(Node** head) {
	Node* temp = *head;

	*head = temp -> next; //head is the next node
	(*head) -> prev = NULL; //the prev node of head is set to null
	
	free(temp);
}

void deleteAnywhere(Node** head, int pos) {
	//if position is valid
	if (pos <= 0) {
		printf("Invalid Position");
		return;
	}

	if (pos == 1) {
		deleteFront(head);
		return;
	}

	//traverse to the deleting node
	Node* temp = *head;
	for (int i = 1; i < pos; i++) {
		temp = temp -> next;
		if (temp == NULL) {
			printf("Out of Bounds\n");
			return;
	}
	}

	//deleting node
	Node* nodeToDelete = temp;
	if (nodeToDelete->prev != NULL) {
        nodeToDelete->prev->next = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL) {
        nodeToDelete->next->prev = nodeToDelete->prev;
    }	

    free(nodeToDelete);
}

void deleteEnd(Node** head) {
	Node* temp = *head;

	//if only one node is present
	if (temp->next == NULL) {
    	free(temp);       
        *head = NULL;     
        return;
    }

	while(temp -> next != NULL) {
		temp = temp -> next;
	}

	temp -> prev -> next = NULL;
	temp -> prev = NULL;

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
			printf("%d -> ", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
int main() {
	Node* head = NULL;

	//menu 
	int choice;
	menu:
	printf("1- Insert a node\n2- Delete a node\n3- Display the nodes\n4- Exit\n");
	scanf("%d", &choice);

	switch(choice) {
	case 1:
		{
			//insert menu
			int insertionChoice;
			printf("1- Insert at Front\n2- Insert at position\n3- Insert at end\n");
			scanf("%d", &insertionChoice);
			
			//scan for data
			int item;
			printf("Enter data of node: ");
			scanf("%d", &item);

			switch(insertionChoice) {
			case 1:
				{
					insertFront(&head, item);
					goto menu;
				}
			case 2:
				{
					int position;
					printf("Enter position to insert: ");
					scanf("%d", &position);
					insertAnywhere(&head, item, position);
					goto menu;
				}
			case 3:
				{
					insertEnd(&head, item);
					goto menu;
				}
			}
		}
	case 2:
		{
			if(head == NULL) {
				printf("List is Empty\n");
				goto menu;
			}
			//delete menu
			int deletionChoice;
			printf("1- Delete at Front\n2- Delete at position\n3- Delete at end\n");
			scanf("%d", &deletionChoice);

			switch(deletionChoice) {
			case 1:
				{
					deleteFront(&head);
					goto menu;
				}
			case 2:
				{
					int position;
					printf("Enter position to delete: ");
					scanf("%d", &position);
					deleteAnywhere(&head, position);
					goto menu;
				}
			case 3:
				{
					deleteEnd(&head);
					goto menu;
				}
			}
		}
	case 3:
		{
			display(head);
			goto menu;
		}
	default: return 0;
	}
	return 0;
}
