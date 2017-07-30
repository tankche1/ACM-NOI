# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2010;
const int mod=1000000007;
typedef long long LL;
int n;
int p[maxn];

LL F[maxn][maxn];
LL dp[maxn][maxn];

inline int lowbit(int x) {return x&(-x);}

struct FenwickTree{
    LL C[maxn];
    void clear(){
        memset(C,0,sizeof(C));
    }

    void add(int x,LL v){
        //printf("x:%d v:%lld\n",x,v);
        while(x<=n){
            C[x]+=v;
            while(C[x]>=mod) C[x]-=mod;
            x+=lowbit(x);
        }
    }

    LL sum(int x){
        LL res=0;
        while(x>0){
            res+=C[x];x-=lowbit(x);
            while(res>=mod) res-=mod;
        }
        return res;
    }

}fwt;

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d",&p[i]);

    F[1][1]=1;
    for(int i=2;i<=n;i++){
        F[i][1]=1;F[i][i]=F[i-1][i-1]*i%mod;
        for(int j=2;j<i;j++){
            F[i][j]=(F[i-1][j-1]+F[i-1][j])*j%mod;
        }
    }

    for(int i=1;i<=n;i++){
        dp[1][i]=1;
    }
    for(int i=2;i<=n;i++){
        fwt.clear();
        for(int j=i;j<=n;j++){
            if(dp[i-1][j-1]>0) fwt.add(p[j-1],dp[i-1][j-1]);
            dp[i][j]=fwt.sum(p[j]-1);
            //printf("dp[%d][%d]:%lld\n",i,j,dp[i][j]);
        }
    }

    LL sum,ans=0;
    for(int i=1;i<=n;i++){
        sum=0;
        for(int j=i;j<=n;j++) sum+=dp[i][j];
        sum%=mod;
        //printf("i:%d sum:%lld F[n][i]:%lld\n",i,sum,F[n][i]);
        ans=(ans+sum*F[n][i])%mod;
    }
    printf("%lld\n",ans);
    return 0;
}
