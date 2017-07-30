# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1010;
const int maxm=400010;
const int INF=~0U>>1;
const LL inf=(LL)1<<61;

struct Edge{
	int from,to;LL flow,cap;
	Edge(){}
	Edge(int from,int to,LL flow,LL cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int S,T,edge,n;
	Edge edges[maxm];
	int first[maxn],next[maxm];
	int cur[maxn],d[maxn];
	
	void init(int nn){
		n=nn+1;
		memset(first,-1,sizeof(first));
		edge=0;
	}
	
	void add_edge(int from,int to,LL cap){
		next[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0);
		first[to]=edge++;
	}

	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
			d[S]=0;
		queue<int> q;q.push(S);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
				if(edges[e].cap>edges[e].flow&&d[edges[e].to]>d[x]+1){
					d[edges[e].to]=d[x]+1;
					q.push(edges[e].to);
				}
			}
		}
		return d[T]!=INF;
	}
	
	LL DFS(int x,LL a){
		if(x==T||a==0) return a;
		LL flow=0,f;
		for(int &e=cur[x];e!=-1;e=next[e]){
			if(d[edges[e].to]==d[x]+1&&(f=DFS(edges[e].to,min(edges[e].cap-edges[e].flow,a)))>0){
				flow+=f;a-=f;
				edges[e].flow+=f;edges[e^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	
	LL maxflow(int ss,int tt){
		S=ss;T=tt;
		LL flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(S,inf);
		}
		return flow;
	}
	
}dinic;

int n,m;
int main()
{
	int S,T;
	int x,y,d;
	LL c;
	int tcase;
	int t=0;
	scanf("%d",&tcase);
	while(tcase--){
	printf("Case %d: ",++t);
	scanf("%d%d",&n,&m);
	S=1,T=n;
	dinic.init(T+1);
	for(int i=1;i<=m;i++){
		scanf("%d%d%I64d%d",&x,&y,&c,&d);x++;y++;c=c*(m+10)+1;
		dinic.add_edge(x,y,c);
		if(d==1) dinic.add_edge(y,x,c);
	}int ans=0;
	ans=(dinic.maxflow(S,T))%(m+10);
	/*for(int i=0;i<dinic.edge;i+=2){
		if(dinic.edges[i].flow==dinic.edges[i].cap) ans++;
	}*/
	printf("%d\n",ans);
}
	return 0;
}
