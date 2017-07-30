# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int A[maxn][maxn],B[maxn][maxn],down[maxn][maxn];
int n,m;
int main(){
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
        scanf("%d",&A[i][j]);

    for(int i=n;i>=1;i--){
        for(int j=m;j>=1;j--){
            if(i==n) down[i][j]=A[i][j];
            else down[i][j]=min(down[i+1][j],A[i][j]);
        }
    }

    for(int i=n;i>=1;i--)
        B[i][m]=down[i][m];
    for(int j=m-1;j>=0;j--){
        for(int i=n;i>=1;i--){
            if(i==1) B[i][j]=min(B[i][j+1],down[i][j]);
            else B[i][j]=min(B[i-1][j+1],down[i][j]);
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            printf("%d",B[i][j]);
            if(j!=m) printf(" ");
        }puts("");
    }
    return 0;
}
