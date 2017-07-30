#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<algorithm>
#define maxn 50050
using namespace std;
struct node
{
    int l,r;
    bool operator <(const node &b)const
    {
        return r>b.r||(r==b.r&&l>b.l);
    }
    node(){}
    node(int l,int r)
    {
        this->l=l;
        this->r=r;
    }
}a[maxn],b[maxn];
priority_queue<node>Q;
int n;
bool vis[maxn];
int x;
bool cmp(const node &a,const node &b)
{
    return a.l<b.l||(a.l==b.l&&a.r<b.r);
}
int main()
{
    int T;
    cin>>T;
    int k=0;
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d%d",&a[i].l,&a[i].r);
        sort(a+1,a+n+1,cmp);
        int m=0;
        int now=1;
        x=1;
        while(m<n)
        {
            if(Q.empty())
            {
                if(now>m)
                {
                    int p,ans=0x3f3f3f3f;
                    for(int j=x;j<=n;++j)
                        if(!vis[j]&&a[j].r<ans)
                        {
                            ans=a[j].r;
                            p=j;
                        }
                    vis[p]=true;
                    b[++m]=a[p];
                    now=m;
                    for(int j=x;j<=n&&j-1000<=x;++j)
                        if(!vis[j]&&a[j].l<=a[p].r)
                        {
                            Q.push(a[j]);
                            vis[j]=true;
                        }
                        else if(a[j].l>a[p].r)
                        {
                            x=j;
                            break;
                        }
                }
                else
                {
                    for(int j=x;j<=n&&j-1000<=x;++j)
                        if(!vis[j]&&a[j].l<=b[now].r)
                        {
                            Q.push(a[j]);
                            vis[j]=true;
                        }
                        else if(a[j].l>b[now].r)
                        {
                            x=j;
                            break;
                        }
                }
            }
            else
            {
                int tm=now;
                while(!Q.empty())
                {
                    b[++m]=Q.top();
                    Q.pop();
                    k=max(k,m-now);
                }
                now++;
            }
        }
        printf("%d\n",k);
        for(int i=1;i<=n;++i)
            printf("%d %d\n",b[i].l,b[i].r);
        memset(vis,0,sizeof vis);
    }
    return 0;
}
