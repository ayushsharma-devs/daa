#include <stdio.h>

int main() {
    int size;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&size);
    int arr[size];
    for(int i=0;i<size;i++){
        printf("Enter the element %d: ",i+1);
        scanf("%d",&arr[i]);
    }
    int n = sizeof(arr) / sizeof(arr[0]);
    int prefixSum[n];

    prefixSum[0] = arr[0];
    for (int i = 1; i < n; i++)
        prefixSum[i] = prefixSum[i - 1] + arr[i];

    printf("Output Array: ");
    for (int i = 0; i < n; i++)
        printf("%d ", prefixSum[i]);

    return 0;
}
