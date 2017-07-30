# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1005;
typedef long long LL;
bool vis[maxn];
int prime[maxn];
void get_prime(int n){
	memset(vis,false,sizeof(vis));prime[0]=0;
	for(int i=2;i<=n;i++){
		if(!vis[i]){
			prime[++prime[0]]=i;
			for(int j=i*i;j<=n;j+=i)
				vis[j]=true;
		}
	}//printf("%d\n",prime[0]);
}
LL dp[200][maxn];
int main(){
	int n;
	scanf("%d",&n);
	get_prime(n);
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	for(int i=1;i<=prime[0];i++){
		for(int j=0;j<=n;j++){
			if(dp[i-1][j]){
				//printf("dp[%d][%d]:%d\n",i-1,j,dp[i-1][j]);if(i>prime[0]) continue;
				dp[i][j]+=dp[i-1][j];
				for(int v=prime[i];v+j<=n;v*=prime[i]){
					dp[i][v+j]+=dp[i-1][j];
				}
			}
		}
	}
	/*for(int i=160;i<=prime[0];i++)
		for(int j=0;j<=n;j++)
			if(dp[i][j]) printf("dp[%d][%d]:%lld\n",i,j,dp[i][j]);*/
	long long ans=0;
	for(int i=0;i<=n;i++)
		ans+=dp[prime[0]][i];
	printf("%lld\n",ans);
	return 0;
}
