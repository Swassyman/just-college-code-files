#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_SIZE 3
#define TOTAL_FRAMES 10

void sendFrame(int frameNumber) {
    printf("Sender: Sending frame %d\n", frameNumber);
}

int receiveFrame(int frameNumber) {
    if (rand() % 3) {
        printf("Receiver: Frame %d received\n", frameNumber);
        return 1;
    } else {
        printf("Receiver: Frame %d lost\n", frameNumber);
        return 0;
    }
}

void sendACK(int frameNumber) {
    printf("Receiver: Sending ACK %d\n", frameNumber);
}

int receiveACK(int lastACK) {
    if (rand() % 3) {
        printf("Sender: ACK %d received\n", lastACK);
        return 1;
    } else {
        return 0;
    }
}

int main() {
    srand(time(NULL));

    int windowStart = 0;
    int ack_received = -1;

    while (windowStart < TOTAL_FRAMES) {
        for (int i = windowStart; i < windowStart + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            sendFrame(i);
        }

        sleep(1);

        int lastInOrderFrame = windowStart - 1;
        for (int i = windowStart; i < windowStart + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (receiveFrame(i)) {
                lastInOrderFrame = i;
            } else {
                break;
            }
        }

        if (lastInOrderFrame >= windowStart) {
            sendACK(lastInOrderFrame);
        }

        sleep(1);

        if (receiveACK(lastInOrderFrame)) {
            printf("Sliding window forward.\n");
            windowStart = lastInOrderFrame + 1;
        } else {
            printf("Sender: ACK lost. Resending frames from %d.\n", windowStart);
        }

        sleep(2);
    }

    printf("Sender: All frames sent successfully.\n");
    return 0;
}
