# include<stdio.h>
# include<string.h>
# include<stack>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010,maxm=1000010;
int N,M,X;
int first[maxn],next[maxm],v[maxm],edge;
vector<int> G[maxn];
int dp[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

int dfn[maxn],dfs_clock,low[maxn];
int sccno[maxn],sccno_cnt[maxn],col;
stack<int> Stack;

void dfs(int x){
	dfn[x]=low[x]=++dfs_clock;
	Stack.push(x);
	for(int e=first[x];e!=-1;e=next[e]){
		if(!dfn[v[e]]){
			dfs(v[e]);
			low[x]=min(low[x],low[v[e]]);
		}
		else if(!sccno[v[e]]) low[x]=min(low[x],dfn[v[e]]);
	}
	if(low[x]==dfn[x]){
		int u;col++;sccno_cnt[col]=0;
		do{
			u=Stack.top();Stack.pop();
			sccno[u]=col;
			sccno_cnt[col]++;
		}while(u!=x);
	}
	return;
}

void tarjan(){
	memset(dfn,0,sizeof(dfn));
	memset(sccno,0,sizeof(sccno));
	dfs_clock=0;
	col=0;
	for(int i=1;i<=N;i++)
		if(!dfn[i]) {dfs(i);}
}

int in[maxn],out[maxn];
int plan[maxn];

int main(){
	int a,b;
	scanf("%d%d%d",&N,&M,&X);
	memset(first,-1,sizeof(first));
	edge=0;
	for(int i=1;i<=M;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);
	}
	tarjan();
	for(int i=1;i<=N;i++){
		for(int e=first[i];e!=-1;e=next[e])
			if(sccno[i]!=sccno[v[e]]){
				bool ok=true;
				for(int j=0;j<G[sccno[i]].size();j++)
					if(G[sccno[i]][j]==sccno[v[e]]) {ok=false;break;}
					if(ok){
						G[sccno[i]].push_back(sccno[v[e]]);
						out[sccno[i]]++;in[sccno[v[e]]]++;
					}
			}
	}
	queue<int> Q;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=col;i++){
		if(in[i]==0) Q.push(i),dp[i]=sccno_cnt[i],plan[i]=1;
	}
	int ans=0;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		if(dp[x]>ans) ans=dp[x];
		for(int i=0;i<G[x].size();i++){
			if(dp[x]+sccno_cnt[G[x][i]]>dp[G[x][i]])
				dp[G[x][i]]=dp[x]+sccno_cnt[G[x][i]],plan[G[x][i]]=plan[x];
			else if(dp[x]+sccno_cnt[G[x][i]]==dp[G[x][i]])
				plan[G[x][i]]=(plan[G[x][i]]+plan[x])%X;
			if(--in[G[x][i]]==0) Q.push(G[x][i]);
		}
	}
	printf("%d\n",ans);
	int num=0;
	for(int i=1;i<=col;i++)
		if(dp[i]==ans) 
			num=(num+plan[i])%X;
	printf("%d\n",num);
	return 0;
}
