#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 100

struct msg {
    long priority;
    char text[MAX_TEXT];
};

int main() {
    int qid = msgget(2345, 0666 | IPC_CREAT);
    struct msg messages[3];

    for (int i = 0; i < 3; i++) {
        printf("Enter message %d: ", i + 1);
        fgets(messages[i].text, MAX_TEXT, stdin);
        printf("Enter priority: ");
        scanf("%ld", &messages[i].priority);
        while(getchar() != '\n');
    }

    for (int i = 0; i < 3; i++) {
        msgsnd(qid, &messages[i], strlen(messages[i].text) + 1, 0);
    }

    return 0;
}