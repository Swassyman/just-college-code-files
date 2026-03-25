#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;

sem_t empty;
sem_t full;
sem_t mutex;

void* producer(void* arg) {
    int item;
    while (1) {
        item = rand() % 100;
        sleep(1);

        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[count] = item;
        count++;
        printf("Produced: %d (Buffer size: %d)\n", item, count);

        sem_post(&mutex);
        sem_post(&full);
	}
	return NULL;
}

void* consumer(void* arg) {
    int item;
    while (1) {
        sleep(2);

        sem_wait(&full);
        sem_wait(&mutex);

        item = buffer[count - 1];
        count--;
        printf("Consumed: %d (Buffer size: %d)\n", item, count);

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t prod_thread, cons_thread;

    sem_init(&empty, 0, BUFFER_SIZE);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&prod_thread, NULL, producer, NULL);
    pthread_create(&cons_thread, NULL, consumer, NULL);

    pthread_join(prod_thread, NULL);
    pthread_join(cons_thread, NULL);

    sem_destroy(&empty);
    sem_destroy(&full);
    sem_destroy(&mutex);

    return 0;
}