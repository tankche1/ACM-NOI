# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int C[maxn],in[maxn];
int dp[maxn];
//queue<int> Q;
int Q[maxn],h,t;

int dfs(int x){
	if(dp[x]!=-1) return dp[x];
	return dp[x]=dfs(C[x])+1;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&C[i]),in[C[i]]++;
	memset(dp,-1,sizeof(dp));
	h=t=0;
	for(int i=1;i<=n;i++) if(!in[i]) Q[t++]=i;
	for(int i=0;i<t;i++){
		int x=Q[i];
		if(--in[C[x]]==0) Q[t++]=C[x];
	}
	for(int i=1;i<=n;i++)
		if(dp[i]==-1&&in[i]){
			int now=i,s=0;
			do{
				now=C[now];
				s++;
			}while(now!=i);
			now=i;
			do{
				now=C[now];
				dp[now]=s;
			}while(now!=i);
		}
		for(int i=1;i<=n;i++)
			printf("%d\n",dfs(i));
	return 0;
}
