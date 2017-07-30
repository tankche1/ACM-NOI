# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=5010;
const int maxm=50010;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn+maxm],next[maxn*2+maxm*6],edge;
	Edge edges[maxn*2+maxm*6];
	int n,s,t;
	int cur[maxn+maxm],d[maxn+maxm];
	
	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap){
		next[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0);
		first[to]=edge++;
	}
	
	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
			d[s]=0;
		queue<int> q;q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
				if(edges[e].cap>edges[e].flow&&d[edges[e].to]>d[x]+1){
					d[edges[e].to]=d[x]+1;
					q.push(edges[e].to);
				}
			}
		}
		return d[t]!=INF;
	}
	
	int DFS(int x,int a){
		if(x==t||a==0) return a;
			int flow=0,f;
		for(int &e=cur[x];e!=-1;e=next[e]){
			if(d[edges[e].to]==d[x]+1&&(f=DFS(edges[e].to,min(edges[e].cap-edges[e].flow,a)))>0){
				flow+=f;
				a-=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	
	int maxflow(int ss,int tt){
		s=ss;t=tt;
		int flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
};
Dinic g;

int n,m;
int main(){
	int a,b,c,x;
	scanf("%d%d",&n,&m);
	int S=0,T=n+m+1;
	g.init(T+1);
	for(int i=1;i<=n;i++){
		scanf("%d",&x);g.add_edge(i,T,x);
	}
	int sum=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		g.add_edge(S,n+i,c);
		g.add_edge(n+i,a,INF);
		g.add_edge(n+i,b,INF);
		sum+=c;
	}
	printf("%d\n",sum-g.maxflow(S,T));
	return 0;
}
