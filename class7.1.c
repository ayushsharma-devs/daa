#include <stdio.h>
#include <stdlib.h>
#include <limits.h> // For INT_MAX

// Define constants
#define MAX_VERTICES 100
#define INF INT_MAX

// Structure to store path information for each node
typedef struct {
    int dist; // Shortest distance from source
    int parent; // Parent node in the shortest path
} NodeInfo;

// Function to find the vertex with the minimum distance value, from the set of vertices not yet included in shortest path tree
int minDistance(int V, NodeInfo info[], int sptSet[]) {
    int min = INF, min_index = -1;

    for (int v = 0; v < V; v++) {
        // Find unvisited node (sptSet[v] == 0) with smallest distance (info[v].dist <= min)
        if (sptSet[v] == 0 && info[v].dist <= min) {
            min = info[v].dist;
            min_index = v;
        }
    }
    return min_index;
}

// Function to print the shortest path from source 's' to destination 'j'
void printPath(int j, NodeInfo info[]) {
    // Base case: If j is the source node, stop recursion.
    if (info[j].parent == -1) {
        return;
    }
    
    // Recurse to print path from parent first
    printPath(info[j].parent, info);
    
    // Print the current node (using 1-based indexing for output)
    printf("->%d", j + 1);
}

// Dijkstra's algorithm function
void dijkstra(int V, int graph[MAX_VERTICES][MAX_VERTICES], int src) {
    // V: Number of vertices
    // graph: Adjacency matrix
    // src: Source vertex (0-based index)

    NodeInfo info[MAX_VERTICES];
    int sptSet[MAX_VERTICES]; // sptSet[i] will be 1 if vertex i is included in shortest path tree or shortest distance from src is finalized

    // 1. Initialization
    for (int i = 0; i < V; i++) {
        info[i].dist = INF;
        info[i].parent = -1; // -1 indicates no parent (source node)
        sptSet[i] = 0; // All vertices are initially unvisited
    }

    // Distance of source vertex from itself is always 0
    info[src].dist = 0;

    // 2. Main Loop
    // Find shortest path for all vertices
    for (int count = 0; count < V - 1; count++) {
        // Pick the minimum distance vertex from the set of vertices not yet processed.
        int u = minDistance(V, info, sptSet);

        // If no more reachable vertices are found, break
        if (u == -1 || info[u].dist == INF) break;

        // Mark the picked vertex as processed
        sptSet[u] = 1;

        // Update dist value of the adjacent vertices of the picked vertex.
        for (int v = 0; v < V; v++) {
            // Update info[v].dist only if:
            // 1. v is not in sptSet (unvisited)
            // 2. There is an edge from u to v (graph[u][v] != 0)
            // 3. Total weight of path from src to v through u is smaller than current info[v].dist
            if (!sptSet[v] && graph[u][v] != 0 && info[u].dist != INF 
                && info[u].dist + graph[u][v] < info[v].dist) 
            {
                info[v].dist = info[u].dist + graph[u][v];
                info[v].parent = u;
            }
        }
    }

    // 3. Print the result
    printf("\nOutput:\n");
    printf("Source\tDestination\tCost\tPath\n");
    for (int i = 0; i < V; i++) {
        // Source index is (src + 1) for 1-based output
        printf("%d\t%d\t\t", src + 1, i + 1);

        // Print Cost
        if (info[i].dist == INF) {
            printf("INF\t"); // Unreachable
        } else {
            printf("%d\t", info[i].dist);
        }

        // Print Path
        if (i == src) {
            printf("-\n"); // Path to self
        } else if (info[i].dist == INF) {
            printf("Unreachable\n");
        } else {
            // The path starts with the source node
            printf("%d", src + 1); 
            // The actual path trace starts from the parent of the destination node
            printPath(i, info);
            printf("\n");
        }
    }
}

// Main function to read input and call Dijkstra
int main() {
    int V, source_vertex_1_based;
    int graph[MAX_VERTICES][MAX_VERTICES] = {0}; // Initialize matrix to 0
    
    // --- Input from user (for V and Source) ---
    printf("Input:\n");
    printf("Enter the Number of Vertices: ");
    // The input file suggests V=5, but we'll read it for generality
    if (scanf("%d", &V) != 1 || V <= 0 || V > MAX_VERTICES) {
        fprintf(stderr, "Invalid number of vertices.\n");
        return 1;
    }

    printf("Enter the Source Vertex (1 to %d): ", V);
    if (scanf("%d", &source_vertex_1_based) != 1 || source_vertex_1_based < 1 || source_vertex_1_based > V) {
        fprintf(stderr, "Invalid source vertex.\n");
        return 1;
    }

    // Convert 1-based source to 0-based index for array
    int src_0_based = source_vertex_1_based - 1;

    // --- Input from file (Adjacency Matrix) ---
    // The file name is hardcoded as per the prompt's instruction: "inDiAdjMat1.dat"
    FILE *file = fopen("inDiAdjMat1.dat", "r");
    if (file == NULL) {
        fprintf(stderr, "\nError: Could not open input file 'inDiAdjMat1.dat'.\n");
        fprintf(stderr, "Please create the file with the content as shown in the prompt.\n");
        return 1;
    }

    // Read the V x V adjacency matrix from the file
    printf("\nReading graph from 'inDiAdjMat1.dat'...\n");
    for (int i = 0; i < V; i++) {
        for (int j = 0; j < V; j++) {
            if (fscanf(file, "%d", &graph[i][j]) != 1) {
                // Handle case where file ends unexpectedly
                fprintf(stderr, "Error reading adjacency matrix from file.\n");
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);

    // Run Dijkstra's Algorithm
    dijkstra(V, graph, src_0_based);

    return 0;
}