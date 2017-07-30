#include <algorithm>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <queue>
#include <cmath>
#define maxn 110
#define INF 0x3f3f3f3f
using namespace std;
struct node
{
    double c;
    int v;
    node *next,*back;
};
node *map[maxn*maxn+maxn];
node Point[maxn*maxn*100];
node *cnt=Point;
int n,N;
int a[maxn];
pair<int,int>p[maxn*maxn];
int S,T;
int d[maxn*maxn+maxn];
void add_edge(int u,int v,double c)
{
    node *p=cnt++,*q=cnt++;
    p->v=v;p->c=c;p->next=map[u];map[u]=p;p->back=q;
    q->v=u;q->c=0;q->next=map[v];map[v]=q;q->back=p;
    return;
}
bool BFS()
{
    queue<int>Q;
    memset(d,-1,sizeof d);
    d[S]=0;
    Q.push(S);
    while(!Q.empty())
    {
        int u=Q.front();
        Q.pop();
        for(node *p=map[u];p;p=p->next)
            if(d[p->v]==-1&&p->c>1e-6)
            {
                d[p->v]=d[u]+1;
                Q.push(p->v);
            }
    }
    return d[T]!=-1;
}
double DFS(int u,double tot)
{
    if(u==T)
        return tot;
    if(tot<1e-6) return 0;
    double sum=0;
    for(node *p=map[u];p;p=p->next)
        if(d[p->v]==d[u]+1&&p->c>1e-6)
        {
            double delta=DFS(p->v,min(p->c,tot-sum));
            sum+=delta;
            p->c-=delta;
            p->back->c+=delta;
            if(fabs(sum-tot)<1e-6) return sum;
        }
    if(sum<tot&&fabs(sum-tot)>1e-6) d[u]=-1;
    return sum;
}
double DINIC()
{
    double ans=0;
    while(BFS())
        ans+=DFS(S,INF);
    return ans;
}
double solve(double k)
{
    S=n+N+1,T=n+N+2;
    for(int i=1;i<=T;++i)
        map[i]=NULL;
    cnt=Point;
    for(int i=1;i<=N;++i)
    {
        add_edge(i+n,p[i].first,INF);
        add_edge(i+n,p[i].second,INF);
        add_edge(S,i+n,1);
    }
    for(int i=1;i<=n;++i)
        add_edge(i,T,k);
    return N-DINIC();
}
int main()
{
    int T;
    cin>>T;
    for(int ii=1;ii<=T;++ii)
    {
        N=0;
        printf("Case #%d: ",ii);
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
            scanf("%d",a+i);
        for(int i=1;i<=n;++i)
            for(int j=i+1;j<=n;++j)
                if(a[i]>a[j])
                {
                    N++;
                    p[N]=make_pair(i,j);
                }
        double l=0,r=(n-1)/2.0;
        for(int i=1;i<=30;++i)
        {
            double mid=(l+r)/2;
            if(solve(mid)<=0) r=mid;
            else l=mid;
        }
        printf("%.7lf\n",l);
    }
    return 0;
}
