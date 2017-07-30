# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int dp[2][11];
int mod=2007;

int main()
{
	int now,last;
	memset(dp,0,sizeof(dp));
	dp[1][1]=1;
	int n,m;
	scanf("%d%d",&n,&m);
	for(int i=2;i<=n;i++){
		now=i%2;last=now^1;
		for(int j=1;j<=10;j++){
			dp[now][j]=(dp[last][j]*j+dp[last][j-1])%mod;
			//if(dp[i][j]) printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);
			}
		}
		printf("%d\n",dp[n%2][m]);
	return 0;
}