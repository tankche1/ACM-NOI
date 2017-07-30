# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=2010;
const LL mod=258280327;
LL live,dead;

LL fpow(LL a,LL b){
    if(b==0) return 1;
    LL ans=fpow(a,b>>1);
    ans*=ans;ans%=mod;
    if(b&1) ans=ans*a%mod;
    return ans;
}

LL g[maxn][maxn];
LL c[maxn];
LL ans[maxn];

int main(){
    int n;LL x,y;
    int tcase;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%I64d%I64d",&n,&x,&y);
        dead=x*fpow(y,mod-2)%mod;
        live=(1-dead+mod)%mod;
        c[0]=1;
        for(int i=1;i<=n;i++) c[i]=c[i-1]*live%mod;

        for(int i=0;i<=n;i++)
            for(int j=0;j<=n;j++)
                g[i][j]=0;
        g[0][0]=1;
        for(int i=1;i<=n;i++){
            for(int j=0;j<=i;j++){
                g[i][j]=g[i-1][j]*(1-c[j]+mod)%mod;
                if(j!=0) g[i][j]=(g[i][j]+g[i-1][j-1]*c[j-1])%mod;
            }
        }
        for(int k=0;k<n;k++){
            ans[k]=0;
            for(int i=k;i<n;i++)
                ans[k]=(ans[k]+g[i][k]*c[k])%mod;
            ans[k]=ans[k]*fpow(n,mod-2)%mod;
            if(k) printf(" ");
            printf("%I64d",ans[k]);
        }puts("");
    }
    return 0;
}
