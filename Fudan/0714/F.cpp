# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL dp[110][110][2];
int main(){
	int tcase;
	int num,n,m;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&num,&n,&m);
		memset(dp,0,sizeof(dp));dp[0][0][0]=1;
		for(int i=1;i<=n;i++){
			for(int j=0;j<i&&j<=m;j++){
				dp[i][j][0]=dp[i-1][j][0]+dp[i-1][j][1];
				if(j==0) dp[i][j][1]=dp[i-1][j][0];
				else  dp[i][j][1]=dp[i-1][j-1][1]+dp[i-1][j][0];
			}
		}
		printf("%d %I64d\n",num,dp[n][m][0]+dp[n][m][1]);
	}
	return 0;
}
