#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int n,m,K;
void init(){
    scanf("%d%d%d",&n,&m,&K);
}
int power(int a,int t){
    int ans=1;
    for (;t;t>>=1,a=1LL*a*a%mod) if (t&1) ans=1LL*ans*a%mod;
    return ans;
}
int fact[1000011],f[1000011];
void preset(int n=1000000){
    f[0]=1; for (int i=1;i<=n;++i) f[i]=1LL*f[i-1]*i%mod;
    cout<<f[100000]<<endl;
    fact[n]=power(f[n],mod-2);
    for (int i=n-1;i>=0;--i) fact[i]=(1LL*fact[i+1]*(i+1))%mod;
}
int C(int n,int k){
    int tmp=fact[k];
    for (int i=1;i<=k;++i) tmp=(1LL*tmp*(n-i+1))%mod;
    return tmp;
}
int C2(int n,int m){
    return ((1LL*f[n]*fact[m])%mod*fact[n-m])%mod;
}
int gao(int n,int k){
    long long ans=0,x=1,t=k;
    for (int i=k;i>=2;--i,x*=-1){
        ans=(ans+x*t*i%mod*power(i-1,n-1))%mod;
        t=t*i%mod;
    }
    return ans%mod;
}
void work(){
    int ans=(1LL*C(m,K)*gao(n,K))%mod; ans=(ans+mod)%mod;
    printf("%d\n",ans);
}
int main(){
    int T; scanf("%d",&T); preset();
    for (int t=1;t<=T;++t) init(),printf("Case #%d: ",t),work();
    return 0;
}
