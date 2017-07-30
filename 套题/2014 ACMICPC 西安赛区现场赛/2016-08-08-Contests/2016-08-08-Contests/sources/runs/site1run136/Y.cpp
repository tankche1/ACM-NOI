#include <queue>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 120
#define M 15000
#define P 105
#define eps 1e-8
#define inf 99999999.9
using namespace std;
struct Ahri
{
	int v,n;
	double l;
}e[M];
int head[N],cnt;
inline void add(int u,int v,double l)
{
	e[++cnt].v=v;
	e[cnt].l=l;
	e[cnt].n=head[u];
	head[u]=cnt;
}
inline void ADD(int u,int v,double l)
{add(u,v,l),add(v,u,0.0);}

queue<int>q;
int s,t,dep[N];
bool bfs()
{
	while(!q.empty())q.pop();
	memset(dep,0,sizeof dep);
	q.push(s),dep[s]=1;
	
	int i,u,v;
	while(!q.empty())
	{
		u=q.front(),q.pop();
		for(i=head[u];i;i=e[i].n)
		{
			if(!dep[v=e[i].v]&&e[i].l>eps)
			{
				dep[v]=dep[u]+1;
				if(v==t)return 1;
				q.push(v);
			}
		}
	}
	return 0;
}
double dinic(int x,double flow)
{
	if(x==t)return flow;
	int i,v;
	double remain=flow,k;
	for(i=head[x];i&&remain>eps;i=e[i].n)
	{
		if(dep[v=e[i].v]==dep[x]+1&&e[i].l>eps)
		{
			k=dinic(v,min(remain,e[i].l));
			if(k<eps)dep[v]=0;
			e[i].l-=k,e[i^1].l+=k;
			remain-=k;
		}
	}
	return flow-remain;
}
int n,sn[P],sum[P];
void input()
{
	scanf("%d",&n);
	for(int i=1;i<=n;i++)scanf("%d",&sn[i]);
	s=n+1,t=n+2;
}
void init()
{
	memset(head,0,sizeof head);
	memset(sum,0,sizeof sum);
	cnt=1;
}

void debug(double mid)
{
	printf("At %.8lf\n",mid);
	for(int k=1;k<=n;k++)
	{
		bool flag=0;
		for(int i=head[k];i;i=e[i].n)
		{
			if(e[i].v==t&&e[i].l>eps)flag=1;
		}
		if(!flag)printf("#%d is selected.\n",k);
	}
}

bool check(double mid)
{
	init();
	int i,j;
	double maxflow=0.0;

	for(i=1;i<=n;i++)
	{
		for(j=1;j<i;j++)if(sn[i]<sn[j])
			ADD(j,i,1.0),sum[j]++;
	}
	for(i=1;i<=n;i++)
	{
		ADD(s,i,(double)sum[i]);
		maxflow+=sum[i];
		ADD(i,t,mid);
	}
	while(bfs())maxflow-=dinic(s,inf);
	
//	if(mid<5)debug(mid);
	
	if(maxflow>eps)return 1;
	else return 0;
}
void work()
{
	double l=0.0,r=5000.0,mid;
	for(int k = 0; k < 100; k ++)
	{
		mid=(l+r)/2.0;
		if(check(mid))l=mid;
		else r=mid;
	}
	printf("%.8lf\n",l);
}


int main()
{
//	freopen("test.in","r",stdin);

	int g,T=0;
	for(scanf("%d",&g);g--;)
	{
		printf("Case #%d: ",++T);
		input();
		work();
	}

	return 0;
}

