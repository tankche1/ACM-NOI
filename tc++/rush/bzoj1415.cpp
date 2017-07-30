#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=~0U>>1;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int n,m;
double dp[maxn][maxn];
int to[maxn][maxn][2];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}
queue<int> Q;

struct Dist{
	int dist[maxn];
	void BFS(int s){
		Q.push(s);
		for(int i=1;i<=n;i++) dist[i]=INF;dist[s]=0;
		while(!Q.empty()){
			int x=Q.front();Q.pop();//printf("x:%d\n",x);
			for(int e=first[x];e!=-1;e=next[e])
				if(dist[v[e]]>dist[x]+1)
					dist[v[e]]=dist[x]+1,Q.push(v[e]),to[s][v[e]][0]=x;
				else if(dist[v[e]]==dist[x]+1) to[s][v[e]][0]=min(to[s][v[e]][0],x);
		}
	}
}node[maxn];

double dfs(int mouse,int cat){
	if(dp[mouse][cat]!=-1) return dp[mouse][cat];
	double &res=dp[mouse][cat];
	if(cat==mouse) return 0;
		if(to[mouse][cat][1]==mouse) return res=1;
	int sum=0;double tot=0;
	for(int e=first[mouse];e!=-1;e=next[e]){
		sum++;
		//if(v[e]!=to[mouse][cat][0])
		tot+=dfs(v[e],to[mouse][cat][1])+1;
		//else tot++;
		//printf("%d %d %.3lf\n",v[e],to[v[e]][cat][1],dfs(v[e],to[v[e]][cat][1]));
	}
	tot+=dfs(mouse,to[mouse][cat][1])+1;
	//printf("mouse:%d cat:%d res:%.3lf\n",mouse,cat,tot/((sum+1)*1.0));
	return res=tot/((sum+1)*1.0);
}

int main(){
	int a,b;
	int cat,mouse;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	scanf("%d%d",&cat,&mouse);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);
	
	for(int i=1;i<=n;i++)
		node[i].BFS(i),to[i][i][0]=i;
	//puts("fuck");
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			if(to[i][j][0]!=i) to[i][j][1]=to[i][to[i][j][0]][0];
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			dp[i][j]=-1;
	printf("%.3lf\n",dfs(mouse,cat));
	return 0;
}
