# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
# define pos(x,y) ((x-1)*n+y)
const int maxn=505;
const int INF=~0U>>1;
int lr[maxn][maxn],ud[maxn][maxn],rl[maxn][maxn],du[maxn][maxn];
int n;
int first[maxn*maxn],next[maxn*maxn*4],v[maxn*maxn*4],w[maxn*maxn*4],edge;
int S,T;
int d[maxn*maxn];

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

struct HeapNode{
	int d,u;
	HeapNode(int d,int u):d(d),u(u) {}
	bool operator < (const  HeapNode &rhs)const{
		return d>rhs.d;
	}
};
priority_queue<HeapNode> Q;
bool used[maxn*maxn];

void dijkstra(){
	for(int i=1;i<=T;i++) d[i]=INF;
	d[S]=0;
	Q.push(HeapNode(0,S));
	while(!Q.empty()){
		int x=Q.top().u;Q.pop();
		if(used[x]) continue;
		used[x]=1;
		for(int e=first[x];e!=-1;e=next[e]){
			if(d[v[e]]>d[x]+w[e])
				d[v[e]]=d[x]+w[e],Q.push(HeapNode(d[v[e]],v[e]));
		}
	}
	printf("%d\n",d[T]);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&lr[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			scanf("%d",&ud[i][j]);
	for(int i=1;i<=n+1;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&rl[i][j]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n+1;j++)
			scanf("%d",&du[i][j]);
	S=0,T=n*n+1;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=n;i++)
		add_edge(S,i,lr[1][i]),add_edge(S,i*n,ud[i][n+1]);
	for(int i=1;i<=n;i++)
		add_edge((i-1)*n+1,T,ud[i][1]),add_edge((n-1)*n+i,T,lr[n+1][i]);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(j>1)
				add_edge(pos(i,j),pos(i,j-1),ud[i][j]);
			if(j<n)
				add_edge(pos(i,j),pos(i,j+1),du[i][j+1]);
			if(i>1)
				add_edge(pos(i,j),pos(i-1,j),rl[i][j]);
			if(i<n)
				add_edge(pos(i,j),pos(i+1,j),lr[i+1][j]);
		}
	dijkstra();
	return 0;
}
