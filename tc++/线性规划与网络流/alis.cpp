#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int INF=(~0U>>1)-1;
const int maxn=900;
const int maxm=1000*1000;
int n,A[maxn];

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
			flow+=DFS(S,INF);
			//printf("%d\n",flow);
		}
		return flow;
	}
	
}dinic;

int dp[maxn];
int main(){
	freopen("alis.in","r",stdin);
	freopen("alis.out","w",stdout);
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	dp[0]=0;A[0]=-INF;
	int ans=0;
	for(int i=1;i<=n;i++){
		dp[i]=1;
		for(int j=i-1;j>=0;j--)
			if(A[i]>A[j]) dp[i]=max(dp[i],dp[j]+1);
		ans=max(ans,dp[i]);
	}
	int S=0,T=2*n+1;
	dinic.init(T+1);
	for(int i=1;i<=n;i++){
		if(dp[i]==1)
			dinic.add_edge(S,i,INF);
		if(dp[i]==ans)
			dinic.add_edge(n+i,T,INF);
		dinic.add_edge(i,n+i,1);
		for(int j=i+1;j<=n;j++)
			if(dp[j]==dp[i]+1&&A[j]>A[i])
				dinic.add_edge(n+i,j,1);
	}int g=0;
	printf("%d\n%d\n",ans,g=dinic.maxflow(S,T));
	dinic.add_edge(1,n+1,INF);dinic.add_edge(n,2*n,INF);
	printf("%d\n",g,g+dinic.maxflow(S,T));
	return 0;
}
