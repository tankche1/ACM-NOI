# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1010;
typedef long long LL;
int mod=1000000007;
int dir[maxn];
int n;
LL dp[maxn][maxn];
LL p;
LL two[maxn],inv[maxn];

LL fast_pow(LL a,int b){
    if(b==0) return 1;
    LL tmp=a,res=1;
    while(b){
        if(b&1) res=res*tmp%mod;
        tmp=tmp*tmp%mod;
        b>>=1;
    }
    return res;
}

int main(){
    int T;
    scanf("%d",&T);
    two[0]=1;
    for(int i=1;i<=1000;i++) two[i]=two[i-1]*2%mod;
    inv[1000]=fast_pow(two[1000],mod-2);
    for(int i=999;i>=0;i--) inv[i]=inv[i+1]*(2)%mod;
    //printf("%I64d\n",inv[0]);
    /*for(int i=0;i<=1000;i++) inv[i]=fast_pow(two[i],mod-2);
    printf("%I64d\n",inv[0]);*/

    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++) scanf("%d",&dir[i]);
        for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) dp[i][j]=0;
        dp[1][1]=1;
        LL pp;
        for(int i=2;i<n;i++){
            p=0;pp=0;
            for(int j=i;j>0;j--){
                if(dir[i]==1) {if(j>0) dp[i][j]=dp[i-1][j-1];}
                else{
                    p=(p+dp[i-1][j])*inv[1]%mod;
                    pp+=(dp[i-1][j])*inv[j]%mod;
                    dp[i][j]=p;
                    //dp[i][j]=(dp[i][j+1]+dp[i-1][j])*inv[1]%mod;
                    if(j==1) dp[i][j]=(p+pp)%mod;
                }
                //printf("i:%d j:%d dp[i][j]:%I64d\n",i,j,dp[i][j]);
            }
            dp[i][0]=0;
        }

        p=0;
        for(int j=1;j<=n-1;j++){
            p=(p+dp[n-1][j]*inv[j])%mod;
        }
        if(n==1) p=1;
        printf("Case #%d: ",Tcase);
        printf("%I64d\n",p);
    }
    return 0;
}
