#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=205;
const int maxm=10005;
int col[maxm];
int tcase,n,m;
struct Edge{
	int u,v;
};
Edge edges[maxm];
int bh[maxn];
vector<int> G[maxm];

/*void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}*/

bool cmp(Edge a,Edge b){
	if(a.u!=b.u) return a.u<b.u;
	return a.v<b.v;
}

bool dfs(int x){
	for(int e=0;e<G[x].size();e++){
		int v=G[x][e];
		//printf("x:%d v:%d\n",x,v);
		if(col[v]==-1){
			col[v]=col[x]^1;
			if(!dfs(v)) return false;
		}
		else if(col[v]==col[x]) return false;
	}
	return true;
}

int main(){
	int x;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=m;i++)
			scanf("%d%d",&edges[i].u,&edges[i].v);
		for(int i=1;i<=n;i++)
			scanf("%d",&x),bh[x]=i;
		if(m>3*n-6) {puts("NO");continue;}
		//edge=0;memset(first,-1,sizeof(first));
		for(int i=1;i<=m;i++){
			edges[i].u=bh[edges[i].u],edges[i].v=bh[edges[i].v];if(edges[i].u>edges[i].v) swap(edges[i].u,edges[i].v);
				
			G[i].clear();
		}
			//add_edge(bh[edges[i].u],bh[edges[i].v]),add_edge(bh[edges[i].v],bh[edges[i].u]);
		sort(edges+1,edges+m+1,cmp);
		//for(int i=1;i<=m;i++)
		//	printf("new:%d %d\n",edges[i].u,edges[i].v);
		for(int i=1;i<=m;i++)
			for(int j=i+1;j<=m;j++)
				if(edges[j].u>edges[i].u&&edges[i].v>edges[j].u&&edges[j].v>edges[i].v)
					G[i].push_back(j),G[j].push_back(i);//printf("%d %d\n",i,j);
				else if(edges[j].u>=edges[i].v) break;
		bool ok=true;
				memset(col,-1,sizeof(col));
		for(int i=1;i<=m;i++)
			if(col[i]==-1){
				col[i]=0;
				if(!dfs(i)) {ok=false;break;}
			}
			if(ok) puts("YES");
				else puts("NO");
	}
	return 0;
}
/*
2         
6 9        
1 4  
1 5  
1 6  
2 4  
2 5  
2 6  
3 4  
3 5  
3 6  
1 4 2 5 3 6  
5 5  
1 2  
2 3  
3 4  
4 5  
5 1  
1 2 3 4 5  
*/
