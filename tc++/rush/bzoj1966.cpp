# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=505;
int n,m;
char A[maxn],B[maxm];
bool dp[maxn][maxm];
int q,ans=0;
int main(){
	scanf("%s",A);
	n=strlen(A);
	scanf("%d",&q);
	while(q--){
		scanf("%s",B);m=strlen(B);
		memset(dp,0,sizeof(dp));dp[0][0]=1;
		for(int i=1;i<=n;i++){
			if(A[i-1]=='*') dp[i][0]=dp[i-1][0];
			for(int j=1;j<=m;j++){
				if(A[i-1]=='*') dp[i][j]=dp[i][j-1]|dp[i-1][j];
				else if(A[i-1]=='?') dp[i][j]=dp[i-1][j-1];
				else dp[i][j]=A[i-1]==B[j-1]?dp[i-1][j-1]:0;
		}
	}
		ans+=dp[n][m]^1;
	}
	printf("%d\n",ans);
	return 0;
}
