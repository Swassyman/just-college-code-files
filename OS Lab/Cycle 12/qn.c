#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DISK_SIZE 200

int findSmallest(int arr[], int n) {
    int min = arr[0];
    for(int i = 1; i<n; i++) {
        if(min > arr[i]) min = arr[i];
    }
    return min;
}

int findLargestNumberLessThanHead(int arr[], int n, int head) {
    int max = 0;
    for(int i = 0; i<n; i++) {
        if(max < arr[i] && arr[i] < head) max = arr[i];
    }
    return max;
}

void fcfs(int requests[], int n, int head) {
    int movements = 0;
    for(int i = 0; i<n; i++) {
        movements += abs(head - requests[i]);
        head = requests[i];
    }

    printf("Total number of head movements: %d", movements);
}

void scan(int requests[], int n, int head) {
    int movements = 0;
    int smallestTrack = findSmallest(requests, n);
    movements = (DISK_SIZE - 1 - head) + (DISK_SIZE - 1 - smallestTrack);

    printf("Total number of head movements: %d", movements);
}

void c_scan(int requests[], int n, int head) {
    int movements = 0;
    int closestHead = findLargestNumberLessThanHead(requests, n, head);

    movements = (DISK_SIZE - 1 - head) + (DISK_SIZE - 1) + closestHead;

    printf("Total number of head movements: %d", movements);
}

int main() {
    int diskRequests = 9;
    // printf("Enter number of disk requests: ");
    // scanf("%d", &diskRequests);

    int requests[] = {86, 147, 91, 177, 94, 150, 102, 175, 130};
    // printf("Enter requests:\n");
    // for(int i = 0; i<diskRequests; i++) {
    //     scanf("%d", &requests[i]);
    // }

    int head = 143;
    // printf("Enter initial head position: ");
    // scanf("%d", &head);

    int choice;
    while(1) {
        printf("\nDisk Scheduling Algorithms:\n");
        printf("1. FCFS (First-Come-First-Serve)\n");
        printf("2. SCAN (Elevator)\n");
        printf("3. C-SCAN (Circular SCAN)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
        case 1:
            fcfs(requests, diskRequests, head);
            break;
        case 2:
            scan(requests, diskRequests, head);
            break;
        case 3:
            c_scan(requests, diskRequests, head);
            break;
        case 4: return 0;
        default: continue;
        }
    }
    return 0;
}