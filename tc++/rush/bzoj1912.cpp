#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,K;
int first[maxn],next[maxn<<1],v[maxn<<1],edge,w[maxn<<1];
int dp[maxn],bot[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=1;
	first[a]=edge++;
}
int _max=0,node1,node2;
int fa[maxn],deep[maxn];

void dfs(int x){
	dp[x]=0;bot[x]=x;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa[x]) continue;fa[v[e]]=x;deep[v[e]]=deep[x]+1;
		dfs(v[e]);
		if(dp[x]+w[e]+dp[v[e]]>_max)
			_max=dp[x]+w[e]+dp[v[e]],node1=bot[x],node2=bot[v[e]];
		if(dp[v[e]]+w[e]>dp[x])
			dp[x]=dp[v[e]]+w[e],bot[x]=bot[v[e]];
	}
	if(dp[x]>_max)
		_max=dp[x],node1=bot[x],node2=x;
}

int main(){
	int a,b;
	scanf("%d%d",&n,&K);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		add_edge(b,a);
	}
	fa[1]=1;deep[1]=1;
	dfs(1);
	int ans=_max;
	if(K>1){
	a=node1,b=node2;
	if(deep[a]<deep[b]) swap(a,b);
	while(deep[a]>deep[b]){
		for(int e=first[fa[a]];e!=-1;e=next[e])
			if(v[e]==a) {w[e]=-1;break;}
		a=fa[a];
	}
	while(a!=b){
		for(int e=first[fa[a]];e!=-1;e=next[e])
			if(v[e]==a) {w[e]=-1;break;}
		a=fa[a];
			for(int e=first[fa[b]];e!=-1;e=next[e])
			if(v[e]==b) {w[e]=-1;break;}
		b=fa[b];
	}_max=0;
	dfs(1);
	ans+=_max;
}
	printf("%d\n",2*(n-1)-ans+K);
	return 0;
}
