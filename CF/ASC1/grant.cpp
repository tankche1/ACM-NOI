# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

const int maxn=500100;
int n;
int dp[maxn][2];
bool son[maxn];
int track[maxn];
int first[maxn],next[maxn],v[maxn],edge=0;
int ans[maxn],ans_num=0;
void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void Tree_dp(int x){
	int tot0=0;
	for(int e=first[x];e!=-1;e=next[e])
		Tree_dp(v[e]),tot0+=max(dp[v[e]][0],dp[v[e]][1]);
	dp[x][0]=tot0;
	for(int e=first[x];e!=-1;e=next[e])
		if(1000+tot0-max(dp[v[e]][0],dp[v[e]][1])+dp[v[e]][0]>dp[x][1])
			dp[x][1]=1000+tot0-max(dp[v[e]][0],dp[v[e]][1])+dp[v[e]][0],track[x]=v[e];
	//printf("dp[%d][0]:%d [1]:%d\n",x,dp[x][0],dp[x][1]);
}

void dfs(int x,int t){
	if(t==0){
		for(int e=first[x];e!=-1;e=next[e])
			if(dp[v[e]][0]>=dp[v[e]][1]) dfs(v[e],0);
			else dfs(v[e],1);
	}
	else{
		for(int e=first[x];e!=-1;e=next[e]){
			if(v[e]==track[x]){
				ans[ans_num++]=v[e];dfs(v[e],0);
			}
			else{
				if(dp[v[e]][0]>=dp[v[e]][1]) dfs(v[e],0);
				else dfs(v[e],1);
			}
		}
	}
}

int main()
{
	freopen("grant.in","r",stdin);
	freopen("grant.out","w",stdout);
	int fa;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));
	for(int i=2;i<=n;i++)
		scanf("%d",&fa),add_edge(fa,i),son[fa]=1;
	memset(dp,0,sizeof(dp));
	Tree_dp(1);
	printf("%d\n",max(dp[1][0],dp[1][1]));
	if(dp[1][0]>=dp[1][1])
		dfs(1,0);
	else dfs(1,1);
	sort(ans,ans+ans_num);
	for(int i=0;i<ans_num;i++)
		printf("%d ",ans[i]);
	puts("");
	return 0;
}
