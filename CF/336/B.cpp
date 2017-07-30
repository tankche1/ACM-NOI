# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=510;
const int INF=1000;
bool vis[maxn][maxn];
int dp[maxn][maxn];
int c[maxn];
int n;

bool Tank(int L,int R){
    int s=0;
    while(L+s<=R-s) {if(c[L+s]!=c[R-s]) return false;s++;}
    return true;
}

void dfs(int L,int R){
    if(vis[L][R]) return;
    vis[L][R]=1;
    if(Tank(L,R)) {dp[L][R]=1;return;}
    dp[L][R]=INF;
    for(int k=L;k<R;k++) {
        dfs(L,k);dfs(k+1,R);
        dp[L][R]=min(dp[L][R],dp[L][k]+dp[k+1][R]);
    }
    for(int s=1;L+s-1<=R-s+1;s++){
        if(c[L+s-1]!=c[R-s+1]) break;
        dfs(L+s,R-s);
        dp[L][R]=min(dp[L+s][R-s],dp[L][R]);
    }
}
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&c[i]);
    dfs(1,n);
    printf("%d\n",dp[1][n]);
    return 0;
}
