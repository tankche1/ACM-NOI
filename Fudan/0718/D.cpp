# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1010;
const int mod=1000000007;
char s[maxn];
int n;
LL dp[maxn][maxn];
LL sum[maxn];
int main(){
	//freopen("in.txt","r",stdin);
	while(scanf("%s",s+2)!=EOF){
		for(int i=2;;i++)
			if(s[i]=='\0') {n=i;break;}
		n--;
		sum[0]=0;
		for(int j=1;j<=n;j++) dp[1][j]=1,sum[j]=sum[j-1]+dp[1][j];
		for(int i=2;i<=n;i++){
			for(int j=1;j<=(n-(i-1));j++){
				if(s[i]=='I') dp[i][j]=sum[j];
				else if(s[i]=='D') {dp[i][j]=sum[(n-(i-2))]-sum[j];if(dp[i][j]<0) dp[i][j]+=mod;}
				else dp[i][j]=sum[(n-(i-2))];
			}
			sum[0]=0;
			for(int j=1;j<=(n-(i-1));j++){
				sum[j]=sum[j-1]+dp[i][j];
				if(sum[j]>=mod) sum[j]-=mod;
			}
		}
		printf("%lld\n",sum[1]);
	}
	return 0;
}
