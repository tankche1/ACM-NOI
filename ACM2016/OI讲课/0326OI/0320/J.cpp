# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL dp[10000010];
const LL mod=(LL)1000000000000000;
int E,suc,fail;
int main(){
    scanf("%d%d%d",&E,&suc,&fail);
    dp[0]=0;
    for(int i=1;i<=E;i++){
        dp[i]=dp[max(0,i-suc)]+dp[max(0,i-fail)]+1;
        if(dp[i]>mod) dp[i]=mod;
    }
    //printf("dp[E]:%I64d\n",dp[E]);
    double ans=min((double)225/((dp[E]+1)*1.0),(double)200/(dp[E]*1.0));
    printf("%.6lf\n",ans);
    return 0;
}
