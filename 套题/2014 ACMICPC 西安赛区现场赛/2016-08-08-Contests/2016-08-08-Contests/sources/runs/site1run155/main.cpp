#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL MO=1e9+7;
const int N=1000005;
LL jc[N],n,m,z,x,y,K,TEST,ans1,ans2,pw[N];
LL pow_mod(LL a,LL b){
    LL s=1;
    while (b)
    {
        if (b&1) s=s*a%MO;
        a=a*a%MO;
        b>>=1ll;
    }
    return s;
}
void pre(){
    jc[0]=1;
    for (int i=1;i<=1000000;++i) jc[i]=(jc[i-1]*i)%MO;
    for (int i=0;i<=1000000;++i) pw[i]=pow_mod(i,MO-2);
}
LL C(LL n,LL k){
    LL ans=1;
    for (LL i=n-k+1;i<=n;++i) ans=ans*i%MO;
    ans=ans*pow_mod(jc[k],MO-2)%MO;
    return ans;
}
void work(){
    cin>>n>>m>>K;
    ans1=K%MO*pow_mod(K-1,n-1)%MO;
    z=-1;x=1;
    for (int i=K-1;i>=1;--i){
        x=x*(i+1)%MO*pw[K-i]%MO;
        ans1=(ans1+MO+z*x*i%MO*pow_mod(i-1,n-1)%MO)%MO;
        z=-z;
    }
    ans1=ans1*C(m,K)%MO;
    cout<<ans1<<endl;
}
int main(){
    //freopen("F.in","r",stdin);freopen("F.out","w",stdout);
    pre();
    cin>>TEST;
    for (int i=1;i<=TEST;++i){
        cout<<"Case #"<<i<<": ";
        work();
    }
}
