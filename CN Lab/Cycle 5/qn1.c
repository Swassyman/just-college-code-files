#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_FRAMES 9

int sendFrame(int frameNumber) {
    printf("Sender: Sending frame %d\n", frameNumber);
    return frameNumber;
}

int receiveACK(int frameNumber) {
    // randomly simulating loss of ack
    if (rand() % 2) {
        printf("Receiver: ACK %d received\n", frameNumber);
        return 1;
    } else {
        printf("Receiver: ACK %d lost\n", frameNumber);
        return 0;
    }
}

int receiveFrame(int frameNumber) {
    // randomly simulating frame loss
    if (rand() % 2) {
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

int main() {
    srand(time(NULL));

    int frameNumber = 0;
    int ACKreceived;

    while (frameNumber < TOTAL_FRAMES) {
        int sentFrame = sendFrame(frameNumber);

        // Simulate frame transmission delay
        sleep(1);

        int frameReceived = receiveFrame(sentFrame);

        if(!frameReceived) {
            printf("Sender: Frame %d lost. Retransmitting frame %d.\n", frameNumber, frameNumber);
            continue;
        }
        else {
            sendACK(frameNumber);

            // Simulate ACK transmission delay
            sleep(1);

            ACKreceived = receiveACK(frameNumber);

            if (ACKreceived) {
                printf("Sender: ACK %d received. Moving to next frame.\n", frameNumber);
                frameNumber++;
            } else {
                printf("Sender: ACK %d not received. Retransmitting frame %d.\n", frameNumber, frameNumber);
            }
        }

        sleep(2);
    }

    printf("Sender: All frames sent successfully.\n");
    return 0;
}