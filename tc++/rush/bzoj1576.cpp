#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=maxn<<2;
const int INF=~0U>>1;
int n,m;
int fa[maxn];
int dep[maxn];
struct Edge{
	int u,v,w;
	Edge(int u=0,int v=0,int w=0):u(u),v(v),w(w) {}
	bool operator <(const Edge &rhs)const{
		return w<rhs.w;
	}
};
Edge edges[maxm];
Edge loop[maxm];int cnt;

struct HeapNode{
	int u,d;
	HeapNode(int u=0,int d=0):u(u),d(d) {}
	bool operator <(const HeapNode &rhs)const{
		return d>rhs.d;
	}
};

priority_queue<HeapNode> Q;
int first[maxn],next[maxm],v[maxm],edge,w[maxm];

void init(){memset(first,-1,sizeof(first));edge=0;}
void add_edge(int a,int b,int c){
		next[edge]=first[a];
		v[edge]=b;
		w[edge]=c;
		edges[edge]=Edge(a,b,c);
		first[a]=edge++;
}

struct Dijkstra{
	bool used[maxn];
	int dis[maxn];
	void dijkstra(int s){
		for(int i=1;i<=n;i++) dis[i]=INF;dis[s]=0;fa[s]=s;dep[s]=0;
		Q.push(HeapNode(s,dis[s]));
		memset(used,false,sizeof(used));
		while(!Q.empty()){
			int x=Q.top().u;Q.pop();
			if(used[x]) continue;used[x]=1;
			for(int e=first[x];e!=-1;e=next[e]){
				if(dis[v[e]]>dis[x]+w[e]){
					dis[v[e]]=dis[x]+w[e];
					dep[v[e]]=dep[x]+1;
					fa[v[e]]=x;
					Q.push(HeapNode(v[e],dis[v[e]]));
				}
			}
		}
		//for(int i=1;i<=n;i++) printf("dis[%d]:%lld\n",i,dis[i]);
	}
}Tree;
int p[maxn];
int find(int x){if(x==p[x]) return x;return p[x]=find(x);}
int ans[maxn];

int main(){
	int a,b,c;
	scanf("%d%d",&n,&m);
	init();
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}cnt=0;
	Tree.dijkstra(1);
	for(int i=0;i<2*m;i++){
		a=edges[i].u,b=edges[i].v,c=edges[i].w;
		if(dep[a]>dep[b]||fa[a]==b||fa[b]==a) continue;
		loop[cnt].u=a;loop[cnt].v=b;loop[cnt].w=Tree.dis[a]+Tree.dis[b]+c;
		//printf("%d %d %d\n",a,b,loop[cnt].w);
		cnt++;
	}
	sort(loop,loop+cnt);
	for(int i=1;i<=n;i++) p[i]=i;
	memset(ans,-1,sizeof(ans));
	for(int i=0;i<cnt;i++){
		int a=loop[i].u,b=loop[i].v;
		int lasta=-1,lastb=-1;//printf("a:%d b:%d\n",a,b);
		while(find(a)!=find(b)){
			//printf("a:%d b:%d\n",a,b);
			if(dep[a]>dep[b]) swap(a,b),swap(lasta,lastb);
			if(lastb!=-1) p[lastb]=b;
			if(ans[b]==-1) ans[b]=loop[i].w-Tree.dis[b];
			b=fa[p[b]];
		}
	}
	for(int i=2;i<=n;i++)
		printf("%d\n",ans[i]);
	return 0;
}
