# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int mod=1000000007;
LL n,m,k;


LL fast_pow(LL a,LL b){
    //if(b==0) return 1;
    //if(a==0) return 0;
    LL res=1,tmp=a;
    while(b>0){
        if(b&1) res=res*tmp%mod;
        tmp=tmp*tmp%mod;
        b>>=1;
    }
    return res;
}

LL Cm[1000100],Ck[1000100];
LL inv[1000100];

LL calc(LL k){
    if(n==1&&k==1) return 1;
    return k*fast_pow(k-1,n-1)%mod;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int i=1;i<=1000000;i++) inv[i]=fast_pow(i,mod-2);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%lld%lld%lld",&n,&m,&k);
        //for(int i=m-k+1;i<=m;i++) res=res*i%mod;
        //for(int i=1;i<=k;i++) res=res*fast_pow(i,mod-2)%mod;

        Cm[0]=1;
        for(int i=1;i<=k;i++){
            Cm[i]=Cm[i-1]*(m-i+1)%mod;
            Cm[i]=Cm[i]*inv[i]%mod;
        }

        Ck[0]=1;
        for(int i=1;i<=k;i++){
            Ck[i]=Ck[i-1]*(k-i+1)%mod;
            Ck[i]=Ck[i]*inv[i]%mod;
        }

        int op=-1;
        LL res=0;
        for(int p=0;p<k;p++){
            op=-op;
            res=res+op*(Ck[p]*calc(k-p)%mod);
        }
        res=(res%mod+mod)%mod;
        res=res*Cm[k]%mod;

        printf("Case #%d: %lld\n",Tcase,res);
    }
    return 0;
}
