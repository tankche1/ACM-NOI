# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=405;
typedef long long LL;
int mod=1000000007;
LL dp[2][maxn*maxn/2];
LL sum[2][maxn*maxn/2];
int n,k;
int main(){
    scanf("%d%d",&n,&k);
    memset(dp,0,sizeof(dp));
    int now,last;
    dp[1][0]=1;
    sum[1][0]=1;
    for(int j=1;j<=k;j++) sum[1][j]=1;
    for(int i=2;i<=n;i++){
        now=i&1;last=now^1;
        memset(dp[now],0,sizeof(dp[now]));
        for(int j=0;j<=k;j++){
            dp[now][j]=sum[last][j];
            if(j-(i-1)-1>=0) dp[now][j]-=sum[last][j-(i-1)-1];
            if(dp[now][j]<0) dp[now][j]+=mod;
        }
        sum[now][0]=dp[now][0];
        for(int j=1;j<=k;j++){
            sum[now][j]=sum[now][j-1]+dp[now][j];
            if(sum[now][j]>=mod) sum[now][j]-=mod;
        }
    }
    now=n&1;
    printf("%I64d\n",dp[now][k]);
    return 0;
}
