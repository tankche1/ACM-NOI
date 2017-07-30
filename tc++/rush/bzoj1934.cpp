# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=310;
int n,m;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int n,m;
	int S,T;
	vector<int> G[maxn];
	Edge edges[maxn*maxn*2];
	int dist[maxn],cur[maxn];
	queue<int> Q;
	
	void init(int nn){
		n=nn;
		for(int i=0;i<n;i++)
			G[i].clear();
		m=0;
	}
	
	void add_edge(int from,int to,int cap){
		edges[m]=Edge(from,to,0,cap);
		G[from].push_back(m++);
		edges[m]=Edge(to,from,0,0);
		G[to].push_back(m++);
	}
	
	bool BFS(){
		for(int i=0;i<n;i++) dist[i]=INF;
		dist[S]=0;
		Q.push(S);
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int e=0;e<G[x].size();e++){
				if(dist[edges[G[x][e]].to]>dist[x]+1&&edges[G[x][e]].flow<edges[G[x][e]].cap)
					dist[edges[G[x][e]].to]=dist[x]+1,Q.push(edges[G[x][e]].to);
			}
		}
		return dist[T]!=INF;
	}
	
	int DFS(int x,int a){
		if(x==T||a==0) return a;
		int f,flow=0;
		for(int &e=cur[x];e<G[x].size();e++){
			int v=edges[G[x][e]].to;
			if((dist[v]==dist[x]+1)&&(f=DFS(v,min(a,edges[G[x][e]].cap-edges[G[x][e]].flow)))>0){
				edges[G[x][e]].flow+=f;
				edges[G[x][e]^1].flow-=f;
				flow+=f;
				a-=f;
				if(!a) break;
			}
		}
		return flow;
	}
	
	int maxflow(int s,int t){
		S=s;T=t;
		int flow=0;
		while(BFS()){
			memset(cur,0,sizeof(cur));
			flow+=DFS(S,INF);
		}
		return flow;
	}
	
};
Dinic dinic;

int main(){
	int c,a,b;
	scanf("%d%d",&n,&m);
	int S=0,T=n+1;
	dinic.init(T+1);
	for(int i=1;i<=n;i++){
		scanf("%d",&c);
		if(!c) dinic.add_edge(S,i,1);
		else dinic.add_edge(i,T,1);
	}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		dinic.add_edge(a,b,1);
		dinic.add_edge(b,a,1);
	}
	printf("%d\n",dinic.maxflow(S,T));
	return 0;
}
