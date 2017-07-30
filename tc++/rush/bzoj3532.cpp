# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=710;
const int maxm=maxn*maxn;
int dp[maxn],A[maxn],B[maxn],C[maxn],num[maxn];
vector<int> q;
int n;
int bh[maxn];

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge (int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn<<1],next[maxm];
	int d[maxn<<1],cur[maxn<<1],edge;
	int S,T,n;
	Edge edges[maxm];
	queue<int> Q;
	
	void init(int nn){
		n=nn;edge=0;memset(first,-1,sizeof(first));
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
		d[S]=0;
		Q.push(S);
		while(!Q.empty()){
			int x=Q.front();Q.pop();
			for(int e=first[x];e!=-1;e=next[e])
				if(d[edges[e].to]==INF&&edges[e].cap>edges[e].flow){
					d[edges[e].to]=d[x]+1;
					Q.push(edges[e].to);
				}
		}
		return d[T]!=INF;
	}
	
	int DFS(int x,int a){
		if(x==T||a==0) return a;
		int f,flow=0;
		for(int &e=cur[x];e!=-1;e=next[e]){
			int v=edges[e].to;
			if(d[v]==d[x]+1&&((f=DFS(v,min(a,edges[e].cap-edges[e].flow)))>0)){
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				flow+=f;
				a-=f;
				if(a==0) break;
			}
		}
		return flow;
	}
	
	int Maxflow(int ss,int tt){
		S=ss;T=tt;
		int maxflow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			maxflow+=DFS(S,INF);
		}
		return maxflow;
	}
}dinic;

bool cmp(int a,int b){
	return C[a]<C[b];
}

int main(){
	//freopen("input.txt","r",stdin);
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++) scanf("%d",&A[i]);
		for(int i=1;i<=n;i++) scanf("%d",&B[i]);
		for(int i=1;i<=n;i++) scanf("%d",&C[i]);
		int ans=0;
		for(int i=1;i<=n;i++){
			dp[i]=1;
			for(int j=i-1;j>=1;j--)
				if(A[i]>A[j]) dp[i]=max(dp[i],dp[j]+1);
			ans=max(ans,dp[i]);
		}
		//printf("ans:%d\n",ans);
		int S=0,T=2*n+1;
		dinic.init(T+1);
		for(int i=1;i<=n;i++)
			dinic.add_edge(i,n+i,B[i]),num[i]=dinic.edge-2;
		for(int i=1;i<=n;i++){
			if(dp[i]==1) dinic.add_edge(S,i,INF);
			if(dp[i]==ans) dinic.add_edge(i+n,T,INF);
			for(int j=i+1;j<=n;j++)
				if(dp[j]==dp[i]+1&&A[i]<A[j]) dinic.add_edge(i+n,j,INF);
		}
		int maxflow=dinic.Maxflow(S,T);
		
		for(int i=1;i<=n;i++) bh[i]=i;
		sort(bh+1,bh+n+1,cmp);
		int f;q.clear();
		for(int i=1;i<=n;i++){
			int e=num[bh[i]];
			if(dinic.edges[e].flow==dinic.edges[e].cap){
				int u=dinic.edges[e].from,v=dinic.edges[e].to;
				dinic.edges[e].flow=dinic.edges[e].cap=dinic.edges[e^1].flow=dinic.edges[e^1].cap=0;
				int ff=dinic.Maxflow(u,S);int fff=dinic.Maxflow(T,v);
				if((f=dinic.Maxflow(S,T))==0) q.push_back(bh[i]);
				else dinic.edges[e].cap=B[bh[i]],dinic.Maxflow(S,T);
			}
		}
		sort(q.begin(),q.end());
		printf("%d ",maxflow);
		printf("%d\n%d",q.size(),q[0]);
		for(int i=1;i<q.size();i++)
			printf(" %d",q[i]);
		puts("");
	}
	return 0;
}
