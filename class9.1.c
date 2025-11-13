#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX

#define INF INT_MAX / 2 // Use a large number for infinity to avoid overflow

// Global variables for matrices and vertex count
int V;
int **dist;
int **path;

// Function to print the path from vertex u to v
void constructPath(int u, int v) {
    if (path[u][v] == -1) {
        // Base case: No intermediate vertex, this is a direct segment
        return;
    }
    int k = path[u][v];
    constructPath(u, k);
    printf("-->%d", k + 1); // Print the intermediate vertex (1-based index)
    constructPath(k, v);
}

// Main function to run the Floyd-Warshall algorithm
void floydWarshall() {
    // Initialize path matrix
    path = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        path[i] = (int *)malloc(V * sizeof(int));
        for (int j = 0; j < V; j++) {
            path[i][j] = -1; // -1 indicates no intermediate vertex
        }
    }

    // The main DP algorithm
    for (int k = 0; k < V; k++) {
        for (int i = 0; i < V; i++) {
            for (int j = 0; j < V; j++) {
                // If path through k is shorter, update distance and path
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][k] + dist[k][j] < dist[i][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = k; // k is the intermediate vertex on the path from i to j
                }
            }
        }
    }
}

// Utility function to print a matrix
void printMatrix(int **matrix) {
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (matrix[i][j] == INF) {
                printf("%7s", "INF");
            } else {
                printf("%7d", matrix[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    FILE *file;
    const char *filename = "inDiAdjMat2.dat";

    printf("Number of Vertices: ");
    scanf("%d", &V);

    // Allocate memory for the distance matrix
    dist = (int **)malloc(V * sizeof(int *));
    for (int i = 0; i < V; i++) {
        dist[i] = (int *)malloc(V * sizeof(int));
    }

    // Open the input file
    file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    // Read the adjacency matrix from the file
    printf("\nInput Adjacency Matrix:\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            fscanf(file, "%d", &dist[i][j]);
            // In standard adjacency matrices, 0 for i!=j means no path.
            // Replace with INF for the algorithm.
            if (i != j && dist[i][j] == 0) {
                dist[i][j] = INF;
            }
        }
    }
    fclose(file);
    printMatrix(dist);

    // Run the algorithm
    floydWarshall();

    // Print the final shortest path matrix
    printf("\nOutput (Shortest Path Matrix):\n");
    printMatrix(dist);
    printf("\n");

    // Get user input for the specific path to display
    int u, v;
    printf("Enter the source and destination vertex: ");
    scanf("%d %d", &u, &v);

    // Adjust for 0-based indexing
    u--; 
    v--;

    // Print the reconstructed path and its weight
    if (dist[u][v] == INF) {
        printf("No path exists from vertex %d to %d.\n", u + 1, v + 1);
    } else {
        printf("Shortest Path from vertex %d to vertex %d: ", u + 1, v + 1);
        printf("%d", u + 1);
        constructPath(u, v);
        printf("-->%d\n", v + 1);
        printf("Path weight: %d\n", dist[u][v]);
    }

    // Free all dynamically allocated memory
    for (int i = 0; i < V; i++) {
        free(dist[i]);
        free(path[i]);
    }
    free(dist);
    free(path);

    return 0;
}