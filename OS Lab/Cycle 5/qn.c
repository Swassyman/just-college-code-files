#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define ROWS_A 2
#define COLS_A 3
#define COLS_B 2

int A[ROWS_A][COLS_A] = {{1, 2, 3}, {4, 5, 6}};
int B[COLS_A][COLS_B] = {{7, 8}, {9, 10}, {11, 12}};
int C[ROWS_A][COLS_B];

typedef struct {
    int row;
    int col;
} Thread;

void* multiply_element(void* arg) {
    Thread* data = (Thread*) arg;
    int row = data->row;
    int col = data->col;
    free(data);
    
    int *result = malloc(sizeof(int));
    *result = 0;
    for (int k = 0; k < COLS_A; k++) {
        *result += A[row][k] * B[k][col];
    }
    pthread_exit(result);
}

int main() {
    pthread_t threads[ROWS_A][COLS_B];
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            Thread* data = malloc(sizeof(Thread));
            data->row = i;
            data->col = j;
            pthread_create(&threads[i][j], NULL, multiply_element, data);
        }
    }

    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            int* result;
            pthread_join(threads[i][j], (void**)&result);
            C[i][j] = *result;
            free(result);
        }
    }

    printf("Resultant Matrix:\n");
    for (int i = 0; i < ROWS_A; i++) {
        for (int j = 0; j < COLS_B; j++) {
            printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}
