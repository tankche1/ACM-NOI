#include <bits/stdc++.h>
#define ll double
using namespace std;
const int maxn=11000+10;
const double eps=1e-6;
const double INF=1e9;
int n,s,t,m,cur[maxn],vis[maxn],dis[maxn],T,a[maxn],ns[maxn],nt[maxn],tt;
struct edge
{
  int from,to;
  ll cap,flow;
};
vector<edge> edges;
vector<int> g[maxn];
void addedge(int from,int to,ll cap)
{
  edges.push_back((edge){from,to,cap,0});
  edges.push_back((edge){to,from,0,0});
  int m1=edges.size();
  g[from].push_back(m1-2);
  g[to].push_back(m1-1);
}
bool bfs()
{
  memset(vis,0,sizeof(vis));
  queue<int> Q;Q.push(s);vis[s]=1;dis[s]=0;
  while(!Q.empty())
  {
    int x=Q.front();Q.pop();
    for(int i=0;i<g[x].size();i++)
    {
      edge e=edges[g[x][i]];
      if(e.cap>e.flow&&!vis[e.to])
      {
        vis[e.to]=1;
        dis[e.to]=dis[x]+1;
        Q.push(e.to);
      }
    }
  }
  return vis[t];
}
ll dfs(int x,ll a)
{
  if(x==t||a<eps) return a;
  ll flow=0,f;
  for(int &i=cur[x];i<g[x].size();i++)
  {
    edge &e=edges[g[x][i]];
    if(dis[e.to]==dis[x]+1&&(f=dfs(e.to,min(a,e.cap-e.flow)))>eps)
    {
      e.flow+=f;
      edges[g[x][i]^1].flow-=f;
      flow+=f;
      a-=f;
      if(a<eps) break;
    }
  }
  return flow;
}
ll maxflow()
{
  ll flow=0;
  while(bfs())
  {
    memset(cur,0,sizeof(cur));
    flow+=dfs(s,INF);
  }
  return flow;
}
bool check(double li)
{
  edges.clear();
  for(int i=s;i<=t;i++) g[i].clear();
  for(int i=1;i<=n;i++) addedge(i,t,li);
  for(int i=n+1;i<=n+m;i++) addedge(s,i,1);
  for(int i=1;i<=m;i++)
  {
    addedge(n+i,ns[i],INF);
    addedge(n+i,nt[i],INF);
  }
  ll res=maxflow();
  res=m-res;
  return res>eps;
}
int main()
{
  scanf("%d",&T);
  while(T--)
  {
    scanf("%d",&n);m=0;
    for(int i=1;i<=n;i++) scanf("%d",&a[i]);
    for(int i=1;i<=n;i++)
      for(int j=i+1;j<=n;j++)
        if(a[i]>a[j])
        {
          m++;
          ns[m]=i;nt[m]=j;
        }
    s=0,t=n+m+1;
    ll l=(ll)m/(ll)n,r=m,ans=l;
    while(fabs(r-l)>eps)
    {
      ll mid=(l+r)/2.0;
      if(check(mid))
      {
        ans=mid;
        l=mid;
      }
      else r=mid;
    }
    tt++;cout<<"Case #"<<tt<<": ";
    printf("%.6lf\n",ans);
  }
  return 0;
}
