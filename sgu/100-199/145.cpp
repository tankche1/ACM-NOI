# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
int n,m,k;
const int maxn=110;
const int maxm=10010;
vector<int> last;
int first[maxn],next[maxm<<1],v[maxm<<1],w[maxm<<1],edge,pre[maxn];
int st,ed;
int cnt;
int ans;
int from[maxn];
bool vis[maxn];
	
void add_edge(int a,int b,int c){
	v[edge]=b;
	w[edge]=c;
	next[edge]=first[a];
	first[a]=edge++;
}

struct Dijkstra{
	int d[maxn];
	bool used[maxn];
	struct HeapNode{
		int d,u;
		HeapNode(int d=0,int u=0):d(d),u(u) {}
		bool operator < (const HeapNode &rhs)const{
			return d<rhs.d;
		}
	};
	
	void dijkstra(){
		priority_queue<HeapNode> Q;
		Q.push(HeapNode(0,ed));
		for(int i=1;i<=n;i++) d[i]=INF;d[ed]=0;
		memset(used,false,sizeof(used));
		while(!Q.empty()){
			int x=Q.top().u;Q.pop();
			if(used[x]) continue;
			used[x]=1;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]>d[x]+w[e])
					d[v[e]]=d[x]+w[e],Q.push(HeapNode(d[v[e]],v[e]));
			}
		}
	}
	
};Dijkstra dij;

void dfs(int u,int dis,int limit,bool record){
	vis[u]=1;
	if(cnt>k) {vis[u]=0;return;}
	if(dis+dij.d[u]>limit) {vis[u]=0;return;}
	if(u==ed){
		cnt++;if(dis==limit&&record) memcpy(pre,from,sizeof(from));
		vis[u]=0;return;
	}
	for(int e=first[u];e!=-1;e=next[e]){
		if(!vis[v[e]])
			from[v[e]]=u,dfs(v[e],dis+w[e],limit,record);
	}
	vis[u]=0;return;
}

int main(){
	scanf("%d%d%d",&n,&m,&k);
	int a,b,c;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);add_edge(b,a,c);
	}
	scanf("%d%d",&st,&ed);
	int L=1,R=1000000;memset(vis,false,sizeof(vis));
	while(L<=R){
		int M=(L+R)>>1;cnt=0;
		dfs(st,0,M,0);
		if(cnt>=k) R=M-1;
		else L=M+1;
	}ans=R+1;
	cnt=0;dfs(st,0,ans,1);
	int u=ed;last.push_back(ed);
	do{
		u=pre[u];
		last.push_back(u);
	}while(u!=st);
	printf("%d %d\n",ans,last.size());
	for(int i=last.size()-1;i>=0;i--)
		printf("%d ",last[i]);putchar(10);
	return 0;
}
