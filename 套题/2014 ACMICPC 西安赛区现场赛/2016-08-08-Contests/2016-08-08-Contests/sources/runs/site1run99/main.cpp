#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
using namespace std;
typedef long long LL;
const LL MO=1e9+7;
const int N=1000005;
LL jc[N],n,m,z,x,y,K,TEST,ans1,ans2;
LL pow_mod(LL a,LL b,LL p){
    if (b==0) return 1;
    if (b==1) return a;
    LL t=pow_mod(a,b/2,p);
    t=t*t%p;
    if (b%2==1) t=t*a%p;
    return t;
}
void pre(){
    jc[0]=1;
    for (int i=1;i<=1000000;++i) jc[i]=(jc[i-1]*i)%MO;
}
LL C(LL n,LL k,LL p){
    LL ans=1;
    for (int i=n-k+1;i<=n;++i) ans=ans*i%p;
    ans=ans*pow_mod(jc[k],p-2,p)%p;
    return ans;
}
void work(){
    cin>>n>>m>>K;
    ans1=C(m,K,MO);
    ans1=ans1*K%MO*pow_mod(K-1,n-1,MO)%MO;
    if (K==1) ans2=1;
    else {
        ans2=C(m,K-1,MO);
        ans2=ans2*(K-1)%MO*pow_mod(K-2,n-1,MO)%MO;
    }
    ans1=(ans1+MO-ans2)%MO;
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
