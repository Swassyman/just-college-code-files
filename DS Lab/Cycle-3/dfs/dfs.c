#include <stdio.h>

void addEdge(int numberOfNodes, int arr[][numberOfNodes], int x, int y) {
    arr[x][y] = 1;
    arr[y][x] = 1;
}

void dfs(int start, int numberOfNodes, int matrix[][numberOfNodes], int visited[]) {
    visited[start] = 1;
    printf("Node %d visited\n", start + 1);

    for (int i = 0; i < numberOfNodes; i++) {
        if (matrix[start][i] == 1 && (!visited[i])) {
            dfs(i, numberOfNodes, matrix, visited);
        }
    }
}

int main() {
    int numberOfNodes = 0;
    printf("Enter number of nodes: ");
    scanf("%d", &numberOfNodes);

    int adjacencyMatrix[numberOfNodes][numberOfNodes];
    int visited[numberOfNodes];

    // Initialize adjacency matrix and visited array
    for (int i = 0; i < numberOfNodes; i++) {
        visited[i] = 0;
        for (int j = 0; j < numberOfNodes; j++) {
            adjacencyMatrix[i][j] = 0;
        }
    }

    // Input edges for each node
    for (int i = 0; i < numberOfNodes; i++) {
        printf("Enter number of connected nodes for node %d: ", i + 1);
        int numberOfConnectedNodes = 0;
        scanf("%d", &numberOfConnectedNodes);

        for (int j = 0; j < numberOfConnectedNodes; j++) {
            printf("Enter connected node: ");
            int x = 0;
            scanf("%d", &x);
            x = x - 1; // Convert to zero-based index
            addEdge(numberOfNodes, adjacencyMatrix, i, x);
        }
    }

    // Start DFS from node 0
    dfs(0, numberOfNodes, adjacencyMatrix, visited);

    return 0;
}
