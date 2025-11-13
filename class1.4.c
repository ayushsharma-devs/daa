#include <stdio.h>

void EXCHANGE(int *p, int *q) {
    int temp = *p;
    *p = *q;
    *q = temp;
}

void ROTATE_RIGHT(int *p1, int p2) {
    int i;
    for (i = p2 - 1; i > 0; i--) {
        EXCHANGE(&p1[i], &p1[i - 1]);
    }
}

int main() {
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);
    int A[n];
    for(int i=0;i<n;i++){
        printf("Enter the element %d: ",i+1);
        scanf("%d",&A[i]);
    }
    

    printf("Before ROTATE: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", A[i]);

    ROTATE_RIGHT(A, 5);

    printf("\nAfter ROTATE: ");
    for (int i = 0; i < 9; i++)
        printf("%d ", A[i]);

    return 0;
}
