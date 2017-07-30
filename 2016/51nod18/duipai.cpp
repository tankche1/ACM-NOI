# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=10010;

int dp[maxn][maxn];
int n;
int l[maxn],r[maxn];


int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&l[i],&r[i]);
    }
    memset(dp[0],0,sizeof(dp[0]));
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            dp[i][j]=max(dp[i-1][j],dp[i][j-1]);
            if(j>=l[i]&&j<=r[i]) dp[i][j]=max(dp[i][j],dp[i-1][j-1]+1);
        }
    }
    printf("%d\n",dp[n][n]);
    return 0;
}
