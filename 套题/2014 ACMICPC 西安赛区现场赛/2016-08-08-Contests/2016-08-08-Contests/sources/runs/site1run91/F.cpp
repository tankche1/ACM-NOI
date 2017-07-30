#include<bits/stdc++.h>
using namespace std;
const int mod=1000000007;
int n,m,k;
void init(){
    scanf("%d%d%d",&n,&m,&k);
}
int power(int a,int t){
    int ans=1;
    for (;t;t>>=1,a=1LL*a*a%mod) if (t&1) ans=1LL*ans*a%mod;
    return ans;
}
int fact[1000011];
void preset(int n=1000000){
    int tmp=1; for (int i=1;i<=n;++i) tmp=(1LL*tmp*i)%mod;
    fact[n]=power(tmp,mod-2);
    for (int i=n-1;i>=1;--i) fact[i]=(1LL*fact[i+1]*(i+1))%mod;
}
int C(int n,int k){
    int tmp=fact[k];
    for (int i=1;i<=k;++i) tmp=(1LL*tmp*(n-i+1))%mod;
    return tmp;
}
int gao(int n,int k){
    return (1LL*k*power(k-1,n-1)-1LL*(k-1)*power(k-2,n-1))%mod;
}
void work(){
    int ans=(1LL*C(m,k)*gao(n,k))%mod; ans=(ans+mod)%mod;
    printf("%d\n",ans);
}
int main(){
    int T; scanf("%d",&T); preset();
    for (int t=1;t<=T;++t) init(),printf("Case #%d: ",t),work();
    return 0;
}
