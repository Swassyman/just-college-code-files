#include <stdio.h>
#include <stdbool.h>

bool isSafe(int P, int R, int alloc[][R], int max[][R], int avail[]) {
    int work[R];
    bool finish[P];
    int safeSeq[P];
    int count = 0;

    for (int i = 0; i < R; i++) {
        work[i] = avail[i];
    }

    for (int p = 0; p < P; p++) {
        finish[p] = false;
    }

    while (count < P) {
        bool found = false;
        for (int p = 0; p < P; p++) {
            if (!finish[p]) {
                bool canAllocate = true;
                for (int r = 0; r < R; r++) {
                    if (max[p][r] - alloc[p][r] > work[r]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    for (int r = 0; r < R; r++) {
                        work[r] += alloc[p][r];
                    }
                    safeSeq[count++] = p;
                    finish[p] = true;
                    found = true;
                }
            }
        }
        if (!found) return false;
    }

    printf("\nSafe Sequence: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSeq[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int noProcesses, noResources;

    printf("Enter the number of processes: ");
    scanf("%d", &noProcesses);
    printf("Enter the number of resources: ");
    scanf("%d", &noResources);

    int available[noResources];
    int max[noProcesses][noResources];
    int alloc[noProcesses][noResources];

    printf("Enter the available resources (R1 R2 R3 ...): ");
    for (int i = 0; i < noResources; i++) {
        scanf("%d", &available[i]);
    }

    printf("\nEnter the maximum resources required by each process:\n");
    for (int i = 0; i < noProcesses; i++) {
        printf("Process %d (R1 R2 R3 ...): ", i);
        for (int j = 0; j < noResources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("\nEnter the allocated resources for each process:\n");
    for (int i = 0; i < noProcesses; i++) {
        printf("Process %d (R1 R2 R3 ...): ", i);
        for (int j = 0; j < noResources; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    if (isSafe(noProcesses, noResources, alloc, max, available)) {
        printf("\nThe system is in a safe state.\n");
    } else {
        printf("\nThe system is not in a safe state.\n");
    }

    return 0;
}