#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int coeff;
	int power;
	struct Node* next;
} Node;

Node* createNode(int coeff, int power) {
	Node* newNode = (Node*)malloc(sizeof(Node));	
	newNode->coeff = coeff;
	newNode->power = power;
	newNode->next = NULL;
	return newNode;
}

void makeTerm(Node** head, int n) {
	int coeff, power;
	for(int i = 0; i < n; i++){
		printf("Enter coefficient and power: ");
		scanf("%d %d", &coeff, &power);

		Node* newNode = createNode(coeff, power);	
			if(newNode == NULL) {
				printf("Memory not allocated.");
				return;
			}
			if(*head == NULL) {
				*head = newNode;
				continue;
			}
			else{
				Node* temp = *head;
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newNode;
			}
	}
}

void add(Node** head, Node** head1, Node** head2) {
	Node* temp1 = *head1;
	Node* temp2 = *head2;	

	while(temp1 != NULL && temp2 != NULL) {
		if(temp1->power > temp2->power) {
			Node* newNode = createNode(temp1->coeff, temp1->power);
			
			if(*head == NULL) {
				*head = newNode;
			}
			else{
				Node* temp = *head;
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newNode;
			}

			temp1 = temp1->next;
		}
		else if( temp1->power < temp2->power) {
			Node* newNode = createNode(temp2->coeff, temp2->power);
			
			if(*head == NULL) {
				*head = newNode;
			}
			else{
				Node* temp = *head;
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newNode;
			}

			temp2 = temp2->next;
		}
		else {
			Node* newNode = createNode(temp1->coeff + temp2->coeff, temp1->power);	
			
			if(*head == NULL) {
				*head = newNode;
			}
			else{
				Node* temp = *head;
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newNode;
			}

			temp1 = temp1->next;
			temp2 = temp2->next;

		}
	}
}

void multiply(Node** head, Node** head1, Node** head2) {
	Node* temp1 = *head1;
	Node* temp2 = *head2;
	while(temp1 != NULL) {
		temp2 = *head2;	
		while(temp2 != NULL) {
			Node* newNode = createNode(temp1->coeff * temp2->coeff, temp1->power + temp2->power);
			if(*head == NULL) {
				*head = newNode;
			}
			else{
				Node* temp = *head;
				while(temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = newNode;
			}
			temp2 = temp2->next;
		}
		temp1 = temp1->next;
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
			printf("%dx^%d", temp->coeff, temp->power);
		else
			printf("%dx^%d + ", temp->coeff, temp->power);
		temp = temp->next;
	}
	printf("\n");
}
int main() {
	Node* headProduct = NULL;
	Node* headSum = NULL;
	Node* head1 = NULL;
	Node* head2 = NULL;
	int n1, n2;
	printf("Enter number of terms of first polynomial: ");
	scanf("%d", &n1);
	makeTerm(&head1, n1);
	printf("Enter number of terms of second polynomial: ");
	scanf("%d", &n2);
	makeTerm(&head2, n2);
	add(&headSum, &head1, &head2);
	display(headSum);
	multiply(&headProduct, &head1, &head2);
	display(headProduct);
	return 0;
}