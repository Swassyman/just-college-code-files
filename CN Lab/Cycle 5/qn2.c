#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

void send_frame(int frame_number) {
    printf("Sender: Sending frame %d\n", frame_number);
}

int receive_frame(int frame_number) {
    if (rand() % 3) {
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

int receive_ack(int expected_ack, int last_ack) {
    if (rand() % 3) {
        printf("Sender: ACK %d received\n", last_ack);
        return 1;
    } else {
        return 0;
    }
}

int main() {
    srand(time(NULL));

    int window_start = 0;
    int ack_received = -1;

    while (window_start < TOTAL_FRAMES) {
        for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            send_frame(i);
        }

        sleep(1);

        int last_in_order_frame = window_start - 1;
        for (int i = window_start; i < window_start + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (receive_frame(i)) {
                last_in_order_frame = i;
            } else {
                break;
            }
        }

        if (last_in_order_frame >= window_start) {
            send_ack(last_in_order_frame);
        }

        sleep(1);

        if (receive_ack(window_start, last_in_order_frame)) {
            printf("Sender: ACK %d received. Sliding window forward.\n", last_in_order_frame + 1);
            window_start = last_in_order_frame + 1;
        } else {
            printf("Sender: ACK lost. Resending frames from %d.\n", window_start);
        }

        sleep(2);
    }

    printf("Sender: All frames sent successfully.\n");
    return 0;
}
