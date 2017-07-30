//dp[i][j]=sum(dp[i-1][l]) l>=0&& l<=min(num[i],j)
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxT=1010;
const int mod=1000000;
int num[maxT];
int T,n,A,B;
int dp[2][1000*100+100];
int sum[1000*100+100];
int len[1000];
int main(){
	scanf("%d%d%d%d",&T,&n,&A,&B);
	memset(num,0,sizeof(num));
	int x;
	memset(dp,0,sizeof(dp));
	for(int i=1;i<=n;i++)
		scanf("%d",&x),num[x]++;
	len[0]=0;
	for(int i=1;i<=T;i++)
		len[i]=len[i-1]+num[i];
	len[T+1]=len[T];
	for(int i=0;i<=num[1];i++) sum[i]=1;
	for(int i=1;i<=T;i++){
		int now=i%2;//int last=!now;
		for(int j=0;j<=len[i];j++)
			dp[now][j]=sum[j]-((j-num[i]-1>=0)?sum[j-num[i]-1]:0);//printf("dp[%d][%d]:%d\n",i,j,dp[now][j]);
		sum[0]=1;
		for(int j=1;j<=len[i];j++)
			sum[j]=(sum[j-1]+dp[now][j])%mod;
		for(int j=len[i]+1;j<=len[i+1];j++)
			sum[j]=sum[j-1];
	}
	int ans=(sum[B]-sum[A-1]+mod)%mod;
	printf("%d\n",ans);
	return 0;
}
