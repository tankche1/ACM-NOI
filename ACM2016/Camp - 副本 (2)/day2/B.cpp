# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=3010;
typedef long long LL;
LL cost[maxn][maxn];
int n;
LL x[maxn];
LL dp[maxn];

LL tank(LL x){ return x*x;}
int main(){
    while(scanf("%d",&n)!=EOF){
        for(int i=1;i<=n;i++){
            scanf("%lld",&x[i]);
        }
        x[0]=x[1];x[n+1]=x[n];
        int now;
        for(int L=1;L<=n;L++){
            cost[L][L]=max(tank(x[L]-x[L-1]),tank(x[L+1]-x[L]));
            now=L;
            for(int R=L+1;R<=n;R++){
                cost[L][R]=cost[L][R-1]-max(tank(x[R]-x[now]),tank(x[now]-x[L-1]))+max(tank(x[R+1]-x[now]),tank(x[now]-x[L-1]));
                cost[L][R]+=tank(x[R]-x[R-1]);
                //printf("now:%d cost[%d][%d]:%lld \n",now,L,R,cost[L][R]);
                while(now<R&&max(tank(x[R+1]-x[now+1]),tank(x[now+1]-x[L-1]))<max(tank(x[R+1]-x[now]),tank(x[now]-x[L-1]))) {
                    cost[L][R]=cost[L][R]-max(tank(x[R+1]-x[now]),tank(x[now]-x[L-1]))+max(tank(x[R+1]-x[now+1]),tank(x[now+1]-x[L-1]));
                    now++;
                }
            //printf("now:%d ",now);
             //   printf("cost[%d][%d]:%lld \n",L,R,cost[L][R]);
            }
        }
        for(int i=1;i<=n;i++){
            dp[i]=cost[1][i];
            for(int j=1;j<i;j++){
                if(dp[j]+cost[j+1][i]<dp[i]) dp[i]=dp[j]+cost[j+1][i];
            }
        }
        printf("%lld\n",dp[n]);
    }
    return 0;
}
