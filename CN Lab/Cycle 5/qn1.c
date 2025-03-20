#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define TOTAL_FRAMES 9

int send_frame(int frame_number) {
    printf("Sender: Sending frame %d\n", frame_number);
    return frame_number;
}

int receive_ack(int frame_number) {
    // randomly simulating loss of ack
    if (rand() % 2) {
        printf("Receiver: ACK %d received\n", frame_number);
        return 1;
    } else {
        printf("Receiver: ACK %d lost\n", frame_number);
        return 0;
    }
}

int receive_frame(int frame_number) {
    // randomly simulating frame loss
    if (rand() % 2) {
        printf("Receiver: Frame %d received\n", frame_number);
        return 1;
    } else {
        printf("Receiver: Frame %d lost\n", frame_number);
        return 0;
    }
}

void send_ack(int frame_number) {
    printf("Receiver: Sending ACK %d\n", frame_number);
}

int main() {
    srand(time(NULL));

    int frame_number = 0;
    int ack_received;

    while (frame_number < TOTAL_FRAMES) {
        int sent_frame = send_frame(frame_number);

        // Simulate frame transmission delay
        sleep(1);

        int frame_received = receive_frame(sent_frame);

        if (frame_received) {
            send_ack(frame_number);

            // Simulate ACK transmission delay
            sleep(1);

            ack_received = receive_ack(frame_number);

            if (ack_received) {
                printf("Sender: ACK %d received. Moving to next frame.\n", frame_number);
                frame_number++;
            } else {
                printf("Sender: ACK %d not received. Retransmitting frame %d.\n", frame_number, frame_number);
            }
        } else {
            printf("Sender: Frame %d lost. Retransmitting frame %d.\n", frame_number, frame_number);
        }

        sleep(2);
    }

    printf("Sender: All frames sent successfully.\n");
    return 0;
}