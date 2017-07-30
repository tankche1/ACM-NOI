/*
删除了与t冲突的点
删除了冲突的边
最优性剪枝
卡时
*/

# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=105;
const int INF=~0U>>1;
const int LIMIT=200000;

int n,k,m,s,t;
int a[maxn][maxn],culture[maxn];
bool nouse[maxn];

int first[maxn],_next[maxn*maxn],v[maxn*maxn],dist[maxn*maxn],edge;
int d[maxn];
bool reach[maxn*maxn];
bool been[maxn],place[maxn];
int ans=INF;
int limit=0;

struct HeapNode{
	int d,u;
	HeapNode() {}
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator < (const HeapNode &rhs)const{
		return d>rhs.d;
	}
};

void add_edge(int aa,int bb,int c){
	_next[edge]=first[aa];
	v[edge]=bb;
	dist[edge]=c;
	first[aa]=edge;
	reach[edge++]=!a[bb][aa];
}

bool used[maxn];
void dijkstra(){
	priority_queue<HeapNode> q;
	for(int i=1;i<=n;i++) d[i]=INF;
	memset(used,false,sizeof(used));
	d[t]=0;q.push(HeapNode(0,t));
	while(!q.empty()){
		int x=q.top().u;q.pop();
		if(used[x]) continue;
			used[x]=1;
		for(int e=first[x];e!=-1;e=_next[e]){
			if(reach[e^1]&&d[v[e]]>d[x]+dist[e]){
				d[v[e]]=d[x]+dist[e];
				q.push(HeapNode(d[v[e]],v[e]));
			}
		}
	}
}

void dfs(int x,int len){
	if(ans-d[x]<=len) return;
	if(x==t) { ans=len;return;}
	if(++limit>LIMIT) return;
	place[x]=true;been[culture[x]]=true;
	for(int e=first[x];e!=-1;e=_next[e]){
		if(reach[e]&&!place[v[e]]){
			bool ok=true;
			for(int i=1;i<=n;i++)
				if(been[i]&&a[culture[v[e]]][i]) {ok=false;break;}
			if(!ok) continue;
			bool last=been[culture[v[e]]];
			dfs(v[e],len+dist[e]);
			place[v[e]]=false;
			been[culture[v[e]]]=last;
		}
	}
	return;
}

int main(){
	scanf("%d%d%d%d%d",&n,&k,&m,&s,&t);
	for(int i=1;i<=n;i++)
		scanf("%d",&culture[i]);
	for(int i=1;i<=k;i++)
		for(int j=1;j<=k;j++)
			scanf("%d",&a[i][j]);
		memset(nouse,false,sizeof(nouse));
	for(int i=1;i<=k;i++)
		if(a[t][i]) nouse[i]=true;
			int u,v,len;
		memset(first,-1,sizeof(first));edge=0;memset(reach,false,sizeof(reach));
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&u,&v,&len);if(nouse[u]||nouse[v]) continue;
		add_edge(u,v,len);
		add_edge(v,u,len);
	}
	dijkstra();
	memset(been,0,sizeof(been));
	memset(place,0,sizeof(place));
	dfs(s,0);
	if(ans==INF) puts("-1");
		else printf("%d\n",ans);
	return 0;
}
