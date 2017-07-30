#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,m;
int u[maxn<<1],v[maxn<<1],next[maxn<<1],first[maxn],edge;

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

bool vis[maxn];
int dfn[maxn],dfs_clock=0;
int dfs(int x){
	vis[x]=1;
	dfn[x]=++dfs_clock;
	int px=-1;
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vis[v[e]]){
			int pv=dfs(v[e]);
			if(pv!=-1)
				printf("%d %d %d\n",x,v[e],v[pv]);
			else if(px!=-1)
				printf("%d %d %d\n",v[px],x,v[e]),px=-1;
			else px=e;
		}
		else{
			if(dfn[v[e]]<dfn[x]) continue;
			if(px==-1) px=e;
			else printf("%d %d %d\n",v[px],x,v[e]),px=-1;
		}
	}
	return px;
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);
	}
	if(m&1) {puts("No solution");return 0;}
	memset(vis,false,sizeof(vis));
	dfs(1);
	return 0;
}
