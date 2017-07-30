#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=110;
const int INF=maxn*maxn*maxn;
int m,n;
int a[maxn][maxn];
int dp[maxn][maxn];
int fromu[maxn],froml[maxn],fromd[maxn];
int main(){
	int tcase;
	scanf("%d",&tcase);
	int T=0;
	while(tcase--){
		scanf("%d%d",&m,&n);
		for(int i=1;i<=m;i++)
			for(int j=1;j<=n;j++)
				scanf("%d",&a[i][j]);
			dp[1][0]=0;
		for(int i=1;i<=m;i++)
			dp[i][1]=dp[i-1][1]+a[i][1];
		for(int j=2;j<=n;j++){
			for(int i=1;i<=m;i++) froml[i]=dp[i][j-1]+a[i][j],fromu[i]=-INF,fromd[i]=-INF;
			for(int i=2;i<=m;i++) fromu[i]=max(fromu[i-1]+a[i][j],froml[i-1]+a[i][j]);
			for(int i=m-1;i>=1;i--) fromd[i]=max(fromd[i+1]+a[i][j],froml[i+1]+a[i][j]);
			for(int i=1;i<=m;i++)
				dp[i][j]=max(max(froml[i],fromu[i]),fromd[i]);//,printf("dp[%d][%d]:%d\n",i,j,dp[i][j]);
		}
		printf("Case #%d:\n",++T);
		printf("%d\n",dp[1][n]);
	}
	return 0;
}
