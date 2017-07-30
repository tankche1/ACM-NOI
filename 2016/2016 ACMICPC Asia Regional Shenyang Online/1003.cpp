# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int mod=1000000007;
const int maxn=1000010;
typedef long long LL;
int m,n,k;
LL jie[maxn];
LL inv[maxn];

LL fast_pow(int a,int b){
    LL res=1,tmp=a;
    while(b){
        if(b&1) res=res*tmp%mod;
        b>>=1;tmp=tmp*tmp%mod;
    }
    return res;
}

void prepare(){
    jie[0]=1;
    for(int i=1;i<=1000000;i++) jie[i]=jie[i-1]*i%mod;
    inv[1000000]=fast_pow(jie[1000000],mod-2);
    for(int i=999999;i>=0;i--){
        inv[i]=inv[i+1]*(i+1)%mod;
    }
    //printf("inv[0]:%I64d\n",inv[0]);
}

LL C(int m,int n){
    return (jie[m]*inv[n]%mod)*inv[m-n]%mod;
}

int main(){
    int Case;
    scanf("%d",&Case);

    prepare();
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d%d",&m,&n,&k);
        if(n==1) {printf("%d\n",m);continue;}
        if((n)*k+n>m) {puts("0");continue;}
        LL ans=C(m-n*k-1,n-1)*k%mod;
        ans=(ans+C(m-n*k,n))%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
