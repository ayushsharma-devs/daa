#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int u,v,w;
} Edge;

int find(int parent[], int i) {
    if (parent[i]!=i)
        parent[i]=find(parent,parent[i]);
    return parent[i];
}

void unionSet(int parent[], int rank[], int x,int y) {
    int xroot=find(parent,x);
    int yroot=find(parent,y);
    if (rank[xroot]<rank[yroot])
        parent[xroot]=yroot;
    else if (rank[xroot]>rank[yroot])
        parent[yroot]=xroot;
    else {
        parent[yroot]=xroot;
        rank[xroot]++;
    }
}

int cmp(const void *a,const void *b) {
    Edge *e1=(Edge*)a;
    Edge *e2=(Edge*)b;
    return e1->w - e2->w;
}

int main() {
    FILE *fp = fopen("inKruskal.dat","r");
    int n,m;
    scanf("%d %d",&n,&m);

    Edge edges[m];
    for (int i=0;i<m;i++)
        scanf("%d %d %d",&edges[i].u,&edges[i].v,&edges[i].w);

    qsort(edges,m,sizeof(Edge),cmp);

    int parent[n+1],rank[n+1];
    for (int i=1;i<=n;i++) {
        parent[i]=i;
        rank[i]=0;
    }

    int totalCost=0;
    printf("Edge Cost\n");
    for (int i=0;i<m;i++) {
        int u=edges[i].u;
        int v=edges[i].v;
        int w=edges[i].w;
        int x=find(parent,u);
        int y=find(parent,v);

        if (x!=y) {
            printf("%d--%d %d\n",u,v,w);
            totalCost+=w;
            unionSet(parent,rank,x,y);
        }
    }
    printf("Total Weight of the Spanning Tree: %d\n",totalCost);
    return 0;
}
