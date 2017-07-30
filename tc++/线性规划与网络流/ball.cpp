#include<stdio.h>
#include<string.h>
# include<queue>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxn=4010;
const int maxm=200010;
const int INF=~0U>>1;
int match[maxn];
bool vis[maxn];
int ans;

struct Dinic{
	struct Edge{
		int from,to,cap,flow;
		Edge(int from=0,int to=0,int cap=0,int flow=0):from(from),to(to),cap(cap),flow(flow) {}
	};
	Edge edges[maxm];
	int first[maxn],cur[maxn],d[maxn],next[maxm],n;
	int edge;
	
	int S,T;
	
	void init(int nn){
		n=nn;memset(first,-1,sizeof(first));edge=0;
	}

	void add_edge(int from,int to,int cap){
		next[edge]=first[from];
		edges[edge]=Edge(from,to,cap,0);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0);
		first[to]=edge++;
	}
	
	bool BFS(){
		for(int i=0;i<n;i++)
			d[i]=INF;
		d[S]=0;queue<int> Q;Q.push(S);
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[edges[e].to]>d[x]+1&&edges[e].flow<edges[e].cap)
					d[edges[e].to]=d[x]+1,Q.push(edges[e].to);
			}
		}
		return d[T]!=INF;
	}
	
	int DFS(int x,int a){
		if(x==T||a==0) return a;
		int f,flow=0;
		for(int &e=cur[x];e!=-1;e=next[e]){
			int v=edges[e].to;
			if(d[v]==d[x]+1&&(f=DFS(v,min(a,edges[e].cap-edges[e].flow)))>0){
				a-=f;
				flow+=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(a==0) return flow;
			}
		}
		return flow;
	}
	
	int maxflow(int s,int t){
		S=s;T=t;
		int flow=0;
		while(BFS()){
			memcpy(cur,first,sizeof(first));
			//for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(S,INF);
		}
		return flow;
	}
	
}dinic;
int n;

int main(){
	scanf("%d",&n);
	int S=0,T=4000;
	dinic.init(T+1);
	int flow=0;
	for(int i=1;i<=1999;i++){
		dinic.add_edge(S,i,1);
		dinic.add_edge(2000+i,T,1);
		for(int j=1;j<i;j++){
			int d=sqrt(i+j);
			if(d*d==i+j) dinic.add_edge(j,2000+i,1);
		}
		flow+=dinic.maxflow(S,T);
		if(i-flow>n) {ans=i-1;printf("%d\n",i-1);break;}
	}
	dinic.init(T+1);
	for(int i=1;i<=ans;i++){
		dinic.add_edge(S,i,1);
		dinic.add_edge(2000+i,T,1);
		for(int j=1;j<i;j++){
			int d=sqrt(i+j);
			if(d*d==i+j) dinic.add_edge(j,2000+i,1);
		}
	}
	dinic.maxflow(S,T);
	memset(match,-1,sizeof(match));
	for(int i=1;i<=ans;i++){
		for(int e=dinic.first[i];e!=-1;e=dinic.next[e])
			if(dinic.edges[e].flow==1)
				match[i]=dinic.edges[e].to-2000;
	}
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=ans;i++){
		if(vis[i]) continue;
		int j=i;
		while(j!=-1){
			printf("%d ",j);vis[j]=1;j=match[j];
		}puts("");
	}
	return 0;
}
