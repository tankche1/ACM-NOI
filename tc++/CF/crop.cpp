# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=maxn*maxn*4;
const int INF=~0U>>1;
int n,m;
int a[maxn],b[maxn];

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn*3],next[maxm],edge;
	Edge edges[maxm];
	int n,s,t;
	int cur[maxn*3],d[maxn*3];
	
	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap){
		//printf("from:%d to:%d cap:%d\n",from,to,cap);
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
}dinic;

int main(){
	int x,y;
	scanf("%d",&n);
	int tot=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	scanf("%d",&m);
	int S=0,T=n+2*m+1;
	dinic.init(T+1);
	for(int i=1;i<=n;i++)
		dinic.add_edge(S,i,a[i]),tot+=a[i],dinic.add_edge(i,T,b[i]),tot+=b[i];
//	int node=n;
	for(int i=1;i<=m;i++){
		int num;scanf("%d%d%d",&num,&x,&y);tot+=x+y;
		dinic.add_edge(S,n+i,x);dinic.add_edge(n+m+i,T,y);
		//dinic.add_edge(S,++node,x);dinic.add_edge(++node,T,y);
		while(num--){
			scanf("%d",&x);
			dinic.add_edge(n+i,x,INF);
			dinic.add_edge(x,n+m+i,INF);
		}
	}
	printf("%d\n",tot-dinic.maxflow(S,T));
	return 0;
}
