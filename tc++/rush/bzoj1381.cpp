#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=205;
const int INF=~0U>>1;
const int maxm=maxn*maxn*20;
int no[maxn][maxn];
int n,m;
inline int pos(int x,int y){
	return (x-1)*n+y;
}

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn*maxn],next[maxm],edge;
	Edge edges[maxm];
	int n,s,t;
	int cur[maxn*maxn],d[maxn*maxn];
	
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
	memset(no,0,sizeof(no));
	scanf("%d%d",&n,&m);
	int ans=n*n-m;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		no[a][b]=1;
	}
	int S=0,T=n*n+1;
	dinic.init(T+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(no[i][j]) continue;
			if((i+j)&1){
				dinic.add_edge(S,pos(i,j),1);
				for(int x=-2;x<=2;x++)
					for(int y=-2;y<=2;y++)
						if(abs(x)+abs(y)==3){
							if(i+x>0&&i+x<=n&&j+y>0&&j+y<=n)
								dinic.add_edge(pos(i,j),pos(i+x,y+j),INF);
						}
			}
			else
				dinic.add_edge(pos(i,j),T,1);
		}
	ans=ans-dinic.maxflow(S,T);
		printf("%d\n",ans);
	return 0;
}
