#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=25;
const int maxnn=1300;
const int maxm=maxnn*16;
int n,m;
char start[maxn][maxn],end[maxn][maxn];
int c[maxn][maxn];

inline int pos(int x,int y){return (x-1)*m+y;}

int dx[8]={-1,-1,-1,0,0,1,1,1},dy[8]={-1,0,1,-1,1,-1,0,1};

void init(){
	char t;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			while((t=getchar())&&t!='0'&&t!='1');start[i][j]=t;
		}
	}
	
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			while((t=getchar())&&t!='0'&&t!='1');end[i][j]=t;
		}
	}
	for(int i=1;i<=n;i++) for(int j=1;j<=m;j++){ while((t=getchar())&&(t<'0'||t>'9'));c[i][j]=t-'0';}
}

struct Edge{
	int from,to,flow,cap,cost;
	Edge() {}
	Edge(int from,int to,int flow,int cap,int cost):from(from),to(to),flow(flow),cap(cap),cost(cost) {}
};

struct zkwMCMF{
	int n,S,T,ans,edge,mflow;
	int first[maxnn],next[maxm];
	Edge edges[maxm];
	int d[maxnn];
	bool vis[maxnn],inq[maxnn];
	
	void Init(int nn){
		n=nn;edge=0;memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap,int cost){
		next[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap,cost);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0,-cost);
		first[to]=edge++;
	}
	
	void SPFA(){
		queue<int> Q;
		for(int i=0;i<n;i++) d[i]=INF;memset(inq,false,sizeof(inq));
		d[T]=0;Q.push(T);
		while(!Q.empty()){
			int x=Q.front();Q.pop();inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				int v=edges[e].to;
				if(edges[e^1].flow<edges[e^1].cap&&d[v]>d[x]+edges[e^1].cost){
					d[v]=d[x]+edges[e^1].cost;
					if(!inq[v]) {inq[v]=true;Q.push(v);}
				}
			}
		}
	}
	
	int DFS(int x,int a){
		if(a==0) return a;
		if(x==T){
			ans+=d[S]*a;mflow+=a;return a;
		}
		int flow=0,f;vis[x]=1;
		for(int e=first[x];e!=-1;e=next[e]){
			if(!vis[edges[e].to]&&d[edges[e].to]+edges[e].cost==d[x]&&((f=DFS(edges[e].to,min(a,edges[e].cap-edges[e].flow)))>0)){
				flow+=f;
				a-=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(a==0) return flow;
			}
		}
		return flow;
	}
	
	bool adjust(){
		int tmp=INF;
		for(int i=0;i<n;i++)
			if(vis[i]){
				for(int e=first[i];e!=-1;e=next[e])
					if(!vis[edges[e].to]&&edges[e].flow<edges[e].cap)
						tmp=min(tmp,d[edges[e].to]+edges[e].cost-d[i]);
			}
		if(tmp==INF) return false;
		for(int i=0;i<n;i++)
			if(vis[i]) d[i]+=tmp;
		return true;
	}
	
	int maxflow(int SS,int TT){
		S=SS;T=TT;
		SPFA();
		ans=0;mflow=0;
		do{
			memset(vis,0,sizeof(vis));
			while(DFS(S,INF));
			}while(adjust());
		return ans;
	}
};
zkwMCMF g;

int main(){
	init();
	int S=0,T=n*m*3+1;
	g.Init(T+1);
	int tot=0;for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) tot+=start[i][j]-'0'-(end[i][j]-'0');if(tot!=0) {puts("-1");return 0;}
	//for(int i=1;i<=n;i++) for(int j=1;j<=m;j++) tot+=start[i][j]-'0';
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(start[i][j]=='1'&&end[i][j]=='1'){
				g.add_edge((pos(i,j)-1)*3+1,(pos(i,j)-1)*3+2,c[i][j]/2,0);
				g.add_edge((pos(i,j)-1)*3+2,(pos(i,j)-1)*3+3,c[i][j]/2,0);
			}
			else if(start[i][j]=='1'){
				tot+=start[i][j]-'0';
				g.add_edge(S,(pos(i,j)-1)*3+2,1,0);
				g.add_edge((pos(i,j)-1)*3+1,(pos(i,j)-1)*3+2,c[i][j]/2,0);
				g.add_edge((pos(i,j)-1)*3+2,(pos(i,j)-1)*3+3,(c[i][j]+1)/2,0);
			}
			else if(end[i][j]=='1'){
				g.add_edge((pos(i,j)-1)*3+2,T,1,0);
				g.add_edge((pos(i,j)-1)*3+1,(pos(i,j)-1)*3+2,(c[i][j]+1)/2,0);
				g.add_edge((pos(i,j)-1)*3+2,(pos(i,j)-1)*3+3,(c[i][j])/2,0);
			}
			else{
				g.add_edge((pos(i,j)-1)*3+1,(pos(i,j)-1)*3+2,c[i][j]/2,0),
				g.add_edge((pos(i,j)-1)*3+2,(pos(i,j)-1)*3+3,(c[i][j])/2,0);
			}
			for(int d=0;d<8;d++){
				int x=i+dx[d],y=j+dy[d];
				if(x>=1&&x<=n&&y>=1&&y<=m){
				//	if(start[x][y]==1&&
					g.add_edge((pos(i,j)-1)*3+3,(pos(x,y)-1)*3+1,INF,1);
				}
			}
		}
	g.maxflow(S,T);
	if(g.mflow!=tot) puts("-1");
		else printf("%d\n",g.ans);
	return 0;
}
/*
5 3
110
011
111
010
000

110
011
101
110
000

431
123
014
640
232
*/
