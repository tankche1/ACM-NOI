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
    fact[n]=power(f[n],mod-2);
    for (int i=n-1;i>=1;--i) fact[i]=(1LL*fact[i+1]*(i+1))%mod;
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
    if (k==1) return 0;
    return (1LL*k*power(k-1,n-1)-1LL*C2(K,k)*gao(n,k-1))%mod;
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
