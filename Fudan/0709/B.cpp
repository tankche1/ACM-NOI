# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int dp[maxn][maxn];
int n;
char s1[maxn],s2[maxn];
int ans;

int main()
{
	int Tcase;
	scanf("%d",&Tcase);
	while(Tcase--){
		ans=0;
		scanf("%d",&n);
		scanf("%s",s1+1);scanf("%s",s2+1);
		memset(dp,0,sizeof(dp));
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(s1[i]-s2[j]<=1&&s1[i]-s2[j]>=-1){
					dp[i][j]=dp[i-1][j-1]+1;
					ans=max(ans,dp[i][j]);
				}
			}
		if(ans>=(n+1)/2) puts("POSITIVE");
			else puts("NEGATIVE");
	}
	return 0;
}
