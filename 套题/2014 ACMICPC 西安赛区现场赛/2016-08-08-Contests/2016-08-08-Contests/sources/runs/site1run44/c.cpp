#include<cstdio>
#include<cstring>
#include<iostream>

using namespace std;
const double lim=1e-12;
const double eps=1e-8;
const int inf=1000000007;
struct way{double flow;int po,next;} e[2000010];
int numh[5110],p[5110],h[5110],cur[5110],x[5110],y[5110],pre[5110],a[110];
double d[5110];
int n,m,len,cas,t;
void add(int x,int y,double f)
{
  e[++len].po=y;
  e[len].flow=f;
  e[len].next=p[x];
  p[x]=len;
}

void build(int x,int y,double f)
{
  add(x,y,f);
  add(y,x,0);
}

double sap()
{
  memset(h,0,sizeof(h));
  memset(numh,0,sizeof(numh));
  memcpy(cur,p,sizeof(p));
  numh[0]=t+1;
  int u=0,j;
  double neck=inf,s=0;
  while (h[0]<t+1)
  {
    d[u]=neck;
    bool ch=1;
    for (int i=cur[u];i>-1;i=e[i].next)
    {
      int j=e[i].po;
      if (h[u]==h[j]+1&&e[i].flow>lim)
      {
        cur[u]=i; pre[j]=u; u=j;
        neck=min(neck,e[i].flow);
        ch=0;
        if (u==t)
        {
          s+=neck;
          while (u)
          {
            u=pre[u];
            j=cur[u];
            e[j].flow-=neck;
            e[j^1].flow+=neck;
          }
          neck=inf;
        }
        break;
      }
    }
    if (ch)
    {
      if (--numh[h[u]]==0) return s;
      int q=-1,tmp=t;
      for (int i=p[u]; i>-1; i=e[i].next)
      {
        int j=e[i].po;
        if (h[u]<tmp&&e[i].flow>lim)
        {
          q=i;
          tmp=h[u];
        }
      }
      h[u]=tmp+1; cur[u]=q; ++numh[h[u]];
      if (u)
      {
        u=pre[u];
        neck=d[u];
      }
    }
  }
  return s;
}

bool check(double mid)
{
  len=-1; memset(p,255,sizeof(p));
  for (int i=1; i<=m; i++)
  {
    build(x[i]+m,i,inf);
    build(y[i]+m,i,inf);
    build(i,t,1);
  }
  for (int i=1; i<=n; i++)
    build(0,i+m,mid);
  double f=sap();
  if (m-f>=lim) return 1;
  else return 0;
}

int main()
{
  scanf("%d",&cas);
  for (int tt=1; tt<=cas; tt++)
  {
    scanf("%d",&n);
    for (int i=1; i<=n; i++)
      scanf("%d",&a[i]);
    m=0;
    for (int i=1; i<=n; i++)
      for (int j=1; j<i;j++)
        if (a[i]<a[j]) {x[++m]=i;y[m]=j;}
    t=n+m+1;
    double l=0,r=m;
    double ans=0;
    while (r-l>eps)
    {
      double mid=(l+r)/2;
      if (check(mid))
      {
        ans=mid;
        l=mid;
      }
      else r=mid;
    }
    printf("Case #%d: %.8lf",tt,ans);
  }
  return 0;
}


