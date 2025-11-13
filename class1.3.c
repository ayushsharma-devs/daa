#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define the maximum size for the frequency array.
// This assumes the input integers are non-negative and less than 1000.
// If your input numbers might be larger (e.g., in the millions), a more advanced
// data structure like a hash map (or a struct/linked list in C) would be necessary.
#define MAX_VAL 1000
#define MAX_ARRAY_SIZE 100 // Maximum number of integers we will read from the file.

// Function to perform the core analysis
void analyze_duplicates(int arr[], int n) {
    // A frequency array to store the count of each number.
    // Index i stores the count of the number 'i'.
    int counts[MAX_VAL] = {0};

    // Variables for analysis results
    int total_distinct_duplicates = 0;
    int most_repeating_element = -1;
    int max_count = 0;

    // --- 1. Populate the Frequency Array ---
    printf("\nThe content of the array: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);

        // Only count if the number is within the defined range (0 to MAX_VAL - 1)
        if (arr[i] >= 0 && arr[i] < MAX_VAL) {
            counts[arr[i]]++;
        }
    }
    printf("\n");

    // --- 2. Analyze Frequencies ---
    for (int i = 0; i < MAX_VAL; i++) {
        int current_count = counts[i];

        // a) Find out the total number of distinct duplicate elements
        // A distinct element is a duplicate if its count is greater than 1.
        if (current_count > 1) {
            total_distinct_duplicates++;
        }

        // b) Find out the most repeating element
        if (current_count > max_count) {
            max_count = current_count;
            most_repeating_element = i;
        }
    }

    // --- 3. Output Results ---
    printf("\nTotal number of distinct duplicate values = %d\n", total_distinct_duplicates);
    
    // Check if any element was found (max_count will be at least 1 if the array is not empty)
    if (most_repeating_element != -1) {
        printf("The most repeating element in the array = %d\n", most_repeating_element);
        printf("It repeats %d times.\n", max_count);
    } else {
        printf("The array is empty or contains numbers outside the detectable range (0 to %d).\n", MAX_VAL - 1);
    }
}

int main() {
    int N;
    int data[MAX_ARRAY_SIZE];
    FILE *file_ptr;
    const char *filename = "inDiAdjMat1.dat";

    // --- 1. Get N from user ---
  
    printf("Enter how many numbers you want to read from file: ");
    if (scanf("%d", &N) != 1 || N <= 0 || N > MAX_ARRAY_SIZE) {
        fprintf(stderr, "Invalid input for N. Please enter a positive integer up to %d.\n", MAX_ARRAY_SIZE);
        return 1;
    }

    // --- 2. Open and Read File ---
    file_ptr = fopen(filename, "r"); // Open file for reading ('r')

    if (file_ptr == NULL) {
        // If file cannot be opened, print an error and exit.
        fprintf(stderr, "Error: Could not open the file '%s'. Make sure it exists in the current directory.\n", filename);
        return 1;
    }

    // Read N integers from the file into the array
    int read_count = 0;
    while (read_count < N && fscanf(file_ptr, "%d", &data[read_count]) == 1) {
        read_count++;
    }

    // Close the file stream after reading
    fclose(file_ptr);

    // Check if we read the expected number of elements
    if (read_count < N) {
        printf("Warning: Only read %d out of the requested %d numbers from the file.\n", read_count, N);
    }

    // --- 3. Perform Analysis ---
    if (read_count > 0) {
        analyze_duplicates(data, read_count);
    } else {
        printf("The file was opened but no integers could be read.\n");
    }

    return 0;
}