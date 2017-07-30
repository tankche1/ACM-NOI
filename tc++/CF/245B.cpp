#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
int m,n;
int a[maxn][maxn];
int dp[maxn][maxn][4];
int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]);
	
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			dp[i][j][0]=max(dp[i-1][j][0],dp[i][j-1][0])+a[i][j];
		}
		
	for(int i=1;i<=m;i++)
		for(int j=n;j>=1;j--)
			dp[i][j][1]=max(dp[i-1][j][1],dp[i][j+1][1])+a[i][j];
	
	for(int i=m;i>=1;i--)
		for(int j=1;j<=n;j++)
			dp[i][j][2]=max(dp[i+1][j][2],dp[i][j-1][2])+a[i][j];
	
	for(int i=m;i>=1;i--)
		for(int j=n;j>=1;j--)
			dp[i][j][3]=max(dp[i+1][j][3],dp[i][j+1][3])+a[i][j];
	
		int ans=0;
	for(int i=2;i<=m-1;i++)
		for(int j=2;j<=n-1;j++){
			ans=max(ans,dp[i][j-1][0]+dp[i][j+1][3]+dp[i+1][j][2]+dp[i-1][j][1]);
			ans=max(ans,dp[i-1][j][0]+dp[i+1][j][3]+dp[i][j-1][2]+dp[i][j+1][1]);
		}
	printf("%d\n",ans);
	return 0;
}
