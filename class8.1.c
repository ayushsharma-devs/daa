#include<stdio.h>
#include<limits.h>
#define MAX 10
int m[MAX][MAX];
int s[MAX][MAX];
//function to print optimal parenthesis
void printOptimalParens(int s[MAX][MAX],int i,int j) {
if (i==j)
printf("A%d",i+1);
else{
printf("(");
printOptimalParens(s,i,s[i][j]-1);
printf(" ");
printOptimalParens(s,s[i][j],j);
printf(")");
}}
void matrixChainOrder(int p[],int n ){
int i,j,k,l,q;
for(i=0;i<n;i++)
m[i][i]=0;
for(l=2;l<=n;l++){
for(i=0;i<n-l+1;i++){
j=i+l-1;
m[i][j]=INT_MAX;
for(k=i;k<j;k++){
q= m[i][k]+m[k+1][j]+p[i]*p[k+1]*p[j+1];
if(q<m[i][j]){
m[i][j]=q;
s[i][j]=k+1;
}}}}}
int main(){
int n,i;
int rows[MAX], cols[MAX] ,p[MAX+1];
printf("Enter the number of matrices:");
scanf("%d" ,&n);
for(i=0;i<n;i++){
printf("Enter the number of rows and cols size of A%d:",i+1);
scanf("%d%d" ,&rows[i], &cols[i]);
if (i > 0 && rows[i] != cols[i - 1]) {
printf("Invalid dimensions! Matrix multiplication not possible.\n");
return 0;
}
}

// Prepare dimension array p[]
for (i = 0; i < n; i++)
p[i] = rows[i];
p[n] = cols[n - 1];
matrixChainOrder(p, n);

printf("\nM Table:\n");
for (i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
if (j < i)
printf("0\t");
else
printf("%d\t", m[i][j]);
}
printf("\n");
}

printf("\nS Table:\n");
for (i = 0; i < n; i++) {
for (int j = 0; j < n; j++) {
if (j < i)
printf("0\t");
else
printf("%d\t", s[i][j]);
}
printf("\n");
}

printf("\nOptimal parenthesization: ");
printOptimalParens(s, 0, n - 1);
printf("\nThe optimal ordering of the given matrices requires %d scalar multiplications.\n", m[0][n - 1]);

return 0;
}
