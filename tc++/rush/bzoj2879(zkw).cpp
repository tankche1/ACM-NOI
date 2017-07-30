#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=45;
const int maxm=105;
const int maxz=810+maxn+maxm;
int n,m,p[maxn];
int a[maxn][maxm];

struct Edge{
	int from,to,flow,cap,cost;
	Edge() {}
	Edge(int from,int to,int flow,int cap,int cost):from(from),to(to),flow(flow),cap(cap),cost(cost) {}
};

struct ZKW{
	int first[maxz],next[maxn*maxz*2];
	Edge edges[maxn*maxn*2];
	int p[maxz],d[maxz],vis[maxz];
	
	
}zkw;
int cook[maxz];

void Add(int x){
	for(int i=1;i<=n;i++)
		zkw.add_edge(i,x,1,a[i][cook[x]]*num[cook[x]]);
	zkw.add_edge(x,T,1,0);
}

int main(){
	int sump=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&p[i]),sump+=p[i];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&a[i][j]);
	int S=0,T=n+m+sump+1;
	zkw.init(T+1);
	for(int i=1;i<=n;i++)
		zkw.add_edge(S,i,p[i],0);
	for(int i=1;i<=m;i++)
		cook[n+i]=i,num[i]=1,Add(n+i);
	int cnt=n+m;
	zkw.SPFA();
	for(int i=1;i<=sump;i++){
		memset(vis,false,sizeof(vis));
		while(!zkw.Dfs(S,INF)) zkw.adjust();
		int x=zkw.edges[zkw.p[T]].from;
		num[cook[x]]++;cnt++;
		cook[cnt]=cook[x];
		Add(cnt);
	}
	return 0;
}
