#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Node {
	char modelName[20];
	int priceModel;
	char manufacturerName[50];
	int engineCapacity;
	struct Node* prev;
	struct Node* next;
}Node;

Node* createNode(){
	Node* newNode = (Node*)malloc(sizeof(Node));

	//check for null alloc
	if (newNode == NULL) {
		printf("Memory cannot be allocated");
		return NULL;
	}
	return newNode;
}

void insertFront(Node** head, char model[], char manufacturer[], int price, int engine) {
	Node* newNode = createNode();
	if(newNode == NULL) {
		return;
	}

	strcpy(newNode -> modelName, model);
	strcpy(newNode -> manufacturerName, manufacturer);
	newNode -> priceModel = price;
	newNode -> engineCapacity = engine;

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

void insertAnywhere(Node** head, char model[], char manufacturer[], int price, int engine, int pos) {
	Node* newNode = createNode();
	if(newNode == NULL) {
		return;
	}

	strcpy(newNode -> modelName, model);
	strcpy(newNode -> manufacturerName, manufacturer);
	newNode -> priceModel = price;
	newNode -> engineCapacity = engine;

	//check for invalid position
	if (pos <= 0) {
		printf("Invalid Position\n");
		free(newNode);
		return;
	}

	//if to insert at front
	if (pos == 1) {
		insertFront(head, model, manufacturer, price, engine);
		return;
	}

	//loop till temp is before position
	Node* temp = *head;
	for(int i = 1; i<pos-1; i++){
		temp = temp->next;
	}

	//if position is out of bounds
	if (temp == NULL) {
		printf("Out of Bounds\n");
		free(newNode);
		return;
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

void insertEnd(Node** head, char model[], char manufacturer[], int price, int engine) {
	Node* newNode = createNode();
	if(newNode == NULL) {
		return;
	}

	strcpy(newNode -> modelName, model);
	strcpy(newNode -> manufacturerName, manufacturer);
	newNode -> priceModel = price;
	newNode -> engineCapacity = engine;

	// if list is empty
	if(*head == NULL) {
		insertFront(head, model, manufacturer, price, engine);
	}
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

	if(*head == NULL) {
		printf("List is Empty\n");
		return;
	}

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

	if(*head == NULL) {
		printf("List is Empty\n");
		return;
	}
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
		printf("\n%s\n", temp -> modelName);
		printf("%s\n", temp -> manufacturerName);
		printf("%d\n", temp -> priceModel);
		printf("%d\n", temp-> engineCapacity);
		printf("-----------------------------");
		temp = temp->next;
	}
	printf("\n");
}
void updatePrice(Node** head, int pos){
	int newPrice;
	printf("Enter the new price of the model: ");
	scanf("%d", &newPrice);

	//traverse till required model
	Node* temp = *head;
	for (int i = 1; i < pos; i++) {
		if (temp == NULL) {
			printf("Exceeded Bounds of List\n");
			return ;
		}
		temp = temp -> next;
	}

	temp -> priceModel = newPrice;
}
void searchPriceRange(Node** head) {
	if(*head == NULL){
		printf("List is Empty\n");
		return;
	}

	//set bounds of price range
	int lowerPrice, upperPrice;
	printf("Enter lower bound of price: ");
	scanf("%d", &lowerPrice);
	printf("Enter upper bound of price: ");
	scanf("%d", &upperPrice);

	Node* temp;
	temp = *head;
	while(temp!=NULL) {
		if(temp -> priceModel > lowerPrice && temp -> priceModel < upperPrice){
			printf("\n%s\n", temp -> modelName);
			printf("%d\n", temp -> priceModel);
			// printf("%s\n", temp -> manufacturerName);
			// printf("%d\n", temp-> engineCapacity);
			printf("-----------------------------");
		}
		temp = temp->next;
	}
	printf("\n");
}
void searchModelName(Node** head) {
	char name[20];
	printf("Enter name of Model to search: ");
	scanf(" %[^\n]s", name);

	Node* temp;
	temp = *head;
	while(temp!=NULL) {
		if(strcmp(temp -> modelName, name) == 0) {
			printf("\n%s\n", temp -> modelName);
			printf("%d\n", temp -> priceModel);
			printf("%s\n", temp -> manufacturerName);
			printf("%d\n", temp-> engineCapacity);
			printf("-----------------------------");
		}
		temp = temp->next;
	}
	printf("\n");
}
int main() {
	Node* head = NULL;
	char model[20];
	char manufacturer[50];
	int price;
	int engine;

	//menu 
	int choice;
	menu:
	printf("1- Insert a node\n2- Delete a node\n3- Display the nodes\n4- Update prices of Models\n5- Search for a model\n6- Exit\n");
	scanf("%d", &choice);

	switch(choice) {
	case 1:
		{
			//insert menu
			int insertionChoice;
			printf("1- Insert at Front\n2- Insert at position\n3- Insert at end\n");
			scanf("%d", &insertionChoice);
			
			//scan for data
			printf("Enter Model Name: ");
			scanf(" %[^\n]s", model);
			printf("Enter Manufacturer Name: ");
			scanf(" %[^\n]s", manufacturer);
			printf("Enter price of the model: ");
			scanf("%d", &price);
			printf("Enter the engine capacity: ");
			scanf("%d", &engine);

			switch(insertionChoice) {
			case 1:
				{
					insertFront(&head, model, manufacturer, price, engine);
					goto menu;
				}
			case 2:
				{
					int position;
					printf("Enter position to insert: ");
					scanf("%d", &position);
					insertAnywhere(&head, model, manufacturer, price, engine, position);
					goto menu;
				}
			case 3:
				{
					insertEnd(&head, model, manufacturer, price, engine);
					goto menu;
				}
			}
		}
	case 2:
		{
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
	case 4:
		{
			int updatePosition;
			printf("Enter position of Model to update: ");
			scanf("%d", &updatePosition);
			updatePrice(&head, updatePosition);
			goto  menu;
		}
	case 5:
		{
			int searchChoice;
			printf("1- Price Range\n2- Model Details\n");
			scanf("%d", &searchChoice);

			switch (searchChoice) {
			case 1:
				{
					searchPriceRange(&head);
					goto menu;
				}
			case 2:
				{
					searchModelName(&head);
					goto menu;
				}
			default: goto menu;
			}
		}
	default: return 0;
	}
	return 0;
}