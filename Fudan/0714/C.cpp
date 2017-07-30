# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=~0U>>1;
int dp[maxn][55];
int main(){
	int num,n,m;
	memset(dp[0],0,sizeof(dp[0]));
	for(int i=1;i<=50;i++)
		dp[1][i]=1;
	for(int i=2;i<=1000;i++){
		dp[i][1]=i;
		for(int j=2;j<=50;j++){
			dp[i][j]=INF;
			for(int x=1;x<=i;x++){
				dp[i][j]=min(dp[i][j],max(dp[x-1][j-1],dp[i-x][j])+1);
			}
			//printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);
		}
	}
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&num,&m,&n);
		printf("%d %d\n",num,dp[n][m]);
	}
	return 0;
}
