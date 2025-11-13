#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int item_id;
    float profit;
    float weight;
    float ratio;
} ITEM;


void swap(ITEM *a, ITEM *b) {
    ITEM temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(ITEM arr[], int n, int i) {
    int largest = i;
    int l = 2*i + 1;
    int r = 2*i + 2;

    if (l < n && arr[l].ratio > arr[largest].ratio)
        largest = l;
    if (r < n && arr[r].ratio > arr[largest].ratio)
        largest = r;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(ITEM arr[], int n) {
    for (int i = n/2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    for (int i = n-1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);
        heapify(arr, i, 0);
    }

    for (int i = 0; i < n/2; i++) {
        swap(&arr[i], &arr[n-1-i]);
    }
}

int main() {
    int n;
    printf("Enter the number of items: ");
    scanf("%d", &n);

    ITEM *items = (ITEM *)malloc(n * sizeof(ITEM));

    for (int i = 0; i < n; i++) {
        printf("Enter the profit and weight of item no %d: ", i+1);
        scanf("%f %f", &items[i].profit, &items[i].weight);
        items[i].item_id = i+1;
        items[i].ratio = items[i].profit / items[i].weight;
    }

    float capacity;
    printf("Enter the capacity of knapsack:");
    scanf("%f", &capacity);

    heapSort(items, n);

    float *x = (float *)malloc(n * sizeof(float));
    for (int i = 0; i < n; i++)
        x[i] = 0.0;

    float total_profit = 0.0;
    float remaining = capacity;

    for (int i = 0; i < n; i++) {
        if (items[i].weight <= remaining) {
            x[i] = 1.0;
            total_profit += items[i].profit;
            remaining -= items[i].weight;
        } else {
            x[i] = remaining / items[i].weight;
            total_profit += x[i] * items[i].profit;
            remaining = 0;
            break;
        }
    }

    printf("Item No\tprofit\tWeight\tAmount to be taken\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%f\t%f\t%f\n", items[i].item_id,
               items[i].profit, items[i].weight, x[i]);
    }

    printf("Maximum profit: %f\n", total_profit);

    free(items);
    free(x);
    return 0;
}
