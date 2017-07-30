#include<stdio.h>
#include<string.h>
# include<queue>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=200010;
typedef long long LL;
const LL INF=(LL)1<<59;
int n,m,len;
int bh[maxn],fa[maxn];
vector<int> G[maxn];
struct Edge{
	int u,v,w;
	Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w) {}
};
Edge edges[maxn<<1];
struct HeapNode{
	int u;LL d;
	HeapNode(int u=0,LL d=0):u(u),d(d) {}
	bool operator <(const HeapNode &rhs)const{
		return d>rhs.d;
	}
};
priority_queue<HeapNode> Q;
int first[maxn],next[maxn<<1],v[maxn<<1],edge,w[maxn<<1];

void init(){memset(first,-1,sizeof(first));edge=0;}
void add_edge(int a,int b,int c){
		next[edge]=first[a];
		v[edge]=b;
		w[edge]=c;
		edges[edge]=Edge(a,b,c);
		first[a]=edge++;
}
bool used[maxn];

struct Dijkstra{
	int p[maxn];
	LL dis[maxn];
	void dijkstra(int s){
		for(int i=1;i<=n;i++) dis[i]=INF;dis[s]=0;
		Q.push(HeapNode(s,dis[s]));
		memset(used,false,sizeof(used));
		while(!Q.empty()){
			int x=Q.top().u;Q.pop();
			if(used[x]) continue;used[x]=1;
			for(int e=first[x];e!=-1;e=next[e]){
				if(dis[v[e]]>dis[x]+w[e]){
					dis[v[e]]=dis[x]+w[e];
					p[v[e]]=x;
					Q.push(HeapNode(v[e],dis[v[e]]));
				}
			}
		}
		//for(int i=1;i<=n;i++) printf("dis[%d]:%lld\n",i,dis[i]);
	}
};
Dijkstra ss,tt;
int S,T;

struct SegmenTree{
	LL _min[maxn<<2],lazy[maxn<<2];
	void build(int o,int L,int R){
		_min[o]=INF;lazy[o]=INF;
		if(L==R) return;
		int M=(L+R)>>1;
		build(o<<1,L,M);build(o<<1|1,M+1,R);
	}
	
	void pushdown(int o){
		if(lazy[o]!=INF){
			_min[o<<1]=min(_min[o<<1],lazy[o]);_min[o<<1|1]=min(_min[o<<1|1],lazy[o]);
			lazy[o<<1]=min(lazy[o<<1],lazy[o]);lazy[o<<1|1]=min(lazy[o<<1|1],lazy[o]);
			lazy[o]=INF;
		}
	}
	
	void update(int o,int L,int R,int qL,int qR,LL val){
		if(qL<=L&&qR>=R) {_min[o]=min(_min[o],val);lazy[o]=min(lazy[o],val);return;}
		int M=(L+R)>>1;
		pushdown(o);
		if(qL<=M) update(o<<1,L,M,qL,qR,val);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
		_min[o]=min(_min[o<<1],_min[o<<1|1]);
	}
	
	LL query(int o,int L,int R,int pos){
		//printf("L:%d R:%d\n",L,R);
		if(L==R) return _min[o];
		pushdown(o);
		int M=(L+R)>>1;
		if(pos<=M) return query(o<<1,L,M,pos);
		else return query(o<<1|1,M+1,R,pos);
	}
}seg;

const int Step=18;
int dp[maxn][Step+1];
int dep[maxn];
void prepare(){
	for(int i=1;i<=n;i++) dp[i][0]=fa[i];
	for(int j=1;j<=Step;j++)
		for(int i=1;i<=n;i++)
		dp[i][j]=dp[dp[i][j-1]][j-1];
}

void dfs(int x){ 
	for(int e=0;e<(int)G[x].size();e++){
		int v=G[x][e];
		dep[v]=dep[x]+1;dfs(v);
	}
}

int Lca(int a,int b){
	if(dep[a]<dep[b]) swap(a,b);
	int t=dep[a]-dep[b];
	for(int j=Step;j>=0;j--)
		if(t&(1<<j)) a=dp[a][j];
	int j=Step;
	while(a!=b){
		while(j&&dp[a][j]==dp[b][j]) j--;
		a=dp[a][j];b=dp[b][j];
	}
	return a;
}

void print(LL t){
	if(t==INF) puts("Infinity");
	else printf("%lld\n",t);
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int a,b,c;
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);add_edge(b,a,c);
	}
	scanf("%d%d",&S,&T);
	ss.dijkstra(S),tt.dijkstra(T);
	
	len=0;fa[S]=S;
	for(int i=1;i<=n;i++){
		if(i!=S) fa[i]=ss.p[i],G[fa[i]].push_back(i);//edges[p[i]].on=true;
		bh[i]=-1;
		//printf("fa[%d]:%d\n",i,fa[i]);
	}
	int u=T;
	while(u!=S){
		len++;u=fa[u];
	}
	len++;
	
	u=T;int num=len;
	while(u!=S){
		bh[u]=num--;
		u=fa[u];
	}
	bh[u]=num--;
	//for(int i=1;i<=n;i++) printf("bh[%d]:%d fa:%d\n",i,bh[i],fa[i]);
	
	dep[S]=0;dfs(S);
	prepare();
	seg.build(1,1,len);
	for(int i=0;i<edge;i++)
		if(fa[edges[i].v]!=edges[i].u){
			int x=edges[i].u,y=edges[i].v,z=edges[i].w;
			LL cost=ss.dis[x]+tt.dis[y]+z;
			//printf("x:%d y:%d z:%d\n",x,y,z);
			if(bh[Lca(x,T)]!=-1&&bh[Lca(x,T)]+1<=bh[Lca(y,T)]) //printf("%d %d %lld\n",bh[Lca(x,y)]+1,bh[Lca(y,T)],cost),
				seg.update(1,1,len,bh[Lca(x,T)]+1,bh[Lca(y,T)],cost);
		}
	int q;
	scanf("%d",&q);
	//for(int i=1;i<=n;i++) printf("bh[%d]:%d fa:%d\n",i,bh[i],fa[i]);
	while(q--){
		scanf("%d%d",&a,&b);//printf("bh[b]:%d fa[b]:%d\n",bh[b],fa[b]);
		if(fa[a]==b) swap(a,b);
		if(bh[b]!=-1&&fa[b]==a){
			LL t=seg.query(1,1,len,bh[b]);
			print(t);
		}
		else print(ss.dis[T]);
	}
	return 0;
}
/*
6 7 
1 2 1 
2 3 1 
3 4 2 
4 5 1 
5 6 1
1 3 3 
4 6 3 
1 6 
4
1 2
1 3
4 3
6 5
*/
