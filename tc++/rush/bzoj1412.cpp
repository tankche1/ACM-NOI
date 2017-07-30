# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
# define pos(i,j) (i-1)*m+j
using namespace std;
const int maxn=105*105;
const int maxm=maxn*10;
const int INF=~0U>>1;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn],next[maxm],edge;
	Edge edges[maxm];
	int n,s,t;
	int cur[maxn],d[maxn];
	
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
	int a;
	scanf("%d%d",&n,&m);
	int S=0,T=n*m+1;g.init(T+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			scanf("%d",&a);
			if(a==1) 
				g.add_edge(S,pos(i,j),INF);
			else if(a==2) g.add_edge(pos(i,j),T,INF);
			if(i>1) g.add_edge(pos(i,j),pos(i-1,j),1);
			if(i<n) g.add_edge(pos(i,j),pos(i+1,j),1);
			if(j>1) g.add_edge(pos(i,j),pos(i,j-1),1);
			if(j<m) g.add_edge(pos(i,j),pos(i,j+1),1);
		}
		printf("%d\n",g.maxflow(S,T));
	return 0;
}
