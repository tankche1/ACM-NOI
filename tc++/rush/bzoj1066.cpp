# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxr=22;
const int maxn=maxr*maxr*2;
const int INF=~0U>>1;

struct Edge{
	int from,to,flow,cap;
	
	void give(int fr,int t,int fl,int c){
		from=fr;to=t;flow=fl;cap=c;
	}
};
Edge node;

struct Dinic{
	int n,m,s,t;
	int first[maxn],next[maxn*maxn];
	Edge edges[maxn*maxn];
	int d[maxn],cur[maxn];
	bool vis[maxn];
	
	void init(int a){
		n=a;
		m=0;
		memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap){
		next[m]=first[from];
		first[from]=m;
		node.give(from,to,0,cap);
		edges[m++]=node;
		next[m]=first[to];
		first[to]=m;
		node.give(to,from,0,0);
		edges[m++]=node;
	}
	
	bool BFS(){
		queue<int> q;
		memset(vis,false,sizeof(vis));
		q.push(s);
		for(int i=0;i<n;i++)
			d[i]=INF;
		d[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			vis[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				int v=edges[e].to;
				if(edges[e].cap>edges[e].flow&&d[v]>d[x]+1){
					d[v]=d[x]+1;
					if(!vis[v]) vis[v]=1,q.push(v);
				}
			}
		}
		return d[t]!=INF;
	}
	
	int DFS(int x,int a){
		if(x==t||a==0) return a;
		int flow=0,f;
		for(int &e=cur[x];e!=-1;e=next[e]){
			int v=edges[e].to;
			if(d[v]==d[x]+1&&(f=DFS(v,min(a,edges[e].cap-edges[e].flow)))>0){
				flow+=f;
				a-=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(!a) break;
			}
		}
		return flow;
	}
	
	int Maxflow(int S,int T){
		s=S;t=T;
		int flow=0;
		while(BFS()){
			memcpy(cur,first,sizeof(first));
			flow+=DFS(s,INF);
		}
		return flow;
	}
};
Dinic g;

int r,c,d;
char s[maxr][maxr];
char b[maxr][maxr];
int main(){
	scanf("%d%d%d",&r,&c,&d);
	for(int i=1;i<=r;i++)
		scanf("%s",s[i]+1);
	for(int i=1;i<=r;i++)
		scanf("%s",b[i]+1);
	int S=0,T=r*c*2+1,tot=0;
	g.init(T+1);
	for(int i=1;i<=r;i++)
		for(int j=1;j<=c;j++){
			if(s[i][j]>'0') g.add_edge((i-1)*c*2+(j-1)*2+1,(i-1)*c*2+j*2,s[i][j]-'0');
			if(b[i][j]=='L') g.add_edge(S,(i-1)*c*2+(j-1)*2+1,1),tot++;
			if(i+d>r||i-d<1||j+d>c||j-d<1) g.add_edge((i-1)*c*2+j*2,T,INF);
			for(int x=max(i-d,1);x<=min(r,i+d);x++)
				for(int y=max(j-d,1);y<=min(c,j+d);y++){
					if((i-x)*(i-x)+(y-j)*(y-j)<=d*d)
						g.add_edge((i-1)*c*2+j*2,(x-1)*c*2+(y-1)*2+1,INF);
				}
		}
		printf("%d\n",tot-g.Maxflow(S,T));
	return 0;
}
