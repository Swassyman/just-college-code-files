#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_SIZE 3
#define TOTAL_FRAMES 10

int ack[TOTAL_FRAMES] = {0};
int received[TOTAL_FRAMES] = {0};

void send_frame(int frame_number) {
    printf("Sender: Sending frame %d\n", frame_number);
}

int receive_frame(int frame_number) {
    if (rand() % 3) {
        printf("Receiver: Frame %d received\n", frame_number);
        received[frame_number] = 1;
        return 1;
    } else {
        printf("Receiver: Frame %d lost\n", frame_number);
        return 0;
    }
}

void send_ack(int frame_number) {
    printf("Receiver: Sending ACK %d\n", frame_number);
}

int receive_ack(int frame_number) {
    if (received[frame_number]) {
        if (rand() % 3) {
            printf("Sender: ACK %d received\n", frame_number);
            ack[frame_number] = 1;
            return 1;
        } else {
            printf("Sender: ACK %d lost\n", frame_number);
        }
    }
    return 0;
}

int main() {
    srand(time(NULL));

    int window_start = 0;

    while (window_start < TOTAL_FRAMES) {
        for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack[i]) {
                send_frame(i);
            }
        }

        sleep(1);

        for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack[i] && receive_frame(i)) {
                send_ack(i);
            }
        }

        sleep(1);

        for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            receive_ack(i);
        }

        while (window_start < TOTAL_FRAMES && ack[window_start]) {
            window_start++;
        }

        sleep(2);
    }

    printf("Sender: All frames sent successfully.\n");
    return 0;
}
