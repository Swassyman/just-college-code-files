#include <stdio.h>
#include <stdlib.h>

#define MAX_ROUTERS 10
#define INFINITY 9999

int costMatrix[MAX_ROUTERS][MAX_ROUTERS];
int numRouters;

typedef struct {
    int distance[MAX_ROUTERS];
    int nextHop[MAX_ROUTERS];
} DistanceVector;

void initialize_dvr(DistanceVector routers[]) {
    for (int i = 0; i < numRouters; i++) {
        for (int j = 0; j < numRouters; j++) {
            if (i == j) {
                routers[i].distance[j] = 0;
                routers[i].nextHop[j] = j;
            } else if (costMatrix[i][j] != 0) {
                routers[i].distance[j] = costMatrix[i][j];
                routers[i].nextHop[j] = j;
            } else {
                routers[i].distance[j] = INFINITY;
                routers[i].nextHop[j] = -1;
            }
        }
    }
}

// Update distance vectors using Bellman-Ford equation for DVR
void update_distance_vectors(DistanceVector routers[]) {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < numRouters; i++) { //each router's table
            for (int j = 0; j < numRouters; j++) { //i to j link is checked
                if (i != j) {
                    for (int k = 0; k < numRouters; k++) { //all other paths are checked
                        if (routers[i].distance[j] != INFINITY && routers[j].distance[k] != INFINITY) {
                            int minDist = routers[i].distance[j] + routers[j].distance[k];
                            if (minDist < routers[i].distance[k]) {
                                routers[i].distance[k] = minDist;
                                routers[i].nextHop[k] = routers[i].nextHop[j];
                                updated = 1;
                            }
                        }
                    }
                }
            }
        }
    } while (updated);
}

void print_distance_vector(int router, DistanceVector routers[]) {
    printf("Router %d Distance Vector:\n", router);
    for (int i = 0; i < numRouters; i++) {
        printf("  -> Router %d: Cost = %d, Next Hop = %d\n", i, routers[router].distance[i], routers[router].nextHop[i]);
    }
}

void dijkstra(int source, int distance[], int nextHop[]) {
    int visited[MAX_ROUTERS] = {0};

    for (int i = 0; i < numRouters; i++) {
        distance[i] = INFINITY;
        nextHop[i] = -1;
    }
    distance[source] = 0;

    for (int count = 0; count < numRouters - 1; count++) {
        int minDistance = INFINITY, min_index = -1;
        for (int v = 0; v < numRouters; v++) {
            if (!visited[v] && distance[v] <= minDistance) {
                minDistance = distance[v];
                min_index = v;
            }
        }

        visited[min_index] = 1;

        for (int v = 0; v < numRouters; v++) {
            if (!visited[v] && costMatrix[min_index][v] && distance[min_index] != INFINITY &&
                distance[min_index] + costMatrix[min_index][v] < distance[v]) {
                distance[v] = distance[min_index] + costMatrix[min_index][v];
                nextHop[v] = min_index;
            }
        }
    }
}

// Print the shortest paths from a router for LSR
void print_shortest_paths(int source, int distance[], int nextHop[]) {
    printf("Router %d Shortest Paths:\n", source);
    for (int i = 0; i < numRouters; i++) {
        printf("  -> Router %d: Cost = %d, Next Hop = %d\n", i, distance[i], nextHop[i]);
    }
}

int main() {
    int choice;
    DistanceVector routers[MAX_ROUTERS];

    printf("Enter the number of routers: ");
    scanf("%d", &numRouters);

    printf("Enter the cost matrix (0 for no direct link):\n");
    for (int i = 0; i < numRouters; i++) {
        for (int j = 0; j < numRouters; j++) {
            scanf("%d", &costMatrix[i][j]);
        }
    }

    while (1) {
        printf("\nMenu:\n");
        printf("1. Distance Vector Routing (DVR)\n");
        printf("2. Link State Routing (LSR)\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                initialize_dvr(routers);
                update_distance_vectors(routers);
                printf("\nFinal Distance Vectors:\n");
                for (int i = 0; i < numRouters; i++) {
                    print_distance_vector(i, routers);
                }
                break;

            case 2:
                printf("\nShortest Paths:\n");
                for (int i = 0; i < numRouters; i++) {
                    int distance[MAX_ROUTERS], nextHop[MAX_ROUTERS];
                    dijkstra(i, distance, nextHop);
                    print_shortest_paths(i, distance, nextHop);
                }
                break;

            case 3:
                printf("Exiting...\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}