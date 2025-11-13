#include <stdio.h>
#include <limits.h>

#define MAX 20

int n; // number of vertices
int cost[MAX][MAX]; // input cost adjacency matrix
int parent[MAX]; // parent array for MST
int key[MAX]; // minimum edge weights
int mstSet[MAX]; // to track visited vertices

// Function to find vertex with minimum key value
int minKey(int key[], int mstSet[]) {
    int min = INT_MAX, min_index;
    for (int v = 0; v < n; v++)
        if (mstSet[v] == 0 && key[v] < min)
            min = key[v], min_index = v;
    return min_index;
}

// Print MST adjacency matrix and total weight
void printMST() {
    int mst[MAX][MAX] = {0};
    int totalCost = 0;

    // Build MST cost adjacency matrix
    for (int i = 1; i < n; i++) {
        mst[i][parent[i]] = cost[i][parent[i]];
        mst[parent[i]][i] = cost[i][parent[i]];
        totalCost += cost[i][parent[i]];
    }

    // Display MST cost adjacency matrix
    printf("\nCost Adjacency Matrix of MST:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", mst[i][j]);
        printf("\n");
    }

    printf("Total Weight of the Spanning Tree: %d\n", totalCost);
}

// Prim’s Algorithm
void primMST(int start) {
    for (int i = 0; i < n; i++) {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[start] = 0;
    parent[start] = -1;

    for (int count = 0; count < n - 1; count++) {
        int u = minKey(key, mstSet);
        mstSet[u] = 1;

        for (int v = 0; v < n; v++) {
            if (cost[u][v] && mstSet[v] == 0 && cost[u][v] < key[v]) {
                parent[v] = u;
                key[v] = cost[u][v];
            }
        }
    }

    printMST();
}

int main() {
    FILE *fp;
    fp = fopen("inUnAdjMat.dat", "r");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    printf("Enter the Number of Vertices: ");
    scanf("%d", &n);

    printf("Reading adjacency matrix from file...\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            fscanf(fp, "%d", &cost[i][j]);

    fclose(fp);

    int start;
    printf("Enter the Starting Vertex: ");
    scanf("%d", &start);

    primMST(start - 1); // convert to 0-indexed

    return 0;
}