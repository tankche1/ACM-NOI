# include<stdio.h>
# include<iostream>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=2010;
const int INF=10000000;
const int mod=1000000007;
int n,d;
int w[maxn];
LL dp[maxn][2][maxn];
LL num[maxn][2][maxn];

void dfs(int L,int R){
    int now=R&1;int last=now^1;
    if(L==R) {num[L][now][0]=num[L][now][1]=1;dp[L][now][0]=dp[L][now][1]=0;return;}
    if(w[L]+w[R]<d) {
        dfs(L+1,R);
        for(int t=0;t<=R-L+1;t++) dp[L][now][t]=-INF,num[L][now][t]=0;
        num[L][now][0]=num[L][now][R-L+1]=1;dp[L][now][0]=dp[L][now][R-L+1]=0;
        for(int t=1;t<R-L+1;t++){

            if(dp[L+1][now][t]>dp[L][now][t]) dp[L][now][t]=dp[L+1][now][t],num[L][now][t]=num[L+1][now][t];
            else if(dp[L+1][now][t]==dp[L][now][t]) num[L][now][t]+=num[L+1][now][t];

            if(dp[L+1][now][t-1]>dp[L][now][t]) dp[L][now][t]=dp[L+1][now][t-1],num[L][now][t]=num[L+1][now][t-1];
            else if(dp[L+1][now][t-1]==dp[L][now][t]) num[L][now][t]+=num[L+1][now][t-1];

            while(num[L][now][t]>=mod) num[L][now][t]-=mod;
        }
        return;
    }

    dfs(L,R-1);
    for(int t=0;t<=R-L+1;t++) dp[L][now][t]=-INF,num[L][now][t]=0;

    for(int t=0;t<=R-1-L+1;t++){
        if(dp[L][last][t]+R-1-L+1-t>dp[L][now][t+1]) dp[L][now][t+1]=dp[L][last][t]+R-1-L+1-t,num[L][now][t+1]=num[L][last][t];
        else if(dp[L][last][t]+R-1-L+1-t==dp[L][now][t+1]) num[L][now][t+1]+=num[L][last][t];

        if(dp[L][last][t]+t>dp[L][now][t]) dp[L][now][t]=dp[L][last][t]+t,num[L][now][t]=num[L][last][t];
        else if(dp[L][last][t]+t==dp[L][now][t]) num[L][now][t]+=num[L][last][t];
    }
    for(int t=0;t<=R-L+1;t++)
        while(num[L][now][t]>=mod) num[L][now][t]-=mod;
}

int main(){
    scanf("%d%d",&n,&d);
    for(int i=1;i<=n;i++){
        scanf("%d",&w[i]);
    }w[n+1]=d;
    sort(w+1,w+n+1);w[0]=0;
    dfs(1,n);
    int now=n&1;
    LL ans=0,tmp=0;
    for(int t=0;t<=n;t++){
        if(dp[1][now][t]>ans) ans=dp[1][now][t],tmp=num[1][now][t];
        else if(dp[1][now][t]==ans) tmp+=num[1][now][t];
        while(tmp>=mod) tmp-=mod;
    }
    //printf("%I64d %I64d\n",ans,tmp);
    cout << ans << ' ' << tmp << endl;
    return 0;
}
