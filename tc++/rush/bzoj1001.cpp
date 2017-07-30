# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=1005;
struct Edge{
	int from,to,dist,next;
};
Edge edges[maxn*maxn*3*2];
int first[maxn*maxn*2],edge_cnt;

struct HeapNode{
	int d,u;
	HeapNode(int d,int u):d(d),u(u) {}
	bool operator < (const HeapNode& rhs)const{
		return d>rhs.d;
	}
};

struct Dijkstra{
	int n;
	bool done[maxn*maxn*2];
	int d[maxn*maxn*2];
	
	void init(int n){
		this->n=n;
	}
	
	void dijkstra(int s){
		for(int i=0;i<n;i++) 
			d[i]=INF;
		d[s]=0;
		priority_queue<HeapNode> q;
		HeapNode h(0,s);q.push(h);
		memset(done,false,sizeof(done));
		while(!q.empty()){
			int x=q.top().u;q.pop();
			if(done[x]) continue;
				done[x]=true;
			for(int e=first[x];e!=-1;e=edges[e].next){
				int v=edges[e].to;
				if(d[v]>d[x]+edges[e].dist){
					d[v]=d[x]+edges[e].dist;
					HeapNode h(d[v],v);
					q.push(h);
				}
			}
		}
	}
};
Dijkstra g;

void add_edge(int from,int to,int dist){
	//printf("from:%d to:%d dist:%d\n",from,to,dist)
	edges[edge_cnt].next=first[from];
	edges[edge_cnt].from=from;
	edges[edge_cnt].to=to;
	edges[edge_cnt].dist=dist;
	first[from]=edge_cnt++;
}

int n,m,ans;
int main(){
	int a;
	scanf("%d%d",&n,&m);
	if(n==1||m==1){
		ans=INF;
		for(int i=1;i<max(m,n);i++){
		scanf("%d",&a);
		ans=min(ans,a);
		}
		printf("%d\n",ans);return 0;
	}
	int S=0,T=(n-1)*(m-1)*2+1,from,to;
	memset(first,-1,sizeof(first));edge_cnt=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<m;j++){
			scanf("%d",&a);
			if(i==1) from=T;
				else from=(i-2)*(m-1)*2+2*(j-1)+1;
			if(i==n) to=S;
				else to=(i-1)*(m-1)*2+2*j;
			add_edge(from,to,a);add_edge(to,from,a);
		}
		for(int i=1;i<n;i++)
			for(int j=1;j<=m;j++){
				scanf("%d",&a);
				if(j==1) from=S;
					else from=(i-1)*2*(m-1)+(j-1)*2;
				if(j==m) to=T;
					else to=(i-1)*2*(m-1)+(j-1)*2+1;
				add_edge(from,to,a);add_edge(to,from,a);
			}
		for(int i=1;i<n;i++)
			for(int j=1;j<m;j++){
				scanf("%d",&a);
				from=(i-1)*2*(m-1)+(j-1)*2+1;
				to=from+1;
				add_edge(from,to,a);add_edge(to,from,a);
			}
		g.init(T+1);
		g.dijkstra(S);
		printf("%d\n",g.d[T]);
	return 0;
}
