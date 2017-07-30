# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
# define pos(x,y) (x-1)*m+y
using namespace std;
const int maxn=23;
const int INF=~0U>>1;
const int maxnode=20*20+10,maxm=410*90*2;
typedef pair<int,int> pi;
int n,m;
char s[maxn][maxn];
bool im[maxn][maxn];
int Ti;

struct Edge{
	int from,to,flow,cap,dist;
	Edge() {};
	Edge(int from,int to,int flow,int cap,int dist) :from(from),to(to),flow(flow),cap(cap),dist(dist) {}
};

struct Dinic{
	int first[maxnode],edge,next[maxm];
	Edge edges[maxm];
	int cur[maxnode];
	int n,s,t;
	int d[maxnode];
	
	void init(int nn){
		n=nn;
		memset(first,-1,sizeof(first));edge=0;
	}
	
	void add_edge(int from,int to,int dist,int cap){
		//printf("from:%d to:%d dist:%d cap:%d\n",from,to,dist,cap);
		next[edge]=first[from];
		edges[edge++]=Edge(from,to,0,cap,dist);
		first[from]=edge-1;
		next[edge]=first[to];
		edges[edge++]=Edge(to,from,0,0,dist);
		first[to]=edge-1;
	}
	
	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
		d[s]=0;
		queue<int> q;
		q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
				if(edges[e].dist<=Ti&&edges[e].flow<edges[e].cap){
					if(d[edges[e].to]>d[x]+1){
						d[edges[e].to]=d[x]+1;
						//if(Ti==3) printf("d[%d]:%d dist:%d \n",edges[e].to,d[x]+1,edges[e].dist);
						q.push(edges[e].to);
					}
				}
			}
		}
		return d[t]!=INF;
	}
	
	int DFS(int x,int a){
		if(x==t||a==0) return a;
		int flow=0,f;
		for(int &e=cur[x];e!=-1;e=next[e]){
			if(edges[e].dist<=Ti&&d[edges[e].to]==d[x]+1&&((f=DFS(edges[e].to,min(a,edges[e].cap-edges[e].flow)))>0)){
				a-=f;
				flow+=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(a==0) break;
			}
		}
		//if(flow!=0)
		//printf("x:%d flow:%d\n",x,flow);
		return flow;
	}
	
	int maxflow(int SS,int TT){
		s=SS;t=TT;
		int flow=0;
		while(BFS()){//puts("fuck");
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
};
Dinic g;

int vis[maxn][maxn];
int dx[4]={0,0,-1,1},dy[4]={-1,1,0,0};

void flood(int xx,int yy){
	queue<pi> q;
	q.push(make_pair(xx,yy));
	memset(vis,-1,sizeof(vis));vis[xx][yy]=0;
	while(!q.empty()){
		pi now=q.front();q.pop();
		for(int d=0;d<4;d++){
			int x=now.first+dx[d],y=now.second+dy[d];
			if(x>=1&&x<=n&&y>=1&&y<=m){
				if(s[x][y]=='X'||s[x][y]=='D') continue;
				if(vis[x][y]==-1){
					im[x][y]=true;
					vis[x][y]=vis[now.first][now.second]+1;
					g.add_edge(pos(x,y),pos(xx,yy),vis[x][y],INF);
					q.push(make_pair(x,y));
				}
			}
		}
	}
}

int main(){
	int S=0,T;
	scanf("%d%d",&n,&m);T=n*m+1;
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	g.init(T+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='D') g.add_edge(pos(i,j),T,0,1);
	int change_edge=g.edge;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='D'){
				flood(i,j);
			}
			int people=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			if(s[i][j]=='.') {
				g.add_edge(S,pos(i,j),0,1);
				if(!im[i][j]) {puts("impossible");return 0;}
				people++;
			}
	int L=0,R=n*m;
	while(L<=R){
		int M=(L+R)>>1;
		Ti=M;
		for(int i=0;i<g.edge;i++) g.edges[i].flow=0;
		for(int i=0;i<change_edge;i+=2)
			g.edges[i].cap=Ti;
		int flow=g.maxflow(S,T);
		//printf("M:%d cflow:%d \n",M,flow);
		if(flow==people) R=M-1;
			else L=M+1;
	}
	printf("%d\n",R+1);
	return 0;
}
