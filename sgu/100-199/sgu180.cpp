#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;
const int maxn=1e5+1000;
const int inf=1<<30;
int n,g[maxn];
struct Node
{
    int val;
    int id;
    int index;
    bool operator < (const Node &a)const{
        return val<a.val;
    }
}a[maxn];
int pos[maxn];
int lowbit(int x)
{
    return x&(-x);
}
void Update(int x,int val)
{
    for(;x<=n;x+=lowbit(x))
        g[x]+=val;
}
int Sum(int x)
{
    int ans=0;
    for(;x>0;x-=lowbit(x))
        ans+=g[x];
    return ans;
}
int main()
{
    while(scanf("%d",&n)!=EOF)
    {
        long long ans=0;
        memset(g,0,sizeof(g));
        for(int i=1;i<=n;i++)
        {
            a[i].index=i;
            scanf("%d",&a[i].val);
        }
        sort(a+1,a+n+1);
        int cnt=0;
        for(int i=1;i<=n;i++)
        {
            if(i>1&&a[i].val==a[i-1].val)
                pos[a[i].index]=cnt;
            else
                pos[a[i].index]=++cnt;
        }
        for(int i=1;i<=n;i++)
        {
            Update(pos[i],1);
            ans+=i-Sum(pos[i]);
        }
        printf("%lld\n",ans);
    }
    return 0;
}
