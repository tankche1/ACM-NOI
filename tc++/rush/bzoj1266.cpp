# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=510;
const int maxm=250000;
const int INF=~0U>>1;
int n,m,ans;
/*struct Edge1{
	int from,to,dist,c;
	Edge1() {}
	Edge1(int from,int to,int dist,int c) :from(from),to(to),dist(dist),c(c) {}
};*/

int first[maxn],u[maxm],next[maxm],v[maxm],dis[maxm],c[maxm],edge;

void add_edge(int from,int to,int dist,int cc){
	next[edge]=first[from];
	u[edge]=from;
	v[edge]=to;
	dis[edge]=dist;
	c[edge]=cc;
	first[from]=edge++;
}

bool inq[maxn];
struct SPFA{
	int d[maxn];
	
	void spfa(int s){
		for(int i=1;i<=n;i++) d[i]=INF;
			d[s]=0;
		queue<int> q;
		q.push(s);
		memset(inq,false,sizeof(inq));
		while(!q.empty()){
			int x=q.front();q.pop();
			inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]>d[x]+dis[e]){
					d[v[e]]=d[x]+dis[e];
					if(!inq[v[e]]){
						inq[v[e]]=true;
						q.push(v[e]);
					}
				}
			}
		}
	}
};
SPFA start,end;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap) :from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	
	int first[maxn],edge,n,next[maxm];
	int cur[maxn],d[maxn];
	int s,t;
	Edge edges[maxm];
	
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
		queue<int> q;
		q.push(s);
		for(int i=1;i<=n;i++)
			d[i]=INF;
		d[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[edges[e].to]>d[x]+1&&edges[e].cap>edges[e].flow){
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
		for(int e=first[x];e!=-1;e=next[e]){
			if(d[edges[e].to]==d[x]+1&&(f=DFS(edges[e].to,min(a,edges[e].cap-edges[e].flow)))>0){
				flow+=f;
				a-=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	
	int maxflow(int S,int T){
		int flow=0;
		s=S;t=T;
		while(BFS()){
			for(int i=1;i<=n;i++) cur[i]=first[i];
				flow+=DFS(s,INF);
		}
		return flow;
	}
};
Dinic g;

int main(){
	scanf("%d%d",&n,&m);
	int from,to,dist,cc;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d%d",&from,&to,&dist,&cc);
		add_edge(from,to,dist,cc);
		add_edge(to,from,dist,cc);
	}
	start.spfa(1);
	end.spfa(n);
	ans=start.d[n];
	printf("%d\n",ans);
	g.init(n+1);
	for(int i=0;i<edge;i++){
		if(start.d[u[i]]+end.d[v[i]]+dis[i]==ans)
			g.add_edge(u[i],v[i],c[i]);
	}
	printf("%d\n",g.maxflow(1,n));
	return 0;
}
