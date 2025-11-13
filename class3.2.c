#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1000

int comparisons = 0;

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high, int *isWorst) {
    int pivot = arr[high];
    int i = low - 1;

    // If pivot is smallest or largest, suspect worst-case
    if (pivot == arr[low] || pivot == arr[high]) {
        *isWorst = 1;
    }

    for (int j = low; j < high; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }

    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(int arr[], int low, int high, int *isWorst) {
    if (low < high) {
        int pi = partition(arr, low, high, isWorst);

        quickSort(arr, low, pi - 1, isWorst);
        quickSort(arr, pi + 1, high, isWorst);
    }
}

void readFromFile(const char *filename, int arr[], int *n) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("Error opening file: %s\n", filename);
        exit(1);
    }

    *n = 0;
    while (fscanf(fp, "%d", &arr[*n]) != EOF && *n < MAX) {
        (*n)++;
    }
    fclose(fp);
}

void writeToFile(const char *filename, int arr[], int n) {
    FILE *fp = fopen(filename, "w");
    if (!fp) {
        printf("Error writing to file: %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        fprintf(fp, "%d ", arr[i]);
    }

    fclose(fp);
}

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int choice, arr[MAX], n = 0, isWorst = 0;
    char inputFile[50], outputFile[50];

    while (1) {
        printf("\nMAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. ERROR (EXIT)\n");
        printf("Enter option: ");
        scanf("%d", &choice);

        comparisons = 0;
        isWorst = 0;

        switch (choice) {
            case 1:
                strcpy(inputFile, "inAsce.dat");
                strcpy(outputFile, "outQuickAsce.dat");
                break;
            case 2:
                strcpy(inputFile, "inDesc.dat");
                strcpy(outputFile, "outQuickDesc.dat");
                break;
            case 3:
                strcpy(inputFile, "inRand.dat");
                strcpy(outputFile, "outQuickRand.dat");
                break;
            case 4:
                printf("Exiting...\n");
                exit(0);
            default:
                printf("Invalid choice!\n");
                continue;
        }

        readFromFile(inputFile, arr, &n);
        printf("\nBefore Sorting (%s):\n", inputFile);
        printArray(arr, n);

        quickSort(arr, 0, n - 1, &isWorst);

        printf("\nAfter Sorting (%s):\n", outputFile);
        printArray(arr, n);

        writeToFile(outputFile, arr, n);

        printf("Number of Comparisons: %d\n", comparisons);
        printf("Scenario: %s-case\n", isWorst ? "Worst" : "Best/Average");
    }

    return 0;
}
