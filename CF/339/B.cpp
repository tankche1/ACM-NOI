#include<map>
#include<set>
#include<cmath>
#include<stack>
#include<queue>
#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<iostream>
#include<algorithm>
#define pi acos(-1)
#define mod 10000007
#define inf 1000000000
#define ll long long
using namespace std;
ll read()
{
    ll x=0,f=1;char ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9'){x=x*10+ch-'0';ch=getchar();}
    return x*f;
}
struct data{
    ll id,v;
}a[100005];
bool cmp(data a,data b){
    if(a.v==b.v)return a.id<b.id;
    return a.v<b.v;
}
ll n,A,cf,cm,m,num;
ll ans,L,R,ans2[100005];
ll sum[100005];
ll cal(ll m,ll R)
{
    ll l=0,r=A,ans=0;
    while(l<=r)
    {
        ll mid=(l+r)>>1;
        int p=lower_bound(a+1,a+n+1,(data){0,mid},cmp)-a-1;
        if(p>=R-1)p=R-1;
        if(p*mid-sum[p]<=m)ans=mid,l=mid+1;
        else r=mid-1;
    }
    return ans;
}
int main()
{
    n=read();A=read();cf=read();cm=read();m=read();
    for(int i=1;i<=n;i++)
        a[i].v=read(),a[i].id=i;
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=n;i++)sum[i]=sum[i-1]+a[i].v;
    L=cal(m,n+1);ans=L*cm;R=n+1;
    for(int i=n;i;i--)
    {
        m-=A-a[i].v;
        num++;
        if(m>=0)
        {
            ll mn=cal(m,i);
            if(num*cf+mn*cm>ans)
            {
                ans=num*cf+mn*cm;
                L=mn;R=i;
            }
        }
    }
    cout<<ans<<endl;
    for(int i=1;i<=n;i++)
    {
        if(i>=R)ans2[a[i].id]=A;
        else if(a[i].v<=L)ans2[a[i].id]=L;
        else ans2[a[i].id]=a[i].v;
    }
    for(int i=1;i<=n;i++)
        printf("%d ",ans2[i]);
    return 0;
}
