# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int INF=maxn;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int dp[maxn][3];
int du[maxn];
//0 覆盖全部 根不建 1 覆盖全部 根建 2根不覆盖
int n;

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int x,int fa){
	if(du[x]==1) {
		dp[x][0]=1;dp[x][1]=INF;dp[x][2]=0;
	}
	dp[x][0]=dp[x][1]=dp[x][2]=0;
	int spe=INF;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa) continue;
		dfs(v[e],x);
		dp[x][0]+=min(dp[v[e]][0],dp[v[e]][1]);
		spe=min(spe,dp[v[e]][1]-dp[v[e]][0]);
		dp[x][1]+=min(min(dp[v[e]][0],dp[v[e]][1]),dp[v[e]][2]);
		dp[x][2]+=dp[v[e]][0];
	}
	dp[x][0]+=spe<=0?0:spe;
	dp[x][1]++;
	return;
}

int main(){
	scanf("%d",&n);
	int a,b;
	memset(first,-1,sizeof(first));edge=0;
	memset(du,0,sizeof(du));
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);du[a]++;du[b]++;
		add_edge(a,b);add_edge(b,a);
	}
	dfs(1,0);
	printf("%d\n",min(dp[1][0],dp[1][1]));
	return 0;
}
