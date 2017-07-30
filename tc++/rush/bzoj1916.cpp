# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxk=11;
const int maxn=50005;
const int maxm=maxn*3;
const long long INF=(2*(1e+9))*maxn;
int n,m,K;
LL dp[maxn][maxk];
int first[maxn],next[maxm],v[maxm],w[maxm],edge;

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

LL dfs(int now,int k){
	if(dp[now][k]!=-1) return dp[now][k];
	LL &res=dp[now][k];
	res=INF;LL _max=0;
	for(int e=first[now];e!=-1;e=next[e]){
		if(k) res=min(res,dfs(v[e],k-1)+w[e]);
		_max=max(_max,dfs(v[e],k)+w[e]);
	}
	res=min(res,_max);
	//printf("dp[%d][%d]:%d\n",now,k,res);
	return res;
}

int main(){
	scanf("%d%d%d",&n,&m,&K);
	memset(dp,-1,sizeof(dp));
	memset(first,-1,sizeof(first));
	edge=0;
	int a,b,c;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c);
	printf("%lld\n",dfs(1,K));
	return 0;
}
