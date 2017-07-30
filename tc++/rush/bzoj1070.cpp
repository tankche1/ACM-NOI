/*
拆点 m工人变成m*n个点 表示他修的倒数第i辆车 连车 费用为i*cost
*/
# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxnode=700;
const int maxm=10;
const int maxn=62;
const int INF=~0U>>1;

struct Edge{
	int from,to,flow,cap,cost;
	
	void give(int fr,int t,int fl,int ca,int co){
		from=fr;to=t;flow=fl;cap=ca;cost=co;
	}
};
Edge node;

struct Dinic{
	int first[maxnode],next[maxnode*maxnode];
	Edge edges[maxnode*maxnode];
	int d[maxnode],a[maxnode],p[maxnode];
	bool inq[maxnode];
	int n,m;
	
	void init(int a){
		n=a;m=0;
		memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap,int cost){
		next[m]=first[from];
		first[from]=m;
		node.give(from,to,0,cap,cost);
		edges[m++]=node;
		next[m]=first[to];
		first[to]=m;
		node.give(to,from,0,0,-cost);
		edges[m++]=node;
	}
	
	bool BellmanFord(int s,int t,int &flow,int &cost){
		queue<int> q;
		q.push(s);
		a[s]=INF;
		p[s]=0;
		memset(inq,false,sizeof(inq));
		for(int i=0;i<n;i++) d[i]=INF;
		d[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				int v=edges[e].to;
				if(edges[e].cap>edges[e].flow&&d[v]>d[x]+edges[e].cost){
					d[v]=d[x]+edges[e].cost;
					a[v]=min(a[x],edges[e].cap-edges[e].flow);
					p[v]=e;
					if(!inq[v]) inq[v]=true,q.push(v);
				}
			}
		}
		if(d[t]==INF) return false;
		flow+=a[t];
		cost+=a[t]*d[t];
		int u=t;
		while(u!=s){
			edges[p[u]].flow+=a[t];
			edges[p[u]^1].flow-=a[t];
			u=edges[p[u]].from;
		}
		return true;
	}
	
	int Mincost(int s,int t){
		int flow=0,cost=0;
		while(BellmanFord(s,t,flow,cost));
			return cost;
	}
};
Dinic g;

int cost[maxm][maxn];
int m,n;
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&cost[j][i]);
	int S=0,T=m*n+n+1;
	g.init(T+1);
	for(int i=1;i<=n;i++)
		g.add_edge(S,i,1,0);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k=1;k<=n;k++)
			g.add_edge(i,n+(j-1)*n+k,1,(k*cost[j][i]));
	for(int i=n+1;i<=n+m*n;i++)
		g.add_edge(i,T,1,0);
	double ans=(double)g.Mincost(S,T)/(n*1.0);
		printf("%.2f\n",ans);
	return 0;
}
