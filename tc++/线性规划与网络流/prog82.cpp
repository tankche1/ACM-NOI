#include<stdio.h>
#include<string.h>
# include<vector>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=100;
const int maxm=30*40*2+100;
const int INF=~0U>>1;
int m,n;
bool ok;
int val[50],cost[50];

inline int getint(){
	char t;
	while((t=getchar())&&(t<'0'||t>'9'));//if(t=='\n') return -1;
	int res=t-'0';
	while((t=getchar())&&(t>='0'&&t<='9')) res=res*10+t-'0';
		if(t=='\n') ok=false;
	return res;
}

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
int go[50];

int main(){
	//freopen("shut.in","r",stdin);
	//freopen("shut.out","w",stdout);
	char s[maxn];
	scanf("%d %d\n",&m,&n);
	int S=0,T=m+n+1;
	dinic.init(T+1);
	int ans=0;
	for(int i=1;i<=m;i++){
		scanf("%d",&val[i]);ans+=val[i];
		dinic.add_edge(S,i,val[i]);
		gets(s);
		for(int j=0;j<strlen(s);j++){
			if(s[j]>='0'&&s[j]<='9'){
				int res=s[j]-'0';
				while(s[j+1]>='0'&&s[j+1]<='9')
					res=res*10+s[++j]-'0';
				dinic.add_edge(i,m+res,INF);
				//printf("i:%d res:%d\n",i,res);
			}
		}
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&cost[i]),dinic.add_edge(m+i,T,cost[i]);//go[i]=dinic.edge-2;
	ans-=dinic.maxflow(S,T);
	for(int i=1;i<=m;i++)
		if(dinic.d[i]!=INF) printf("%d ",i);puts("");
	for(int i=1;i<=n;i++)
		if(dinic.d[m+i]!=INF) printf("%d ",i);puts("");
	printf("%d\n",ans);
	return 0;
}
/*
2 3 
10 1 2 
25 2 3 
5 6 7
*/