# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int mod=12345678;
const int maxn=155;
const int maxk=22;
int n,m,k;
int dp[2][maxn][maxk][maxk];
int main(){
	scanf("%d%d%d",&n,&m,&k);
	memset(dp,0,sizeof(dp));
	dp[0][0][0][0]=1;
	for(int i=1;i<=n+m;i++){
		int now=i%2;int last=!now;
		memset(dp[now],0,sizeof(dp[now]));
		for(int j=0;j<=min(i,n);j++)
			for(int boy=0;boy<=k;boy++)
				for(int girl=0;girl<=k;girl++){
					if(dp[last][j][boy][girl]>0){
						if(boy+1<=k&&j<=n)
							dp[now][j+1][boy+1][max(girl-1,0)]=(dp[now][j+1][boy+1][max(girl-1,0)]+dp[last][j][boy][girl])%mod;
						if(girl+1<=k&&i-j<=m)
							dp[now][j][max(boy-1,0)][girl+1]=(dp[now][j][max(boy-1,0)][girl+1]+dp[last][j][boy][girl])%mod;
					}
					/*if(dp[last][j][boy][girl]>0)
						printf("dp[%d][%d][%d][%d]:%d\n",i-1,j,boy,girl,dp[last][j][boy][girl]);*/
				}
	}
	long long ans=0;
	for(int boy=0;boy<=k;boy++)
		for(int girl=0;girl<=k;girl++)
			ans+=dp[(n+m)%2][n][boy][girl];
	printf("%d\n",(int)((ans)%mod));
	return 0;
}
