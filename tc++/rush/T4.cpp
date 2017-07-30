#include<stdio.h>
#include<string.h>
# include<stack>
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
stack<int> S;
bool ok[maxn];
void dfs(int x,bool can,int u,int root){
	//memset(ok,false,sizeof(ok));
	while(!S.empty()) S.pop();
	S.push(x);dp[x][0]=dp[x][1]=0;ok[x]=0;
	while(!S.empty()){
		int x=S.top();//printf("x:%d\n",x);
		if(!ok[x]) {
		vis[x]=1;ok[x]=1;
		for(int e=first[x];e!=-1;e=next[e])
			if(v[e]!=root) dp[v[e]][0]=0,dp[v[e]][1]=0,S.push(v[e]),ok[v[e]]=0;
		}
		else{
				for(int e=first[x];e!=-1;e=next[e])
					if(v[e]!=root) dp[x][0]+=max(dp[v[e]][0],dp[v[e]][1]),dp[x][1]+=dp[v[e]][0];
				if(!can&&x==u) dp[x][1]=-INF;else dp[x][1]+=a[x];S.pop();
			}
	}
}

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

int main(){
	int x;
	scanf("%d",&tcase);
	int t=0;
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
				int u=i;
				//while(u!=x) vis[u]=0,u=fa[u];vis[x]=0;
				//printf("i:%d\n",i);
				dfs(x,0,fa[x],x);res=dp[x][1];//while(u!=x) vis[u]=0,u=fa[u];vis[x]=0;
				dfs(x,1,fa[x],x);res=max(res,dp[x][0]);
				//printf("res:%d\n",res);
				ans+=res;
			}
			printf("Case #%d:\n",++t);
		printf("%d\n",ans);
	}
	return 0;
}
