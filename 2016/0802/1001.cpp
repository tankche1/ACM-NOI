# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=2010;
double INF=10000;
int K,W;
double dp[maxn][30];
bool vis[maxn][30];

void dfs(int k,int w){
    if(k==0) {dp[k][w]=0;return;}
    if(w==0) {dp[k][w]=INF;return;}
    if(vis[k][w]) return;
    vis[k][w]=1;

    dp[k][w]=INF;
    for(int j=1;j<=k;j++){
        dfs(k-j,w);dfs(j-1,w-1);
        dp[k][w]=min(dp[k][w],dp[k-j][w]*(k-j+1)/((k+1)*1.0)+dp[j-1][w-1]*(j)/((k+1)*1.0)+1);
    }
}

int main(){
    memset(vis,0,sizeof(vis));
    dfs(2000,15);
    while(scanf("%d%d",&K,&W)!=EOF){
        W=min(W,15);
        dfs(K,W);

        printf("%.6lf\n",dp[K][W]);
    }
    return 0;
}
