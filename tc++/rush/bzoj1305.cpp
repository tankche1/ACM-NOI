# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=110;
const int INF=~0U>>1;
bool g[maxn>>1][maxn>>1];
int n,k;

struct Edge{
	int from,to,flow,cap;
	Edge(int from,int to,int flow,int cap) :from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int n,m,s,t;
	vector<Edge> edges;
	vector<int> G[maxn<<1];
	int d[maxn<<1];
	int cur[maxn<<1];
	
	void init(int nn){
		n=nn;
		edges.clear();
		for(int i=0;i<n;i++) G[i].clear();
	}
	
	void add_edge(int from,int to,int cap){
		Edge A(from,to,0,cap);
		edges.push_back(A);G[from].push_back(edges.size()-1);
		A=Edge(to,from,0,0);
		edges.push_back(A);G[to].push_back(edges.size()-1);
	}
	
	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
			d[s]=0;
		queue<int> q;q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=0;e<G[x].size();e++){
				int v=edges[G[x][e]].to;
				if(d[v]>d[x]+1&&edges[G[x][e]].cap>edges[G[x][e]].flow){
					d[v]=d[x]+1;q.push(v);
				}
			}
		}
		return d[t]!=INF;
	}
	
	int DFS(int x,int a){
		if(x==t||a==0) return a;
		int flow=0;
		for(int &e=cur[x];e<G[x].size();e++){
			int f;
			if(d[edges[G[x][e]].to]==d[x]+1&&((f=DFS(edges[G[x][e]].to,min(a,edges[G[x][e]].cap-edges[G[x][e]].flow)))>0)){
				a-=f;flow+=f;
				edges[G[x][e]].flow+=f;
				edges[G[x][e]^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	
	int Maxflow(int S,int T){
		s=S;t=T;
		int flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=0;
			flow+=DFS(s,INF);
		}
		return flow;
	}
};
Dinic G;

int main(){
	char ch;
	scanf("%d %d\n",&n,&k);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			scanf("%c",&ch);g[i][j]=ch=='Y'?1:0;//printf("%d %d\n",i,j);
		}
		
		if(i!=n) scanf("\n");
	}
	int L=0,R=n;
	int S=0,T=4*n+1;
	G.init(T+1);
	for(int i=1;i<=n;i++)
		G.add_edge(S,i,1);
	for(int i=1;i<=n;i++)
		G.add_edge(2*n+i,T,1);
	for(int i=1;i<=n;i++){
		G.add_edge(i,n+i,k);
	//	G.add_edge(2*n+i,T,INF);
		G.add_edge(3*n+i,2*n+i,k);
		for(int j=1;j<=n;j++)
			if(g[i][j]) G.add_edge(i,2*n+j,1);
			else G.add_edge(n+i,3*n+j,1);
	}
		
	while(L<=R){
		int M=(L+R)>>1;
		for(int e=0,i=0;i<2*n;i++,e+=2)
			G.edges[e].cap=M;
		//printf("M:%d\n",M);
		//for(int e=0;e<G.edges.size();e+=2)
		//	printf("from:%d to:%d cap:%d\n",G.edges[e].from,G.edges[e].to,G.edges[e].cap);
		for(int e=0;e<G.edges.size();e++) G.edges[e].flow=0;
		if(G.Maxflow(S,T)==n*M) L=M+1;
			else R=M-1;
	}
	printf("%d\n",L-1);
	return 0;
}
