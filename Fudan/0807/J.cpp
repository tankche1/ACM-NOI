#include<iostream>
#include<cstring>
#include<cstdlib>
#include<cstdio>
#include<algorithm>
#define maxn 100010
#define mod 1000000007
using namespace std;
typedef unsigned long long LL;
struct node
{
    int v,f;
    bool operator <(const node &b)const
    {
        return v<b.v;
    }
}a[maxn];
int n;
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
    for(int ii=1;ii<=T;++ii)
    {
        printf("Case %d: ",ii);
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d%d",&a[i].v,&a[i].f);
        sort(a+1,a+n+1);
        LL sum=0,ans=0;
        for(int i=1;i<=n;++i)
        {
            sum+=a[i].f;
            ans+=sum*a[i].f;
        }
        sum=1;
        for(int i=1;i<n;++i)
            sum=sum*(a[i].f+1)%mod;
        printf("%llu %llu\n",ans,sum);
    }
    return 0;
}
