#include <stdio.h>
#include <stdlib.h>

#define MAX_ROUTERS 10
#define INFINITY 9999

int cost_matrix[MAX_ROUTERS][MAX_ROUTERS];
int num_routers;

// Structure for Distance Vector Routing
typedef struct {
    int distance[MAX_ROUTERS];
    int next_hop[MAX_ROUTERS];
} DistanceVector;

void initialize_dvr(DistanceVector routers[]) {
    for (int i = 0; i < num_routers; i++) {
        for (int j = 0; j < num_routers; j++) {
            if (i == j) {
                routers[i].distance[j] = 0;
                routers[i].next_hop[j] = j;
            } else if (cost_matrix[i][j] != 0) {
                routers[i].distance[j] = cost_matrix[i][j];
                routers[i].next_hop[j] = j;
            } else {
                routers[i].distance[j] = INFINITY;
                routers[i].next_hop[j] = -1;
            }
        }
    }
}

// Update distance vectors using Bellman-Ford equation for DVR
void update_distance_vectors(DistanceVector routers[]) {
    int updated;
    do {
        updated = 0;
        for (int i = 0; i < num_routers; i++) {
            for (int j = 0; j < num_routers; j++) {
                if (cost_matrix[i][j] != 0) {
                    for (int k = 0; k < num_routers; k++) {
                        // check if distance of i to k is larger than i to j + j to k
                        if (routers[i].distance[k] > routers[i].distance[j] + routers[j].distance[k]) {
                            routers[i].distance[k] = routers[i].distance[j] + routers[j].distance[k];
                            routers[i].next_hop[k] = j;
                            updated = 1;
                        }
                    }
                }
            }
        }
    } while (updated);
}

void print_distance_vector(int router, DistanceVector routers[]) {
    printf("Router %d Distance Vector:\n", router);
    for (int i = 0; i < num_routers; i++) {
        printf("  -> Router %d: Cost = %d, Next Hop = %d\n", i, routers[router].distance[i], routers[router].next_hop[i]);
    }
}

void dijkstra(int source, int distance[], int next_hop[]) {
    int visited[MAX_ROUTERS] = {0};

    for (int i = 0; i < num_routers; i++) {
        distance[i] = INFINITY;
        next_hop[i] = -1;
    }
    distance[source] = 0;

    for (int count = 0; count < num_routers - 1; count++) {
        int min_distance = INFINITY, min_index = -1;
        for (int v = 0; v < num_routers; v++) {
            if (!visited[v] && distance[v] <= min_distance) {
                min_distance = distance[v];
                min_index = v;
            }
        }

        visited[min_index] = 1;

        for (int v = 0; v < num_routers; v++) {
            if (!visited[v] && cost_matrix[min_index][v] && distance[min_index] != INFINITY &&
                distance[min_index] + cost_matrix[min_index][v] < distance[v]) {
                distance[v] = distance[min_index] + cost_matrix[min_index][v];
                next_hop[v] = min_index;
            }
        }
    }
}

// Print the shortest paths from a router for LSR
void print_shortest_paths(int source, int distance[], int next_hop[]) {
    printf("Router %d Shortest Paths:\n", source);
    for (int i = 0; i < num_routers; i++) {
        printf("  -> Router %d: Cost = %d, Next Hop = %d\n", i, distance[i], next_hop[i]);
    }
}

int main() {
    int choice;
    DistanceVector routers[MAX_ROUTERS];

    printf("Enter the number of routers: ");
    scanf("%d", &num_routers);

    printf("Enter the cost matrix (0 for no direct link):\n");
    for (int i = 0; i < num_routers; i++) {
        for (int j = 0; j < num_routers; j++) {
            scanf("%d", &cost_matrix[i][j]);
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
                for (int i = 0; i < num_routers; i++) {
                    print_distance_vector(i, routers);
                }
                break;

            case 2:
                printf("\nShortest Paths:\n");
                for (int i = 0; i < num_routers; i++) {
                    int distance[MAX_ROUTERS], next_hop[MAX_ROUTERS];
                    dijkstra(i, distance, next_hop);
                    print_shortest_paths(i, distance, next_hop);
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