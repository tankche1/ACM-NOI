#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
const int N=101;
const int INF=2100000000;
int q[N],f[N],map[N][N],temp[N][N];
int n,s1,e1,s2,e2,q1,q2,i,j,flow,tt;
char c,enter;
bool flag;
bool bfs()
{
  memset(q,0,sizeof(q));
  memset(f,-1,sizeof(f));
  int h=0,t=1;f[0]=1;
  while (h<t)
  {
    int now=q[++h];if (now==n) return 1;
    for (int i=0;i<=n;i++)
      if (map[now][i]&&f[i]==-1)
      {
        q[++t]=i;
        f[i]=f[now]+1;
      }
  }
  return 0;
}
int dinic(int sta,int sum)
{
  if (sta==n) return sum;
  int os=sum;
  for (int i=0;i<=n;i++)
    if (map[sta][i]&&f[i]==f[sta]+1)
    {
      int Min=dinic(i,min(os,map[sta][i]));
      map[sta][i]-=Min;map[i][sta]+=Min;os-=Min;
    }
  if (os==sum) f[sta]=-1;
  return sum-os;
}
int main()
{
  while (scanf("%d%d%d%d%d%d%d",&n,&s1,&e1,&q1,&s2,&e2,&q2)!=EOF)
  {
    s1++;e1++;s2++;e2++;
    memset(map,0,sizeof(map));
    memset(temp,0,sizeof(temp));
    for (i=1;i<=n;i++)
    {
      scanf("%c",&enter);
      for (j=1;j<=n;j++) 
      {
        scanf("%c",&c);
        if (c=='O') map[i][j]=temp[i][j]=2;else if (c=='N') map[i][j]=temp[i][j]=INF;
      }
    }
    flag=true;
    flow=0;map[0][s1]=q1*2;map[0][s2]=q2*2;map[e1][++n]=q1*2;map[e2][n]=q2*2;
    while (bfs()) 
    {
      tt=dinic(0,INF);
      flow+=tt;
    }
    if (flow<2*(q1+q2)) flag=false;
    if (flag)
    {
      memset(map,0,sizeof(map));
      for (i=1;i<n;i++)
        for (j=1;j<n;j++)
          map[i][j]=temp[i][j];
      map[0][s1]=q1*2;map[0][e2]=q2*2;map[e1][n]=q1*2;map[s2][n]=q2*2;flow=0;
      while (bfs())
      {
        tt=dinic(0,INF);
        flow+=tt;
      }  
      if (flow<2*(q1+q2)) flag=false;
    }
    if (flag) printf("Yes\n");else printf("No\n");
  }
  return 0;
}