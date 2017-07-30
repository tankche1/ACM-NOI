# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1010;
int mod=1000000007;
int n,s;
int a[maxn];
typedef long long LL;
LL dp[2][3][3][maxn];

int main(){
    int T;
    int now,last;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&n,&s);
        for(int i=1;i<=n;i++) scanf("%d",&a[i]);

        memset(dp[0],0,sizeof(dp[0]));
        dp[0][0][0][0]=1;
        for(int i=1;i<=n;i++){
            now=i&1;last=now^1;
            memset(dp[now],0,sizeof(dp[now]));
            for(int j=s;j>=0;j--){
                for(int s1=0;s1<=2;s1++){
                    for(int s2=0;s2<=2;s2++){
                        dp[now][s1][s2][j]+=dp[last][s1][s2][j];
                        if(s2>=1) dp[now][s1][s2][j]+=dp[last][s1][s2-1][j];
                        if(j>=a[i]){
                            dp[now][s1][s2][j]+=dp[last][s1][s2][j-a[i]];
                            if(s1>=1) dp[now][s1][s2][j]+=dp[last][s1-1][s2][j-a[i]];
                        }
                        if(dp[now][s1][s2][j]>=mod) dp[now][s1][s2][j]%=mod;
                    }
                }
            }
        }

        LL ans=0;
        for(int j=0;j<=s;j++) ans+=dp[n&1][2][2][j];
        ans=ans*4%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
