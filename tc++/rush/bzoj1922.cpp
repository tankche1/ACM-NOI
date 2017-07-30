# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=3010;
const int maxm=70010;
const int INF=~0U>>1;
int Limit[maxn],Min[maxn],dist[maxn],in[maxn];
int u[maxm],v[maxm],w[maxm],first[maxn],next[maxm],edge;
bool used[maxn];
vector<int> G[maxn];
int n,m;

struct HeapNode{
	int d,u;
	HeapNode() {}
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator < (const HeapNode &rhs)const{
		return d>rhs.d;
	}
};

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	u[edge]=a;v[edge]=b;w[edge]=c;
	first[a]=edge++;
}

void dijkstra(){
	priority_queue<HeapNode> Q;
	Q.push(HeapNode(0,1));
	for(int i=1;i<=n;i++)
		dist[i]=Min[i]=INF;
	dist[1]=Min[1]=0;
	memset(used,false,sizeof(used));
	while(!Q.empty()){
		int x=Q.top().u;Q.pop();
		if(used[x]) continue;used[x]=true;
			//printf("dist[%d]:%d\n",x,dist[x]);
		for(int e=first[x];e!=-1;e=next[e]){
			if(Min[v[e]]>dist[x]+w[e]){
				Min[v[e]]=dist[x]+w[e];
				if((!in[v[e]])&&max(Min[v[e]],Limit[v[e]])<dist[v[e]]){
					dist[v[e]]=max(Min[v[e]],Limit[v[e]]);Q.push(HeapNode(dist[v[e]],v[e]));
				}
			}
		}
		for(int i=0;i<G[x].size();i++){
			Limit[G[x][i]]=max(Limit[G[x][i]],dist[x]);
			if(--in[G[x][i]]==0){
				dist[G[x][i]]=max(Limit[G[x][i]],Min[G[x][i]]);
				Q.push(HeapNode(dist[G[x][i]],G[x][i]));
			}
		}
	}
}

int main(){
	int a,b,c,x;
	scanf("%d%d",&n,&m);
	edge=0;memset(first,-1,sizeof(first));
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);if(a==b) continue;
		add_edge(a,b,c);
	}
	memset(Limit,0,sizeof(Limit));
	for(int i=1;i<=n;i++){
		scanf("%d",&in[i]);
		for(int j=1;j<=in[i];j++){
			scanf("%d",&x);G[x].push_back(i);
		}
	}
	
	dijkstra();
	printf("%d\n",dist[n]);
	return 0;
}
