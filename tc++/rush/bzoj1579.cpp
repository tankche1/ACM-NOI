# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxk=22;
const int maxm=50010<<1;
typedef long long LL;
const LL INF=(LL)(1)<<60;
//const LL INF=~0U>>1;
LL ans;
LL d[maxn][maxk];
int first[maxn],next[maxm],v[maxm],dis[maxm],edge;
bool used[maxn][maxk];
int n,m,k;

struct Node{
	int x,use;
	LL way;
	Node() {}
	Node(int x,int use,LL way):x(x),use(use),way(way) {}
	bool operator < (Node rhs)const{
		return way>rhs.way;
	}
};

void add_edge(int from,int to,int dist){
	//printf("%d - %d\n",from,to);
	next[edge]=first[from];
	v[edge]=to;
	dis[edge]=dist;
	first[from]=edge++;
}

LL dijkstra(){
	priority_queue<Node> q;
	memset(used,false,sizeof(used));
	for(int i=1;i<=n;i++) for(int j=0;j<=k;j++) d[i][j]=INF;
	d[1][0]=0;
	q.push(Node(1,0,0));
	while(!q.empty()){
		Node now=q.top();q.pop();
		if(now.x==n) return d[now.x][now.use];
		if(used[now.x][now.use]) continue;
			//printf("x:%d use:%d d:%d\n",now.x,now.use,d[now.x][now.use]);
		used[now.x][now.use]=1;
		for(int e=first[now.x];e!=-1;e=next[e]){
			//printf("v[e]:%d\n",v[e]);
			if(now.use<k&&d[v[e]][now.use+1]>d[now.x][now.use]){
				d[v[e]][now.use+1]=d[now.x][now.use];
				q.push(Node(v[e],now.use+1,d[v[e]][now.use+1]));
			}
			if(d[v[e]][now.use]>d[now.x][now.use]+dis[e]){
				d[v[e]][now.use]=d[now.x][now.use]+dis[e];
				q.push(Node(v[e],now.use,d[v[e]][now.use]));
			}
		}
	}
	return INF;
}

int main(){
	int a,b,c;
	scanf("%d%d%d",&n,&m,&k);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);add_edge(b,a,c);
	}
	printf("%lld\n",dijkstra());
	return 0;
}
