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
    int qid = msgget(2345, 0666);
    struct msg received;

    printf("Messages in priority order:\n");
    for (int p = 3; p >= 0; p--) {
        msgrcv(qid, &received, MAX_TEXT, p, 0);
        printf("%s", received.text);
    }

    msgctl(qid, IPC_RMID, 0);
    return 0;
}