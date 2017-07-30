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

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%lld%lld%lld",&n,&m,&k);
        //for(int i=m-k+1;i<=m;i++) res=res*i%mod;
        //for(int i=1;i<=k;i++) res=res*fast_pow(i,mod-2)%mod;
        Cm[0]=1;
        for(int i=1;i<=k;i++){
            Cm[i]=Cm[i-1]*(m-i+1)%mod;
            Cm[i]=Cm[i]*fast_pow(i,mod-2)%mod;
        }

        Ck[0]=1;
        for(int i=1;i<=k;i++){
            Ck[i]=Ck[i-1]*(k-i+1)%mod;
            Ck[i]=Ck[i]*fast_pow(i,mod-2)%mod;
        }

        int op=-1;
        LL res=0;
        for(int p=0;p<k;p++){
            op=-op;
            res=(res+(LL)op*Ck[k-p]*(k-p)%mod*fast_pow(k-p-1,n-1))%mod;
        }
        res=res*Cm[k]%mod;

        printf("Case #%d: %lld\n",Tcase,res);
    }
    return 0;
}
