# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxk=1000010;
const int mod=(1e+9)+7;
int n,m,k;
LL Cm[maxk];
LL Ck[maxk];
LL num[maxk];
LL inv[maxk];

LL fast_pow(int a,int b){
    LL ans=1,tmp=a;
    while(b>0){
        if(b&1) ans=ans*tmp%mod;
        b>>=1;tmp=tmp*tmp%mod;
    }
    return ans;
}

void prepare(){
    for(int i=1;i<=k;i++){
        inv[i]=fast_pow(i,mod-2);
    }
    Cm[0]=1;
    for(int i=1;i<=k;i++){
        Cm[i]=Cm[i-1]*(m+1-i)%mod*inv[i]%mod;
    }

    Ck[0]=1;
    for(int i=1;i<=k;i++){
        Ck[i]=Ck[i-1]*(k+1-i)%mod*inv[i]%mod;
    }
}

LL calc(LL k){
    if(n==1&&k==1) return 1;
    return k*fast_pow(k-1,n-1)%mod;
}

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d%d",&n,&m,&k);
        prepare();
        int op=-1;
        LL ans=0;
        for(int p=0;p<k;p++){
            op=-op;
            ans=ans+op*(Ck[p]*calc(k-p)%mod);
        }
        ans=(ans%mod+mod)%mod;
        ans=ans*Cm[k]%mod;
        printf("Case #%d: ",Tcase);
        printf("%I64d\n",ans);
    }
    return 0;
}
