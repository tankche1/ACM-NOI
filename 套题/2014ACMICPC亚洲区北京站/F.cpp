# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=1000000007;
const int maxn=55;
bool a[maxn][maxn];
LL dp[maxn][8];
int n,m;
int main(){
    int T,len,x;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&m);
        memset(a,0,sizeof(a));
        for(int i=1;i<=m;i++){
            scanf("%d",&len);
            while(len--){
                scanf("%d",&x);
                a[i][x]=1;
            }
        }

        LL ans=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                for(int k=1;k<=n;k++){
                    memset(dp,0,sizeof(dp));
                    dp[0][0]=1;
                    for(int t=0;t<m;t++){
                        for(int s=0;s<8;s++){
                            while(dp[t][s]>=mod) dp[t][s]-=mod;
                            dp[t+1][s]+=dp[t][s];
                            dp[t+1][s^(a[t+1][i]<<2)^(a[t+1][j]<<1)^(a[t+1][k])]+=dp[t][s];
                        }
                    }
                    ans+=dp[m][7];
                }
            }
        }
        ans%=mod;

        printf("Case #%d: ",Tcase);
        printf("%I64d\n",ans);
    }
    return 0;
}
