# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL dp[2][1<<10];
int n,m;
int cur=0;
int maxs;
int main(){
	while(scanf("%d%d",&m,&n)!=EOF){
	if(m<n) swap(m,n);
	memset(dp,0,sizeof(dp));
	maxs=1<<n;
	dp[1][maxs-1]=1;cur=0;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			cur^=1;
			memset(dp[cur^1],0,sizeof(dp[cur^1]));
			//printf("i:%d j:%d\n",i,j);
			for(int state=0;state<maxs;state++)
			if(dp[cur][state]>0){
				//printf("dp[%d]:%lld\n",state,dp[cur][state]);
				if(((!(state&1)))&&i>1) dp[cur^1][(state>>1)+(1<<(n-1))]+=dp[cur][state];//,puts("a");;//up
				if((state&1)) dp[cur^1][state>>1]+=dp[cur][state];//,puts("b");
				if((state&1)&&((state&(1<<(n-1)))==0)&&j!=1) dp[cur^1][(state>>1)+(1<<(n-1))+(1<<(n-2))]+=dp[cur][state];//puts("c");
			}
			//int fuck;scanf("%d",&fuck);
		}
	}
	cur^=1;
	LL ans=0;
	//for(int i=0;i<maxs;i++)
		ans=max(ans,dp[cur][maxs-1]);
	printf("%lld\n",ans);
}
	return 0;
}
