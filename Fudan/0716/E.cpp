# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=(50010)<<1;
const int INF=~0U>>1;
int first[maxn],nnext[maxm],u[maxm],v[maxm],edge=0,dis[maxm],fa[maxn];
int d[maxn];
bool used[maxn];
int n,m;

void add_edge(int from,int to,int dist){
	//printf("%d - %d\n",from,to);
	nnext[edge]=first[from];
	v[edge]=to;u[edge]=from;
	dis[edge]=dist;
	first[from]=edge++;
}

struct HeapNode{
	int val,x;
	HeapNode(int val=0,int x=0):val(val),x(x) {}
	bool operator < (const HeapNode &rhs)const{
		return val>rhs.val;
	}
};
priority_queue<HeapNode> Q;

void Dijkstra(int ban){
	for(int i=1;i<=n;i++) used[i]=false,d[i]=INF;
	memset(fa,-1,sizeof(fa));fa[1]=0;
	while(!Q.empty()){Q.pop();}
	d[1]=0;Q.push(HeapNode(0,1));
	while(!Q.empty()){
		int x=Q.top().x;Q.pop();
		if(used[x]) continue;
		if(x==n) break;
		used[x]=1;
		for(int e=first[x];e!=-1;e=nnext[e]){
			if(e==ban||e==(ban^1)) continue;
			if(d[v[e]]>d[x]+dis[e]){
				d[v[e]]=d[x]+dis[e];Q.push(HeapNode(d[v[e]],v[e]));fa[v[e]]=e;
			}
		}
	}
}

vector<int> List;
int main(){
	int tcase;
	scanf("%d",&tcase);
	int a,b,c;
	//memset(rem,0,sizeof(rem));
	while(tcase--){
		scanf("%d%d",&n,&m);
		memset(first,-1,sizeof(first));edge=0;
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&a,&b,&c);
			add_edge(a,b,c);add_edge(b,a,c);
		}
		Dijkstra(-1);//printf("d[n]:%d\n",d[n]);
		if(d[n]==INF) {puts("-1");continue;}
		int x=n;List.clear();
		while(x!=1){
			List.push_back(fa[x]);x=u[fa[x]];
		}
		int ans=-1;
		for(int i=0;i<(int)List.size();i++){
			Dijkstra(List[i]);ans=max(ans,d[n]);
		}
		if(ans==INF) {puts("-1");continue;}
		printf("%d\n",ans);
	}
	return 0;
}
