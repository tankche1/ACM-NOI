# include<stdio.h>
# include<algorithm>
using namespace std;
const int maxn=100010;

int l0,l1,s0,s1,n;
int pass[maxn][2],dribble[maxn][2];
int dp[maxn][2];
int main()
{
	int tcase,other,ans;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d%d%d",&n,&l0,&l1,&s0,&s1);
		for(int st=0;st<=1;st++){
			for(int i=1;i<n;i++)
				scanf("%d",&pass[i][st]);
			for(int i=1;i<n;i++)
				scanf("%d",&dribble[i][st]);
		}
		dp[1][0]=l0;dp[1][1]=l1;
		for(int i=2;i<=n;i++){
			for(int st=0;st<=1;st++){
				other=1-st;
				dp[i][st]=min(dp[i-1][st]+dribble[i-1][st],dp[i-1][other]+pass[i-1][other]);
			}
			//printf("i:%d\n",i);
		}
		ans=min(dp[n][0]+s0,dp[n][1]+s1);
		printf("%d\n",ans);
	}
	
	return 0;
}
