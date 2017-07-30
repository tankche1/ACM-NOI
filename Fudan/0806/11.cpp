#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#define mod 1000000007
using namespace std;
typedef long long LL;
LL power(LL a,LL b)
{
    LL sum=1;
    while(b)
    {
        if(b&1) sum=sum*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return sum;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        LL n;
        scanf("%I64d",&n);
        LL ou=n/2,ji=(n+1)/2;
        LL ans=(power(2,ji-1)*power(2,ou)%mod-1+mod)%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
