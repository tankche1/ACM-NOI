# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=210;
int n;
int a[maxn],b[maxn];
int dp[maxn][maxn];

int dfs(int L,int R){
    if(dp[L][R]!=-1) return dp[L][R];
    if(L==R) return dp[L][R]=b[L-1]+b[R+1];

    dp[L][R]=dfs(L+1,R);
    dp[L][R]=min(dp[L][R],dfs(L,R-1));

    for(int k=L+1;k<R;k++){
        dp[L][R]=min(dp[L][R],dp[L][k-1]+dp[k+1][R]);
    }
    dp[L][R]+=b[L-1]+b[R+1];
    return dp[L][R];
}
int main(){
    int ans,T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        ans=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&a[i]);ans+=a[i];
        }
        b[0]=0;b[n+1]=0;
        for(int i=1;i<=n;i++){
            scanf("%d",&b[i]);
        }

        memset(dp,-1,sizeof(dp));
        dfs(1,n);

        printf("Case #%d: ",Tcase);
        printf("%d\n",ans+dp[1][n]);
    }
    return 0;
}
