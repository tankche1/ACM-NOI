# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=105;
const int mod=9999973;
typedef long long LL;
LL dp[maxn][maxn][maxn];
int n,m;
void add(LL &x,LL y){
	x=(x+y)%mod;
}
int main(){
	scanf("%d%d",&n,&m);
	memset(dp,0,sizeof(dp));dp[0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=m;j++)
			for(int k=0;j+k<=m;k++){
				if(dp[i][j][k]!=0){
					for(int num=0;num<=2;num++){
						if(num==0) dp[i+1][j][k]=(dp[i+1][j][k]+dp[i][j][k])%mod;
						if(num==1){
							dp[i+1][j+1][k]=(dp[i+1][j+1][k]+dp[i][j][k]*(m-j-k))%mod;
							if(j>=1)  dp[i+1][j-1][k+1]=(dp[i+1][j-1][k+1]+dp[i][j][k]*j)%mod;
						}
						if(num==2){
							if(m-j-k>=2) add(dp[i+1][j+2][k],dp[i][j][k]*(m-j-k)*(m-j-k-1)/2);
							if(j>=1&&m-j-k>=1) add(dp[i+1][j][k+1],dp[i][j][k]*(m-j-k)*(j));
							if(j>=2) add(dp[i+1][j-2][k+2],dp[i][j][k]*j*(j-1)/2);
						}
					}
				}
			}
	}
	LL ans=0;
	for(int j=0;j<=m;j++)
		for(int k=0;j+k<=m;k++)
			add(ans,dp[n][j][k]);
		printf("%lld\n",ans);
	return 0;
}
