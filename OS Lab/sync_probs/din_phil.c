#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5  // Number of philosophers

sem_t forks[N];
sem_t mutex;

void think(int id) {
    printf("Philosopher %d is thinking.\n", id);
    sleep(rand() % 3 + 1);
}

void eat(int id) {
    printf("Philosopher %d is eating.\n", id);
    sleep(rand() % 3 + 1);
    printf("Philosopher %d finished eating.\n", id);
}

void* philosopher(void* num) {
    int id = *(int*)num;
    int left = id;
    int right = (id + 1) % N;

    while (1) {
        think(id);

        sem_wait(&mutex); // Ensure only one philosopher picks up forks
        if (sem_trywait(&forks[left]) == 0) {
            if (sem_trywait(&forks[right]) == 0) {
                sem_post(&mutex); // Release mutex before eating
                eat(id);
                sem_post(&forks[left]);
                sem_post(&forks[right]);
            } else {
                sem_post(&forks[left]); // Couldn’t get right fork, release left
                sem_post(&mutex);
            }
        } else {
            sem_post(&mutex);
        }
    }

    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t philosophers[N];
    int ids[N];

    // Initialize semaphores
    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++) {
        sem_init(&forks[i], 0, 1);
    }

    // Create threads
    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL, philosopher, &ids[i]);
    }

    // Join threads (unreachable in infinite loop, for completeness)
    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    return 0;
}
