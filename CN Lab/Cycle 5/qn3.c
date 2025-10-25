#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_SIZE 3
#define TOTAL_FRAMES 10

int ack[TOTAL_FRAMES] = {0};
int received[TOTAL_FRAMES] = {0};

void sendFrame(int frameNumber) {
    printf("Sender: Sending frame %d\n", frameNumber);
}

int receiveFrame(int frameNumber) {
    if (rand() % 3) {
        printf("Receiver: Frame %d received\n", frameNumber);
        received[frameNumber] = 1;
        return 1;
    } else {
        printf("Receiver: Frame %d lost\n", frameNumber);
        return 0;
    }
}

void sendACK(int frameNumber) {
    printf("Receiver: Sending ACK %d\n", frameNumber);
}

int receiveACK(int frameNumber) {
    if (received[frameNumber]) {
        if (rand() % 3) {
            printf("Sender: ACK %d received\n", frameNumber);
            ack[frameNumber] = 1;
            return 1;
        } else {
            printf("Sender: ACK %d lost\n", frameNumber);
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int windowStart = 0;

    while (windowStart < TOTAL_FRAMES) {
        for (int i = windowStart; i < windowStart + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack[i]) {
                sendFrame(i);
            }
        }

        sleep(1);

        for (int i = windowStart; i < windowStart + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack[i] && receiveFrame(i)) {
                sendACK(i);
            }
        }

        sleep(1);

        for (int i = windowStart; i < windowStart + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            receiveACK(i);
        }

        while (windowStart < TOTAL_FRAMES && ack[windowStart]) {
            windowStart++;
        }

        sleep(2);
    }

    printf("Sender: All frames sent successfully.\n");
    return 0;
}
