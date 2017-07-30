# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=105;
const int INF=~0U>>1;
int n,F,D;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn*4],next[maxn*maxn*6+2*maxn],edge;
	Edge edges[maxn*maxn*6+2*maxn];
	int n,s,t;
	int cur[maxn*4],d[maxn*4];
	
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

int main(){
	scanf("%d%d%d",&n,&F,&D);
	int S=0,T=n+F+D+n+1;
	g.init(T+1);
	for(int i=1;i<=n;i++){
		int len1,len2,x;
		scanf("%d%d",&len1,&len2);
		for(int j=1;j<=len1;j++) {scanf("%d",&x);g.add_edge(x,F+i,1);}
		for(int j=1;j<=len2;j++) {scanf("%d",&x);g.add_edge(F+n+i,F+n+n+x,1);}
		g.add_edge(F+i,F+n+i,1);
	}
	for(int i=1;i<=F;i++)
		g.add_edge(S,i,1);
	for(int i=1;i<=D;i++)
		g.add_edge(F+n+n+i,T,1);
	printf("%d\n",g.maxflow(S,T));
	return 0;
}
