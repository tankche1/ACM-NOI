#include<iostream>
#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<queue>
#include<algorithm>
#define maxn 100010
using namespace std;
struct node
{
    int l,r,num;
    bool operator <(const node &b)const
    {
        return r>b.r;
    }
}a[maxn];
int n,m;
int path[maxn];
bool vis[maxn];
bool cmp(const node &a,const node &b)
{
    return a.l<b.l;
}
int main()
{
    int T;
    cin>>T;
    while(T--)
    {
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",&a[i].l);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&a[i].r);
            a[i].num=i;
        }
        sort(a+1,a+n+1,cmp);
        priority_queue<node>Q;
        int i=1;m=0;
        while(true)
        {
            while(a[i].l==m&&i<=n) {Q.push(a[i]);i++;}
            while(!Q.empty())
            {
                if(Q.top().r>=m) break;
                Q.pop();
            }
            if(!Q.empty()) {path[++m]=Q.top().num;Q.pop();}
            else break;
        }
        if(!m)
        {
            puts("0");
            for(int i=1;i<n;++i)
                printf("%d ",i);
            printf("%d\n",n);
        }
        else
        {
            printf("%d\n%d",m,path[1]);
            vis[path[1]]=true;
            for(int i=2;i<=m;++i)
            {
                vis[path[i]]=true;
                printf(" %d",path[i]);
            }
            for(int i=1;i<=n;++i)
                if(!vis[i]) printf(" %d",i);
            printf("\n");
        }
        memset(vis,0,sizeof vis);
    }
    return 0;
}
