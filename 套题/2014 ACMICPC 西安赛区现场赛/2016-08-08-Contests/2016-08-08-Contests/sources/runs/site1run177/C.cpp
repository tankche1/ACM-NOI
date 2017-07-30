#include<iostream>
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
struct node
{
	int from,to,next;
	double cap;
}Fu[800010];
int nn=1;
int head[40010];
int hh[40010];
int ss,ee;
void addedge(int f,int t,double c)
{
	swap(f,t);
	++nn;
	Fu[nn].next=head[f];
	Fu[nn].from=f;
	Fu[nn].cap=c;
	Fu[nn].to=t;
	head[f]=nn;
	++nn;
	Fu[nn].next=head[t];
	Fu[nn].from=t;
	Fu[nn].cap=0;
	Fu[nn].to=f;
	head[t]=nn;
}
int dis[40010];
queue<int> Q;
const double eps=1e-8;
int cc=0;
bool bfs(int s,int e)
{
//	cc++;
	memset(dis,0x3f,sizeof(dis));
	dis[s]=0;
	Q.push(s);
	memcpy(hh,head,sizeof(head));
	while(Q.size())
	{
		int now=Q.front();
		Q.pop();
		for(int k=head[now];k;k=Fu[k].next)
			if(Fu[k].cap>eps&&dis[Fu[k].to]==0x3f3f3f3f)
				dis[Fu[k].to]=dis[now]+1,Q.push(Fu[k].to);
	}
	return dis[e]!=0x3f3f3f3f;
}
double dfs(int now,double flow,int e)
{
//	cout<<now<<" "<<flow<<endl;
	if(now==e||flow<=eps) return flow;
	cc++;
	double ans=0,maxflow;
	for(int &k=hh[now];k;k=Fu[k].next)
		if(Fu[k].cap>eps&&dis[Fu[k].to]==dis[now]+1&&(maxflow=dfs(Fu[k].to,min(Fu[k].cap,flow),e)))
		{
			if(maxflow<=eps) continue;
			Fu[k].cap-=maxflow;
			Fu[k^1].cap+=maxflow;
			ans+=maxflow;
			flow-=maxflow;
		}
	return ans;
}
int a[1010];
int main()
{
	int T;
	cin>>T;
	for(int tt=1;tt<=T;tt++)
	{
		nn=1;
		int N;
		cin>>N;
//		for(int i=1;i<=N;i++)
//			a[i]=i;
		for(int i=1;i<=N;i++)
//			swap(a[rand()%N+1],a[rand()%N+1]);
			cin>>a[i];
		int cnt=0;
		for(int i=1;i<=N;i++)
			for(int j=i+1;j<=N;j++)
				if(a[i]>a[j])
					cnt++;
//		cout<<cnt<<endl;
		double l=0.0,r=1e2;
		int t=0;
		while(r-l>eps)
		{
			t++;
			double mid=(r+l)/2;
			double res=cnt;
			nn=1;
			memset(head,0,sizeof(head));
			ss=0,ee=N*N+N+10;
			for(int i=1;i<=N;i++)
				for(int j=i+1;j<=N;j++)
					if(a[i]>a[j])
					{
						addedge(ss,(i-1)*N+j,1);
						addedge((i-1)*N+j,N*N+i,1e9);
						addedge((i-1)*N+j,N*N+j,1e9);
					}
			for(int i=1;i<=N;i++)
				addedge(N*N+i,ee,mid);
			swap(ss,ee);
			while(bfs(ss,ee)) res-=dfs(ss,1e9,ee);
			if(res>0)
				l=mid;
			else r=mid;
		}
//		cout<<cc<<endl;
		printf("Case #%d: %.12lf\n",tt,l);
	}
}
