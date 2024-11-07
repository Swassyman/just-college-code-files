#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct userNode {
    char name[20];
    int id;
    struct userNode* next;
} userNode;

userNode* search(userNode* vertexArray, int numberofNodes, int id) {
    for (int i = 0; i < numberofNodes; i++) {
        if (vertexArray[i].id == id) {
            return &vertexArray[i];
        }
    }
    return NULL;
}

void addFriends(userNode* vertexArray, userNode* vertex, int numberofNodes) {
    printf("Enter number of friends of %s. ", vertex->name);
    printf("Enter 0 if there are no friends left: ");

    int friendCount;
    scanf("%d", &friendCount);

    while (friendCount > 0) {
        int idToSearch = 0;
        printf("Enter ID of friend: ");
        scanf("%d", &idToSearch);

        userNode* friendNode = search(vertexArray, numberofNodes, idToSearch);

        if (friendNode != NULL) {
            userNode* newFriendConnection = malloc(sizeof(userNode));
            *newFriendConnection = *friendNode;

            newFriendConnection->next = vertex->next;
            vertex->next = newFriendConnection;
        } else {
            printf("User with ID %d not found.\n", idToSearch);
        }

        friendCount--;
    }
}

void display(userNode* vertex) {
    printf("%s -> ", vertex->name);
    if (vertex->next != NULL) {
        display(vertex->next);
    } else {
        printf("No next\n");
    }
}

int main() {
    int numberofNodes = 0;
    printf("Enter number of Users: ");
    scanf("%d", &numberofNodes);

    userNode vertexArray[numberofNodes];

    for (int i = 0; i < numberofNodes; i++) {
        printf("Enter Username: ");
        scanf(" %[^\n]s", vertexArray[i].name);

        printf("Enter ID: ");
        scanf("%d", &vertexArray[i].id);
        vertexArray[i].next = NULL;
    }

    for (int i = 0; i < numberofNodes; i++) {
        addFriends(vertexArray, &vertexArray[i], numberofNodes);
    }

    for (int i = 0; i < numberofNodes; i++) {
        printf("\n");
        display(&vertexArray[i]);
    }

    return 0;
}
