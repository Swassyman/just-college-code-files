#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char musicName[50];
    int durationSeconds;
    char musicArtist[20];
    struct Node* next;
} Node;

Node* createNode() {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory could not be allocated\n");
        return NULL;
    }
    return newNode;
}

void insertFront(Node** head, Node** last, char name[], int duration, char artist[]) {
    Node* newNode = createNode();
    if (newNode == NULL) return;

    strcpy(newNode->musicName, name);
    strcpy(newNode->musicArtist, artist);
    newNode->durationSeconds = duration;

    if (*head == NULL) {
        newNode->next = newNode;
        *head = newNode;
        *last = newNode;
    } else {
        newNode->next = *head;
        *head = newNode;
        (*last)->next = *head;
    }
}

void insert(Node** head, Node** last, int pos, char name[], int duration, char artist[]) {
    if (pos == 1) {
        insertFront(head, last, name, duration, artist);
        return;
    }

    Node* temp = *head;
    Node* newNode = createNode();
    if (newNode == NULL) return;

    strcpy(newNode->musicName, name);
    strcpy(newNode->musicArtist, artist);
    newNode->durationSeconds = duration;

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    if (newNode->next == NULL) {
        *last = newNode;
    }
}
void insertEnd(Node** head, Node** last, char name[], int duration, char artist[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory could not be allocated\n");
        return;
    }
    
    strcpy(newNode->musicName, name);
    strcpy(newNode->musicArtist, artist);
    newNode->durationSeconds = duration;

    if (*head == NULL) {
        newNode->next = newNode; // Point to itself for circular structure
        *head = newNode;
        *last = newNode;
    } else {
        newNode->next = *head;
        (*last)->next = newNode;
        *last = newNode; // Update last pointer
    }
}

void deleteFront(Node** head, Node** last) {
    if (*head == NULL) {
        printf("List is Empty\n");
        return;
    }

    Node* temp = *head;
    if (*head == *last) { // Only one element in the list
        *head = NULL;
        *last = NULL;
    } else {
        *head = (*head)->next;
        (*last)->next = *head; // Maintain circular structure
    }
    free(temp);
}

void deletePosition(Node** head, Node** last, int pos) {
    Node* temp = *head;
    if (pos == 1) {
        deleteFront(head, last);
        return;
    }

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }

    Node* temp2 = temp->next;
    temp->next = temp->next->next;

    // If the last node is deleted, update the last pointer
    if (temp2 == *last) {
        *last = temp;
        (*last)->next = *head; // Maintain circular structure
    }

    free(temp2);
}

void deleteEnd(Node** head, Node** last) {
    if (*head == NULL) {
        printf("List is Empty\n");
        return;
    }

    // Handle the case when there is only one node
    if (*head == *last) {
        free(*head);
        *head = NULL;
        *last = NULL;
        return;
    }

    // Traverse the list to find the node before the last node
    Node* temp = *head;
    while (temp->next != *last) {
        temp = temp->next;
    }

    // Update the next pointer of the node before the last
    temp->next = *head;
    
    // Free the last node and update the last pointer
    free(*last);
    *last = temp;
}
void display(Node* head, int times) {
    if (head == NULL) {
        printf("List is Empty\n");
        return;
    }

    Node* temp = head;
    int count = 0;
    do {
        printf("Playing %s ~ %s : %d seconds\n", temp->musicName, temp->musicArtist, temp->durationSeconds);
        temp = temp->next;
        if (temp == head) {
            count++;
            printf("-----------------------------------\n");
        }
    } while (count < times);
    printf("\n");
}

int main() {
    Node* head = NULL;
    Node* last = NULL;

    int duration;
    char name[50], artist[20];

    while (1) {
        int choice;
        printf("1-Insert a Song\n2-Delete a Song\n3-Play\n4-Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int insertionChoice;
                printf("1-At front\n2-Anywhere\n3-At end\n");
                scanf("%d", &insertionChoice);

                printf("Enter name of the music: ");
                scanf(" %[^\n]s", name);

                printf("Enter name of the artist: ");
                scanf(" %[^\n]s", artist);

                printf("Enter duration in seconds: ");
                scanf("%d", &duration);

                if (insertionChoice == 1) {
                    insertFront(&head, &last, name, duration, artist);
                } else if (insertionChoice == 2) {
                    int position;
                    printf("At what position: ");
                    scanf("%d", &position);

                    if (position <= 0) {
                        printf("Invalid Position\n");
                    } else {
                        insert(&head, &last, position, name, duration, artist);
                    }

                }
                else if (insertionChoice == 3) {
                	insertEnd(&head, &last, name, duration, artist);
                }
                break;
            }
        	case 2: {
	        	int deletionChoice;
	        	printf("1-At front\n2-Anywhere\n3-At end\n");
	        	scanf("%d", &deletionChoice);

	        	if (deletionChoice == 1) {
	        		deleteFront(&head, &last);
	        	}
	        	else if (deletionChoice == 2) {
	        		int position;
	        		printf("At what position: ");
	        		scanf("%d", &position);

	        		if (position <= 0) {
	        			printf("Invalid Position\n");
	        		}
	        		else deletePosition(&head, &last, position);
	        	}
	        	break;
        	}
            case 3: {
                int loop;
                printf("Do you want to keep looping?\n1- Yes\n0- No\n");
                scanf("%d", &loop);

                if (loop) {
                    int times;
                    printf("Enter number of times to loop: ");
                    scanf("%d", &times);
                    display(head, times);
                } else {
                    display(head, 1);
                }
                break;
            }

            case 4:
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }
    return 0;
}
