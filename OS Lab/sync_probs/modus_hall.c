#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_HEATHENS 10
#define NUM_PRUDES 10

typedef enum {NEUTRAL, HEATHENS_RULE, PRUDES_RULE, TRANSITION_TO_HEATHENS, TRANSITION_TO_PRUDES} Status;

int heathens = 0;
int prudes = 0;
Status status = NEUTRAL;

sem_t mutex;
sem_t heathenTurn;
sem_t prudeTurn;
sem_t heathenQueue;
sem_t prudeQueue;

void* heathen(void* arg) {
    sem_wait(&heathenTurn);
    sem_post(&heathenTurn);

    sem_wait(&mutex);
    heathens++;

    if (status == NEUTRAL) {
        status = HEATHENS_RULE;
        sem_post(&mutex);
    } else if (status == PRUDES_RULE) {
        if (heathens > prudes) {
            status = TRANSITION_TO_HEATHENS;
            sem_wait(&prudeTurn);
            sem_post(&mutex);
            sem_wait(&heathenQueue);
        } else {
            sem_post(&mutex);
            sem_wait(&heathenQueue);
        }
    } else if (status == TRANSITION_TO_HEATHENS) {
        sem_post(&mutex);
        sem_wait(&heathenQueue);
    } else {
        sem_post(&mutex);
    }

    printf("Heathen %ld is crossing...\n", (long)arg);
    sleep(rand() % 2 + 1);
    printf("Heathen %ld finished crossing.\n", (long)arg);

    sem_wait(&mutex);
    heathens--;
    if (heathens == 0) {
        if (status == TRANSITION_TO_PRUDES) {
            sem_post(&prudeTurn);
        }
        if (prudes > 0) {
            for (int i = 0; i < prudes; i++) sem_post(&prudeQueue);
            status = PRUDES_RULE;
        } else {
            status = NEUTRAL;
        }
    } else if (status == HEATHENS_RULE && prudes > heathens) {
        status = TRANSITION_TO_PRUDES;
        sem_wait(&heathenTurn);
    }
    sem_post(&mutex);
    return NULL;
}

void* prude(void* arg) {
    sem_wait(&prudeTurn);
    sem_post(&prudeTurn);

    sem_wait(&mutex);
    prudes++;

    if (status == NEUTRAL) {
        status = PRUDES_RULE;
        sem_post(&mutex);
    } else if (status == HEATHENS_RULE) {
        if (prudes > heathens) {
            status = TRANSITION_TO_PRUDES;
            sem_wait(&heathenTurn);
            sem_post(&mutex);
            sem_wait(&prudeQueue);
        } else {
            sem_post(&mutex);
            sem_wait(&prudeQueue);
        }
    } else if (status == TRANSITION_TO_PRUDES) {
        sem_post(&mutex);
        sem_wait(&prudeQueue);
    } else {
        sem_post(&mutex);
    }

    printf("Prude %ld is crossing...\n", (long)arg);
    sleep(rand() % 2 + 1);
    printf("Prude %ld finished crossing.\n", (long)arg);

    sem_wait(&mutex);
    prudes--;
    if (prudes == 0) {
        if (status == TRANSITION_TO_HEATHENS) {
            sem_post(&heathenTurn);
        }
        if (heathens > 0) {
            for (int i = 0; i < heathens; i++) sem_post(&heathenQueue);
            status = HEATHENS_RULE;
        } else {
            status = NEUTRAL;
        }
    } else if (status == PRUDES_RULE && heathens > prudes) {
        status = TRANSITION_TO_HEATHENS;
        sem_wait(&prudeTurn);
    }
    sem_post(&mutex);
    return NULL;
}

int main() {
    srand(time(NULL));
    pthread_t hThreads[NUM_HEATHENS];
    pthread_t pThreads[NUM_PRUDES];

    sem_init(&mutex, 0, 1);
    sem_init(&heathenTurn, 0, 1);
    sem_init(&prudeTurn, 0, 1);
    sem_init(&heathenQueue, 0, 0);
    sem_init(&prudeQueue, 0, 0);

    for (long i = 0; i < NUM_HEATHENS; i++) {
        pthread_create(&hThreads[i], NULL, heathen, (void*)i);
        usleep(rand() % 200000);
    }

    for (long i = 0; i < NUM_PRUDES; i++) {
        pthread_create(&pThreads[i], NULL, prude, (void*)i);
        usleep(rand() % 200000);
    }

    for (int i = 0; i < NUM_HEATHENS; i++) {
        pthread_join(hThreads[i], NULL);
    }

    for (int i = 0; i < NUM_PRUDES; i++) {
        pthread_join(pThreads[i], NULL);
    }

    return 0;
}
