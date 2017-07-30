#include<stdio.h>
#include<string.h>
# include<stack>
# include<vector>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=610;
const int maxm=maxn*maxn;
const int INF=~0U>>1;
vector<int> G[maxn];
bool noused[maxn];
int n,m;
int score[maxn];
inline int pos(int x,int y){return x*m+y;}

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
		//printf("from:%d to:%d cap:%d\n",from,to,cap);
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

int first[maxn],next[maxm],v[maxm],edge;

void add_edge(int a,int b){
	//printf("a:%d b:%d\n",a,b);
	G[b].push_back(a);
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

int dfn[maxn],low[maxn],dfs_clock;
//bool instack[maxn];
bool col[maxn];
stack<int> S;

void tarjan(int u){
	//printf("u:%d\n",u);
	dfn[u]=low[u]=++dfs_clock;
	S.push(u);//instack[u]=true;
	for(int e=first[u];e!=-1;e=next[e]){
	//	printf("u:u:%d e:%d v[e]:%d\n",u,e,v[e]);
	//	if(u==6) {printf("%d\n",v[e]);int dd;scanf("%d",&dd);}
		if(!dfn[v[e]])
			tarjan(v[e]),low[u]=min(low[u],low[v[e]]);
		else if(!col[v[e]])
			low[u]=min(low[u],dfn[v[e]]);
	}
	if(low[u]==dfn[u]){
		int x,cnt=0;
		//printf("start:");
		do{
			cnt++;x=S.top();S.pop();col[x]=1;noused[x]=1;//printf("%d ",x);
		}while(x!=u);//puts("");
		if(cnt==1) noused[u]=false;
	}
	return;
}

queue<int> Q;
int main(){
	int x,y,w;
	int ans=0;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++){
			scanf("%d",&score[pos(i,j)]);
			if(score[pos(i,j)]>0) ans+=score[pos(i,j)];
			scanf("%d",&w);
			while(w--){
				scanf("%d%d",&x,&y);add_edge(pos(x,y),pos(i,j));
			}
			if(j!=m-1) add_edge(pos(i,j),pos(i,j+1));
		}
	
	memset(dfn,0,sizeof(dfn));dfs_clock=0;memset(noused,false,sizeof(noused));memset(col,false,sizeof(col));
	for(int i=0;i<m*n;i++)
		if(!dfn[i]) tarjan(i);
//	for(int i=0;i<m*n;i++)
//		if(noused[i]) printf("%d\n",i);
	int S=n*m,T=n*m+1;
		dinic.init(T+1);
	for(int i=0;i<n*m;i++)
		if(noused[i]) Q.push(i);
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		for(int e=0;e<G[x].size();e++){
			int v=G[x][e];
			if(!noused[v]){
				noused[v]=1;Q.push(v);
			}
		}
	}
	for(int i=0;i<m*n;i++){
		if(noused[i]) {ans-=score[i]>0?score[i]:0;continue;}
		if(score[i]>0) dinic.add_edge(S,i,score[i]);
		else if(score[i]<0) dinic.add_edge(i,T,-score[i]);
		for(int e=first[i];e!=-1;e=next[e])
			if(!noused[v[e]])
				dinic.add_edge(i,v[e],INF);
	}
	ans-=dinic.maxflow(S,T);
	printf("%d\n",ans);
	return 0;
}
