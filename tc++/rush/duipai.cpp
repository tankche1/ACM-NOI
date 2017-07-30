#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=~0U>>1;
int tcase,n;
int a[maxn];int fa[maxn];
int dp[maxn][2];
int ans;
int first[maxn],v[maxn],next[maxn],edge;
bool vis[maxn];
void dfs(int x,bool can,int u,int root){
	vis[x]=1;
	dp[x][0]=dp[x][1]=0;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==root) continue;
		dfs(v[e],can,u,root);
		dp[x][0]+=max(dp[v[e]][0],dp[v[e]][1]);
		dp[x][1]+=dp[v[e]][0];
	}
	if(!can&&x==u) dp[x][1]=-INF;
	else dp[x][1]+=a[x];
	return;
}

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

int main(){
	int x;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		memset(first,-1,sizeof(first));edge=0;
		for(int i=1;i<=n;i++){
			scanf("%d",&x);
			add_edge(x,i);
			fa[i]=x;
		}
		for(int i=1;i<=n;i++)
			scanf("%d",&a[i]);
		ans=0;
		int res;
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++)
			if(!vis[i]){
				int x=i;
				while(!vis[x]){
					//printf("x:%d\n",x);
					vis[x]=1;
					x=fa[x];
				}
				//printf("i:%d\n",i);
				dfs(x,0,fa[x],x);res=dp[x][1];
				dfs(x,1,fa[x],x);res=max(res,dp[x][0]);
				//printf("res:%d\n",res);
				ans+=res;
			}
		printf("%d\n",ans);
	}
	return 0;
}
