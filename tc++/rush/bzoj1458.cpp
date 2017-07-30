#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=110;
int n,m,k,g[maxn][maxn];
int row[maxn],line[maxn];
const int INF=~0U>>1;
const int maxm=maxn*maxn*2;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn<<1],next[maxm],edge;
	Edge edges[maxm];
	int n,s,t;
	int cur[maxn<<1],d[maxn<<1];
	
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
}dinic;

int main(){
	int a,b;
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			g[i][j]=1;
	for(int i=1;i<=n;i++)
		scanf("%d",&row[i]);
	for(int i=1;i<=m;i++)
		scanf("%d",&line[i]);
	for(int i=1;i<=k;i++){
		scanf("%d%d",&a,&b);
		g[a][b]=0;
	}
	int S=0,T=n+m+1,sum=0;bool ok=1;
	dinic.init(T+1);
	for(int i=1;i<=n;i++){
		int can=0;
		for(int j=1;j<=m;j++)
			can+=g[i][j];
		//printf("can:%d\n",can);
		if(can<row[i]) ok=false;
		else dinic.add_edge(S,i,can-row[i]);
		sum+=can;
	}
	for(int i=1;i<=m;i++){
			int can=0;
		for(int j=1;j<=n;j++)
			can+=g[j][i];
		if(can<line[i]) ok=false;
		else dinic.add_edge(n+i,T,can-line[i]);
	}
	//printf("sum:%d\n",sum);
	if(!ok) {puts("JIONG!");return 0;}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(g[i][j]) dinic.add_edge(i,n+j,1);
	printf("%d\n",sum-dinic.maxflow(S,T));
	return 0;
}
