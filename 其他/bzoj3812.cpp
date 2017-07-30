# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int maxn=16;
typedef long long LL;
int mod=1000000007;
int n,m;
int out[1<<maxn],in[1<<maxn],p[1<<maxn];
int digit[270];

LL F[1<<maxn],g[1<<maxn];
int h[1<<maxn];
LL two[maxn*maxn];

int Count(int x){
    return digit[x&255]+digit[x>>8];
}

int main(){
    int a,b;
    scanf("%d%d",&n,&m);
    digit[0]=0;
    for(int i=1;i<(1<<8);i++) digit[i]=digit[i>>1]+(i&1);

    for(int i=1;i<=m;i++){
        scanf("%d%d",&a,&b);a--;b--;
        out[1<<a]|=(1<<b);in[1<<b]|=(1<<a);
    }
    two[0]=1;for(int i=1;i<=m;i++) {two[i]=two[i-1]<<1;if(two[i]>=mod) two[i]-=mod;}

    F[0]=0;h[0]=0;
    LL way;
    for(int S=1;S<(1<<n);S++){
        int one=S&(-S);int sta=S^one;
        h[S]=h[sta]+Count(in[one]&sta)+Count(out[one]&sta);

        g[S]=0;
        for(int j=sta;j;j=(j-1)&sta){
            g[S]=(g[S]+mod-g[j]*F[S^j])%mod;
        }

        F[S]=two[h[S]];
        for(int T=S;T;T=(T-1)&S){
            if(S==T) p[0]=0;
            else{
                one=(S^T)&(-(S^T));
                p[S^T]=p[S^T^one]-Count(in[one]&(S^T^one));
                p[S^T]+=Count(out[one]&(T));
            }
            F[S]=(F[S]+mod-g[T]*two[h[S^T]+p[S^T]]%mod)%mod;
        }

        g[S]=(g[S]+F[S])%mod;
    }

    printf("%I64d\n",F[(1<<n)-1]);
    return 0;
}
