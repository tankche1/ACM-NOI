# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
# define in(x) x
# define out(x) p+x
using namespace std;
const int maxn=3010*2;
const int maxm=(20000*2+maxn)<<1;
const int INF=~0U>>1;
int p,n,c;
bool nocut[maxn];

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

int read(){
	char t;
	while((t=getchar())&&(t<'0'||t>'9')) ;
		int res=t-'0';
	while((t=getchar())&&(t>='0'&&t<='9')) res=res*10+t-'0';
	return res;
}

int main(){
	int a,b;
	p=read();c=read();n=read();
	int S=out(1),T=2*p+1;
	g.init(T+1);
	for(int i=1;i<=c;i++){
		a=read();b=read();
		g.add_edge(out(a),in(b),INF);
		g.add_edge(out(b),in(a),INF);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a),nocut[a]=1,g.add_edge(in(a),T,INF);
	for(int i=2;i<=p;i++)
		if(!nocut[i])
		g.add_edge(in(i),out(i),1);
	printf("%d\n",g.maxflow(S,T));
	return 0;
}
