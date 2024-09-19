#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct Node {
	char studentName[20];
	int rollNo;
	int marks;
	struct Node* next;
} Node;
Node* createNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if( newNode == NULL ) {
		printf("Memory could not be allocated\n");
		return NULL;
	}
	return newNode;
}
void insertFront( Node** head, char arr[], int rn, int mks ) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	if( newNode == NULL ) {
		printf("Memory could not be allocated\n");
		return;
	}
	strcpy(newNode -> studentName, arr);
	newNode -> rollNo = rn;
	newNode -> marks = mks;
	newNode->next = *head;
	*head = newNode;
}
void insert( Node** head, int pos, char arr[], int rn, int mks ) {
	Node* temp = *head;
	Node* newNode = (Node*)malloc(sizeof(Node));
	if( newNode == NULL ) {
		printf("Memory could not be allocated\n");
		return;
	}

	strcpy(newNode -> studentName, arr);
	newNode -> rollNo = rn;
	newNode -> marks = mks;

	if( pos==1 ) {
		insertFront( head, arr, rn, mks );
		return;
	}	
	for( int i = 1; i < pos - 1 ; i++ ) {
		temp = temp -> next;
	}
	newNode -> next = temp -> next;
	temp -> next = newNode;
}
void insertEnd(Node** head, char arr[], int rn, int mks) {
    Node* temp = *head;
    Node* newNode = (Node*)malloc(sizeof(Node));

    if (newNode == NULL) {
        printf("Memory could not be allocated\n");
        return;
    }

    // Set the values of the new node
    newNode->next = NULL;
    strcpy(newNode->studentName, arr);
    newNode->rollNo = rn;
    newNode->marks = mks;

    // If the list is empty, set the new node as the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // Traverse to the end of the list
    while (temp->next != NULL) {
        temp = temp->next;
    }

    // Add the new node to the end
    temp->next = newNode;
}
void deleteFront( Node** head ) {
	Node* ptr = *head;
	*head = (*head) -> next;
	free(ptr);
}
void delete( Node** head, int pos ) {
	if( (*head) -> next == NULL ) {
		*head = NULL;
		return;
	}
	Node* temp = *head;
	for( int i = 1; i < pos - 1 ; i++ ) {
		temp = temp -> next;
	}
	temp -> next = temp -> next -> next;
}
void deleteEnd( Node** head ) {
	if( (*head) -> next == NULL ) {
		*head = NULL;
		return;
	}
	Node* temp = *head;
	Node* ptr;
	while( temp -> next != NULL ) {
		ptr = temp;
		temp = temp -> next;
	}
	ptr -> next = NULL;
	temp = NULL;
	free(temp);
	
}
void display( Node* head ) {
	if( head == NULL ){
		printf("List is Empty\n");
		return;
	}
	Node* temp;
	temp = head;
	while( temp != NULL ) {
		printf("%s | %d | %d\n", temp -> studentName, temp -> rollNo, temp -> marks);
		temp = temp->next;
	}
	printf("\n");
}
int search(Node** head, int key){
	int pos = 1;
	Node* temp = *head;
	while( temp != NULL ) {
		if( temp -> rollNo == key ) {
			return pos;
		}
		temp = temp -> next;
		pos++;
	}
	return -1;
}
int main(){
	Node* temp;
	Node* head = NULL;
	Node* newNode;
	int roll;
	char name[20];
	int mks;
	menu:
	int choice;
	printf("1-Create a Record\n2-Search a Record\n3-Insert a Record\n4-Delete a Record\n5-Display Records\n6-Exit\n");
	scanf("%d", &choice);
	switch(choice) {
		case 1:
			newNode = createNode();

			printf("Enter the name: ");
			scanf(" %[^\n]s", name);
			strcpy(newNode -> studentName, name);
			printf("Enter the roll number: ");
			scanf("%d", &roll);
			newNode->rollNo = roll;

			printf("Enter marks: ");
			scanf("%d", &mks);
			newNode->marks = mks;

			goto insertionmenu;
		case 2:
			int key, pos = 0;
			printf("Enter roll number to search: ");
			scanf("%d", &key);
			int ind = search(&head, key);
			if( ind > 0 ) {
				printf("Record found! at %d\n", ind);	
			}
			else {
				printf("Record not available\n");
			}
			goto menu;
		case 3:
			newNode = createNode();

			printf("Enter the name: ");
			scanf(" %[^\n]s", name);
			strcpy(newNode -> studentName, name);

			printf("Enter the roll number: ");
			scanf("%d", &roll);
			newNode -> rollNo = roll;

			printf("Enter marks: ");
			scanf("%d", &mks);
			newNode -> marks = mks;

			insertionmenu:
			int insertionChoice;
			printf("1-At front\n2-Anywhere\n3-At end\n");
			scanf("%d", &insertionChoice);
			switch(insertionChoice) {
				case 1:
					insertFront(&head, name, roll, mks);
					goto menu;
				case 2:
					int position;
					printf("At what position: ");
					scanf("%d", &position);
					if( position <= 0 ) {
						printf("Invalid Position");
						goto menu;
					}
					insert(&head, position, name, roll, mks);
					goto menu;
				case 3:
					insertEnd(&head, name, roll, mks);
					goto menu;
			}
		case 4:
			if( head == NULL ) {
				printf("List is Empty - Operation cannot be performed\n");
				goto menu;
			}
			int deletionChoice;
			printf("1-At front\n2-Anywhere\n3-At end\n");
			scanf("%d", &deletionChoice);
			switch(deletionChoice) {
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
		case 5: 
			display(head);
			goto menu;
	}
	return 0;
}
