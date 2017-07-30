# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=110;
int n;
bool p[maxn][maxn];
int g[maxn][maxn];

int main(){

    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d",&n);
        memset(p,false,sizeof(p));
        //for(int i=1;i<=n;i++) p[i][i]=1;
        printf("%d\n",n);
        if(n%2==0) {puts("No solution");continue;}
        for(int i=2;i<=n;i++) g[1][i]=i-1;
        for(int i=2;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                g[i][j]=g[i-1][j]+1;
                if(g[i][j]>n) g[i][j]=1;
            }
        }

        for(int i=1;i<n;i++){
            for(int j=i+1;j<=n;j++){
                printf("%d %d %d ",i,j,g[i][j]);
            }
        }puts("");
    }
    return 0;
}
