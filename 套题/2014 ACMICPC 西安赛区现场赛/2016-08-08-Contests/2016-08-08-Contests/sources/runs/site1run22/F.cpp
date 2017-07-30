#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#define mod 1000000007
using namespace std;
typedef long long LL;
LL n,m,k;
LL power(LL a,LL b)
{
    if(!a) return 0;
    LL ret=1;
    while(b)
    {
        if(b&1) ret=ret*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return ret;
}
LL C(LL n,LL m)
{
    LL ret=1;
    for(LL i=n;i>n-m;--i)
        ret=ret*i%mod;
    for(LL i=2;i<=m;++i)
        ret=ret*power(i,mod-2)%mod;
    return ret;
}
LL solve(LL k,LL n)
{
    return k*power(k-1,n-1)%mod;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        cin>>n>>m>>k;
        LL ans=C(m,k);
        ans=ans*((solve(k,n)-solve(k-1,n)+mod)%mod)%mod;
        cout<<ans<<endl;
    }
    return 0;
}
