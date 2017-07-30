# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int mod=1000000007;
LL n,m,k;


LL fast_pow(LL a,LL b){
    LL res=1,tmp=a;
    while(b>0){
        if(b&1) res=res*tmp%mod;
        tmp=tmp*tmp%mod;
        b>>=1;
    }
    return res;
}

LL C[1000100];

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%lld%lld%lld",&n,&m,&k);
        LL res=1;
        //for(int i=m-k+1;i<=m;i++) res=res*i%mod;
        //for(int i=1;i<=k;i++) res=res*fast_pow(i,mod-2)%mod;
        C[0]=1;
        for(int i=1;i<=k;i++){
            C[i]=C[i-1]*(m-i+1)%mod;
            C[i]=C[i]*fast_pow(i,mod-2)%mod;
        }

        res=C[k]*k%mod*fast_pow(k-1,n-1)%mod;//printf("res:%lld\n",res);
        if(k>1) res=res-C[k-1]*(k-1)%mod*fast_pow(k-2,n-1)%mod;
        while(res<0) res+=mod;

        printf("Case #%d: %lld\n",Tcase,res);
    }
    return 0;
}
