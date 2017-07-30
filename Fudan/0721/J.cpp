/*
拆点 m工人变成m*n个点 表示他修的倒数第i辆车 连车 费用为i*cost
*/
# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=30*30*2;
const int maxnode=80;
const int INF=~0U>>1;

struct Edge{
	int from,to,flow,cap,cost;
	Edge() {}
	Edge(int from,int to,int flow,int cap,int cost):from(from),to(to),flow(flow),cap(cap),cost(cost) {}
};
Edge node;

struct Dinic{
	int first[maxnode],next[maxm];
	Edge edges[maxm];
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
		edges[m++]=Edge(from,to,0,cap,cost);
		next[m]=first[to];
		first[to]=m;
		edges[m++]=Edge(to,from,0,0,-cost);
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

int c[27][27];
int n,k,m;
char s[maxn],stu[maxn];
int main(){
	int tcase;
	char t;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;i++){
			while((t=getchar())&&(t<'A'||t>'Z'));
			s[i]=t;
		}
		int S=0,T=26+26+1;
		for(int j=1;j<=m;j++){
			g.init(T+1);
			for(int i=0;i<n;i++){
				while((t=getchar())&&(t<'A'||t>'Z'));
				stu[i]=t;
			}
			for(int i=1;i<=26;i++)
				g.add_edge(S,i,1,0),g.add_edge(26+i,T,1,0);
			memset(c,0,sizeof(c));
			for(int i=0;i<n;i++)
				c[stu[i]-'A'+1][s[i]-'A'+1]++;
			for(int i=1;i<=26;i++)
				for(int j=1;j<=26;j++)
					g.add_edge(i,26+j,1,-c[i][j]);
			int ans=-g.Mincost(S,T);
			double output=ans/(n*1.0);
			printf("%.4lf\n",output);
		}
	}
	return 0;
}
