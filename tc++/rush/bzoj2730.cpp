#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=1010;
int dfn[maxn],low[maxn],dfs_clock=0;
int n,m;
int cut[maxn];
int first[maxn],next[maxm],v[maxm],edge;
int num,col;
bool vis[maxn];
void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int x,int fa){
	dfn[x]=low[x]=++dfs_clock;
	int son=0;
	cut[x]=false;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa) continue;
		if(!dfn[v[e]]){
			dfs(v[e],x);
			low[x]=min(low[v[e]],low[x]);
			son++;
			if(low[v[e]]>=dfn[x])
				cut[x]=true;
		}
		else low[x]=min(low[x],dfn[v[e]]);
	}
	if(fa==0) cut[x]=son>=2;
}

void dfs2(int x){
	num++;vis[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(!vis[v[e]]&&!cut[v[e]]) dfs2(v[e]);
		else if(cut[v[e]]&&!vis[v[e]]) col++,vis[v[e]]=true;
}

int main(){
	int tcase=0,a,b;
	while(scanf("%d",&m)!=EOF){
		if(!m) break;
		tcase++;n=0;
		edge=0;memset(first,-1,sizeof(first));
		for(int i=1;i<=m;i++)
			scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a),n=max(n,max(a,b));
		dfs_clock=0;
		memset(dfn,0,sizeof(dfn));
		for(int i=1;i<=n;i++)
			if(!dfn[i]){
				dfs(i,0);
			}
		//for(int i=1;i<=n;i++)
			//printf("cut[%d]:%d\n",i,cut[i]);
		int ans1=0;long long ans2=1;
		memset(vis,false,sizeof(vis));
		//for(int i=1;i<=n;i++) if(cut[i]) vis[i]=true;
		for(int i=1;i<=n;i++)
			if(!vis[i]&&!cut[i]){
				num=0;col=0;
				for(int i=1;i<=n;i++) if(cut[i]) vis[i]=false;
				//printf("i:%d\n",i);
				dfs2(i);
				if(col==1){
					ans2*=num;
					ans1++;
				}
			}
			if(ans1<=1) ans1=2,ans2=n*(n-1)/2;
			printf("Case %d: %d %lld\n",tcase,ans1,ans2);
	}
	return 0;
}
