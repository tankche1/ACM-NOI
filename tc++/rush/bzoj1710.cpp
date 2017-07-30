# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=141;
const int maxm=2010;
const int INF=~0U>>1;
int n,m;
int dp[maxm][maxm];
int cost[maxn];
char s[maxm];

int dfs(int L,int R){
	//printf("L:%d R:%d \n",L,R);
	if(dp[L][R]!=-1) return dp[L][R];
	int &res=dp[L][R];
	res=INF;
	if(R<=L){return res=0;}
	res=min(dfs(L+1,R)+cost[s[L]],dfs(L,R-1)+cost[s[R]]);
	if(s[L]==s[R]) res=min(res,dfs(L+1,R-1));
	//	printf("L:%d R:%d res:%d\n",L,R,res);
	return res;
}

int main(){
	scanf("%d%d",&n,&m);
	scanf("%s",s);
	char t;
	for(int i=1;i<=n;i++){
		while((t=getchar())&&t<'a'||t>'z');
			int x,y;scanf("%d%d",&x,&y);
			cost[t]=min(x,y);
		//printf("cost[%d]:%d\n",t,cost[t]);
	}
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(0,m-1));
	return 0;
}
