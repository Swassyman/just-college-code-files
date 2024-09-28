#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

void insertFront(Node** head, Node** last, int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory could not be allocated\n");
        return;
    }
    newNode->data = x;
    if (*head == NULL) {
        newNode->next = newNode; // Point to itself for circular structure
        *head = newNode;
        *last = newNode;
    } else {
        newNode->next = *head;
        *head = newNode;
        (*last)->next = *head; // Make it circular
    }
}

void insert(Node** head, Node** last, int pos, int x) {
    Node* temp = *head;
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory could not be allocated\n");
        return;
    }
    newNode->data = x;
    if (pos == 1) {
        insertFront(head, last, x);
        return;
    }

    for (int i = 1; i < pos - 1; i++) {
        temp = temp->next;
    }

    newNode->next = temp->next;
    temp->next = newNode;

    // If newNode is inserted at the end, update the last pointer
    if (temp == *last) {
        *last = newNode;
        (*last)->next = *head; // Maintain circular structure
    }
}

void insertEnd(Node** head, Node** last, int x) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory could not be allocated\n");
        return;
    }
    newNode->data = x;

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

    Node* temp = *head;
    if (*head == *last) { // Only one element
        *head = NULL;
        *last = NULL;
    } else {
        while (temp->next != *last) {
            temp = temp->next;
        }
        temp->next = *head;
        free(*last);
        *last = temp; // Update last pointer
    }
}

void display(Node* head) {
    if (head == NULL) {
        printf("List is Empty\n");
        return;
    }

    Node* temp = head;
    do {
        printf("%d -> ", temp->data);
        temp = temp->next;
    } while (temp != head); // Stop when it loops back to head

    printf("(back to head)\n");
}

int main() {
    Node* head = NULL, *last = NULL;
    int x;

    menu:
    {
        int choice;
        printf("1-Insertion\n2-Deletion\n3-Display\n4-Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                int insertionChoice;
                printf("1-At front\n2-Anywhere\n3-At end\n");
                scanf("%d", &insertionChoice);
                int item;
                printf("Enter the data: ");
                scanf("%d", &item);

                switch (insertionChoice) {
                    case 1:
                        insertFront(&head, &last, item);
                        goto menu;
                    case 2: {
                        int position;
                        printf("At what position: ");
                        scanf("%d", &position);
                        if (position <= 0) {
                            printf("Invalid Position\n");
                            goto menu;
                        }
                        insert(&head, &last, position, item);
                        goto menu;
                    }
                    case 3:
                        insertEnd(&head, &last, item);
                        goto menu;
                }
            }

            case 2: {
                int deletionChoice;
                printf("1-At front\n2-Anywhere\n3-At end\n");
                scanf("%d", &deletionChoice);

                switch (deletionChoice) {
                    case 1:
                        deleteFront(&head, &last);
                        goto menu;
                    case 2: {
                        int position;
                        printf("At what position: ");
                        scanf("%d", &position);
                        if (position <= 0) {
                            printf("Invalid Position\n");
                            goto menu;
                        }
                        deletePosition(&head, &last, position);
                        goto menu;
                    }
                    case 3:
                        deleteEnd(&head, &last);
                        goto menu;
                }
            }

            case 3:
                display(head);
                goto menu;

            case 4:
                return 0;

            default:
                goto menu;
        }
    }

    return 0;
}
