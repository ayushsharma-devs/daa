#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person {
    int id;
    char name[50];
    int age;
    int height;
    int weight;
};

struct person *arr = NULL;  // dynamic array
int n = 0;                  // number of students

// Utility: Swap two persons
void swap(struct person *a, struct person *b) {
    struct person temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify for Min-Heap (by age)
void minHeapify(struct person heap[], int size, int i) {
    int smallest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < size && heap[left].age < heap[smallest].age)
        smallest = left;
    if(right < size && heap[right].age < heap[smallest].age)
        smallest = right;

    if(smallest != i) {
        swap(&heap[i], &heap[smallest]);
        minHeapify(heap, size, smallest);
    }
}

// Heapify for Max-Heap (by weight)
void maxHeapify(struct person heap[], int size, int i) {
    int largest = i;
    int left = 2*i + 1;
    int right = 2*i + 2;

    if(left < size && heap[left].weight > heap[largest].weight)
        largest = left;
    if(right < size && heap[right].weight > heap[largest].weight)
        largest = right;

    if(largest != i) {
        swap(&heap[i], &heap[largest]);
        maxHeapify(heap, size, largest);
    }
}

// Build Min-Heap
void buildMinHeap(struct person heap[], int size) {
    for(int i = size/2 - 1; i >= 0; i--)
        minHeapify(heap, size, i);
}

// Build Max-Heap
void buildMaxHeap(struct person heap[], int size) {
    for(int i = size/2 - 1; i >= 0; i--)
        maxHeapify(heap, size, i);
}

// Insert into Min-Heap
void insertMinHeap(struct person heap[], int *size, struct person newPerson) {
    heap[*size] = newPerson;
    int i = *size;
    (*size)++;

    while(i != 0 && heap[(i-1)/2].age > heap[i].age) {
        swap(&heap[i], &heap[(i-1)/2]);
        i = (i-1)/2;
    }
}

// Delete root (oldest person from Min-Heap)
void deleteOldestFromMinHeap(struct person heap[], int *size) {
    if(*size == 0) {
        printf("Heap is empty!\n");
        return;
    }
    heap[0] = heap[*size - 1];
    (*size)--;
    minHeapify(heap, *size, 0);
}

// Display weight of youngest person
void displayYoungestWeight(struct person heap[]) {
    if(n == 0) {
        printf("No data available!\n");
        return;
    }
    printf("Weight of youngest student: %.2f kg\n", heap[0].weight * 0.453592); // pounds→kg
}

int main() {
    int option;
    struct person newP;

    do {
        printf("\nMAIN MENU (HEAP)\n");
        printf("1. Read Data\n");
        printf("2. Create a Min-heap based on the age\n");
        printf("3. Create a Max-heap based on the weight\n");
        printf("4. Display weight of the youngest person\n");
        printf("5. Insert a new person into the Min-heap\n");
        printf("6. Delete the oldest person\n");
        printf("7. Display all data\n");
        printf("8. Exit\n");
        printf("Enter option: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("Enter number of students: ");
                scanf("%d", &n);
                arr = (struct person*)malloc(n * sizeof(struct person));

                for(int i=0; i<n; i++) {
                    printf("Id Name Age Height Weight(pound): ");
                    scanf("%d %s %d %d %d", &arr[i].id, arr[i].name, &arr[i].age, &arr[i].height, &arr[i].weight);
                }
                break;

            case 2:
                buildMinHeap(arr, n);
                printf("Min-Heap (by Age) created!\n");
                break;

            case 3:
                buildMaxHeap(arr, n);
                printf("Max-Heap (by Weight) created!\n");
                break;

            case 4:
                displayYoungestWeight(arr);
                break;

            case 5:
                printf("Enter new person details (Id Name Age Height Weight): ");
                scanf("%d %s %d %d %d", &newP.id, newP.name, &newP.age, &newP.height, &newP.weight);
                insertMinHeap(arr, &n, newP);
                printf("Inserted into Min-Heap!\n");
                break;

            case 6:
                deleteOldestFromMinHeap(arr, &n);
                printf("Deleted oldest person!\n");
                break;

            case 7:
                printf("Exiting...\n");
                break;
            
            case 8: 
            for(int i=0; i<n; i++) {
                printf("Id Name Age Height Weight(pound): ");
                printf("%d %s %d %d %d", &arr[i].id, arr[i].name, &arr[i].age, &arr[i].height, &arr[i].weight);
            }

            default:
                printf("Invalid option!\n");
        }

    } while(option != 7);

    free(arr);
    return 0;
}
