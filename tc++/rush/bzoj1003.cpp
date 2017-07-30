# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=1<<29;

struct Edge{
	int from,to,dist,next;
};
Edge edges[1000];
int first[22],edge_cnt;

void add_edge(int from,int to,int dist){
	edges[edge_cnt].from=from;
	edges[edge_cnt].to=to;
	edges[edge_cnt].dist=dist;
	edges[edge_cnt].next=first[from];
	first[from]=edge_cnt++;
}

struct HeapNode{
	int d,u;
	
	HeapNode(int d,int u):d(d),u(u){
	}
	
	bool operator < (const HeapNode& rhs) const{
		return d>rhs.d;
	}
};


struct Dijkstra{
	int d[22];
	int n,m;
	bool done[22];
	bool vis[22];
	
	void init(int a,int b){
		n=a;b=m;
	}
	
	void dijkstra(int s){
		for(int i=1;i<=n;i++) d[i]=INF;
		d[s]=0;
		priority_queue<HeapNode> q;
		memset(done,false,sizeof(done));
		HeapNode h(0,s);
		q.push(h);
		while(!q.empty()){
			int x=q.top().u;q.pop();
			//printf("x:%d\n",x);
			if(done[x]) continue;
			done[x]=true;
			for(int e=first[x];e!=-1;e=edges[e].next){
				if(!vis[edges[e].to]) continue;
				int v=edges[e].to;
				if(d[v]>d[x]+edges[e].dist){
					d[v]=d[x]+edges[e].dist;
					HeapNode h(d[v],v);
					//printf("%d %d\n",h.d,h.u);
					q.push(h);
				}
			}
		}
	}
};
Dijkstra g;

int n,m,K,e,q;
int day[1001][3];

int cost(int a,int b){
	for(int i=1;i<=m;i++) g.vis[i]=true;
	for(int i=1;i<=q;i++){
		if(!(day[i][1]>b||day[i][2]<a)) g.vis[day[i][0]]=false;
	}
//	for(int i=1;i<=n;i++) printf("vis[%d]:%d\n",i,g.vis[i]);
	g.init(m,edge_cnt);
	g.dijkstra(1);
	//printf("a:%d b:%d d[m]:%d\n",a,b,g.d[m]);
	if(g.d[m]==INF)
	return g.d[m];
	else return g.d[m]*(b-a+1);
}

int dp[110],from,to,dist;
int main(){
	edge_cnt=0;
	scanf("%d%d%d%d",&n,&m,&K,&e);
	memset(first,-1,sizeof(first));
	for(int i=0;i<e;i++){
		scanf("%d%d%d",&from,&to,&dist);
		add_edge(from,to,dist);
		add_edge(to,from,dist);
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&day[i][0],&day[i][1],&day[i][2]);
	}
	dp[0]=-K;
	for(int i=1;i<=n;i++){
		dp[i]=INF;
		for(int j=1;j<=i;j++){
			dp[i]=min(dp[i],dp[j-1]+cost(j,i)+K);
		}
	}
	printf("%d\n",dp[n]);
	return 0;
}
