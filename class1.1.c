#include<stdio.h>
int main(){
    int n;
    printf("Enter the number of elements in the array: ");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++){
        printf("Enter the element %d: ",i+1);
        scanf("%d",&arr[i]);
    }
    //[1,5,2,7,10,12] output: 2,10
    int secondsmall, secondlarge,small=arr[0],large=arr[0];

    for(int i=0;i<n;i++){
        if(arr[i]<  small){
            secondsmall=small;
            small=arr[i];
        }
        else if(arr[i]<secondsmall && arr[i]!=small){
            secondsmall=arr[i];
        }
        if(arr[i]>large){
            secondlarge=large;
            large=arr[i];
        }
        else if(arr[i]>secondlarge && arr[i]!=large){
            secondlarge=arr[i];
        }
    }
    printf("Second smallest element: %d\n",secondsmall);
    printf("Second largest element: %d\n",secondlarge);
    
}