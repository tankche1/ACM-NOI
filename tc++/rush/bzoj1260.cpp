# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
int n;
char s[100];
int dp[60][60];
int dfs(int l,int r){
	if(dp[l][r]!=-1) return dp[l][r];
	if(r-l+1==1) return dp[l][r]=1;
	dp[l][r]=INF;
	for(int k=l;k<r;k++)
		dp[l][r]=min(dfs(l,k)+dfs(k+1,r),dp[l][r]);
	//printf("dp[%d][%d]:%d\n",l,r,dp[l][r]-(s[l]==s[r]));
	return dp[l][r]-=(s[l]==s[r]);
}
int main(){
	scanf("%s",s);
	n=strlen(s);memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(0,n-1));
	return 0;
}
