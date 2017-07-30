# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010,maxm=10010;
const int INF=~0U>>1;
int n,m;
int a[maxn];

struct Edge{
	int from,to,flow,cap,cost;
	Edge() {}
	Edge(int from,int to,int flow,int cap,int cost):from(from),to(to),flow(flow),cap(cap),cost(cost) {}
};

struct MCMF{
	int first[maxn],next[maxm<<2],edge,n;
	int S,T,ans;
	int d[maxn];
	bool vis[maxn],inq[maxn];
	Edge edges[maxm<<2];
	
	void init(int nn){
		n=nn;edge=0;memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap,int cost){
		//printf("from:%d to:%d cap:%d\n",from,to,cap);
		next[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap,cost);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0,-cost);
		first[to]=edge++;
	}
	
	void SPFA(){
		queue<int> Q;
		for(int i=0;i<n;i++) d[i]=-INF;memset(inq,false,sizeof(inq));
		d[T]=0;Q.push(T);
		while(!Q.empty()){
			int x=Q.front();Q.pop();inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				int v=edges[e].to;
				if(edges[e^1].flow<edges[e^1].cap&&d[v]<d[x]+edges[e^1].cost){
					d[v]=d[x]+edges[e^1].cost;
					if(!inq[v]) {inq[v]=true;Q.push(v);}
				}
			}
		}
	}
	
	int dfs(int x,int a){
		if(a==0) return 0;
		if(x==T){
			ans+=d[S]*a;
			return a;
		}
		int flow=0,f;vis[x]=1;
		for(int e=first[x];e!=-1;e=next[e]){
			if(!vis[edges[e].to]&&d[x]==d[edges[e].to]+edges[e].cost&&((f=dfs(edges[e].to,min(edges[e].cap-edges[e].flow,a)))>0)){
				edges[e].flow+=f;edges[e^1].flow-=f;
				a-=f;
				flow+=f;
				if(a==0) return flow;
			}
		}
		return flow;
	}
	
	bool adjust(){
		int tmp=-INF;
		for(int i=0;i<n;i++)
			if(vis[i]){
				for(int e=first[i];e!=-1;e=next[e])
					if(!vis[edges[e].to]&&edges[e].flow<edges[e].cap)
						tmp=max(tmp,d[edges[e].to]+edges[e].cost-d[i]);
			}
		if(tmp==-INF) return false;
		for(int i=0;i<n;i++)
			if(vis[i]) d[i]+=tmp;
		return true;
	}
	
	int maxflow(int s,int t){
		S=s;T=t;SPFA();ans=0;//puts("spfa done");
		do{
			memset(vis,0,sizeof(vis));
			while(dfs(S,INF));
		}while(adjust());
		return ans;
	}
}zkw;

int main(){
	int x,y,c;
	scanf("%d%d",&n,&m);
	int S=0,T=n+2;
	zkw.init(T+1);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);
	}
	for(int i=1;i<=n+1;i++)
		if(a[i-1]-a[i]>0) zkw.add_edge(S,i,a[i-1]-a[i],0);
		else zkw.add_edge(i,T,a[i]-a[i-1],0);
	for(int i=1;i<=n;i++)
		zkw.add_edge(i+1,i,INF,0);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&x,&y,&c);
		zkw.add_edge(y+1,x,INF,c);
	}
	printf("%d\n",zkw.maxflow(S,T));
	return 0;
}

/*
5 3
1 5 6 3 4
2 3 1
1 5 4
3 5 2
*/
