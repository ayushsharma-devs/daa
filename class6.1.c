#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int main() {
    int n, start;
    
    FILE *fp = fopen("inUnAdjMat.dat","r");
   if(!fp){
    printf("Cannot open file inUnAdjMat.dat\n");
    return 1;
   }

    printf("Enter the Number of Vertices: ");
    scanf("%d",&n);

    printf("Enter the Starting Vertex: ");
    scanf("%d",&start);
    start--; 

    int cost[n][n];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            fscanf(fp,"%d",&cost[i][j]);
    fclose(fp);

    int selected[n];
    for (int i=0;i<n;i++) selected[i]=0;
    selected[start]=1;

    int mst[n][n];
    for (int i=0;i<n;i++)
        for (int j=0;j<n;j++)
            mst[i][j]=0;

    int edgeCount=0;
    int totalCost=0;

    while (edgeCount < n-1) {
        int min=INT_MAX, x=-1,y=-1;
        for (int i=0;i<n;i++) {
            if (selected[i]) {
                for (int j=0;j<n;j++) {
                    if (!selected[j] && cost[i][j]) {
                        if (min > cost[i][j]) {
                            min = cost[i][j];
                            x=i;
                            y=j;
                        }
                    }
                }
            }
        }
        if (x!=-1 && y!=-1) {
            mst[x][y]=min;
            mst[y][x]=min;
            totalCost+=min;
            selected[y]=1;
            edgeCount++;
        } else {
            break;
        }
    }

    for (int i=0;i<n;i++) {
        for (int j=0;j<n;j++)
            printf("%d ",mst[i][j]);
        printf("\n");
    }

    printf("Total Weight of the Spanning Tree: %d\n",totalCost);

    return 0;
}
