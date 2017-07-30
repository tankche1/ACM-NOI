#include <bits/stdc++.h>
#define ll double
using namespace std;
const int maxn=11000+10;
const double eps=1e-6;
const double INF=1e9;
int n,s,t,m,cur[maxn],vis[maxn],dis[maxn],T,a[maxn],ns[maxn],nt[maxn],tt;
struct edge
{
  int to,next;
  ll cap;
}E[maxn * 100];
/*vector<edge> edges;
vector<int> g[maxn];
void addedge(int from,int to,ll cap)
{
  edges.push_back((edge){from,to,cap,0});
  edges.push_back((edge){to,from,0,0});
  int m1=edges.size();
  g[from].push_back(m1-2);
  g[to].push_back(m1-1);
}*/
int line[maxn],tot = 1;
inline void addedge(int x,int y,ll v) {
  tot ++; E[tot].to = y; E[tot].next = line[x]; line[x] = tot; E[tot].cap = v;
  tot ++; E[tot].to = x; E[tot].next = line[y]; line[y] = tot; E[tot].cap = 0;
}
bool bfs()
{
  for(int i=s;i<=t;i++) vis[i]=0;
  queue<int> Q;Q.push(s);vis[s]=1;dis[s]=0;
  while(!Q.empty())
  {
    int x=Q.front();Q.pop();
    for(int i = line[x];i != 0;i = E[i].next)
    {
      //edge e=edges[g[x][i]];
      int p = E[i].to;
      if(E[i].cap > 0 && !vis[p])
      {
        vis[p]=1;
        dis[p]=dis[x]+1;
        Q.push(p);
      }
    }
  }
  return vis[t];
}
ll dfs(int x,ll a)
{
  if(x==t||a==0) return a;
  ll flow = 0,f = 0; int p = 0;
  for(int &i=cur[x];i != 0;i = E[i].next)
  {
    //edge &e=edges[g[x][i]];
    p = E[i].to;
    if(dis[p]==dis[x]+1 && (f = dfs(p,min(a,E[i].cap))) > eps)
    {
      E[i].cap -= f;
      E[i^1].cap += f;
      flow += f;
      a -= f;
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
    for(int i=s;i<=t;i++) cur[i]=line[i];
    flow+=dfs(s,INF);
  }
  return flow;
}
bool check(double li)
{
  /*edges.clear();
  for(int i=s;i<=t;i++) g[i].clear();*/
  tot = 1;s=0,t=n+m+1;
  for(int i=s;i<=t;i++) line[i]=0;
  for(int i=1;i<=n;i++) addedge(i,t,li);
  for(int i=n+1;i<=n+m;i++) addedge(s,i,1);
  for(int i=1;i<=m;i++)
  {
    addedge(n+i,ns[i],INF);
    addedge(n+i,nt[i],INF);
  }
  ll res=maxflow();
  res=m-res;
  return res>0;
}
int main()
{
  //freopen("C.in","r",stdin);
  //freopen("C.out","w",stdout);
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
    ll l=(ll)m/n,r=m/2.0,ans=l;
    while(l+eps<=r)
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
