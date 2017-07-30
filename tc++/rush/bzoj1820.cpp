# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=205;
const int INF=~0U>>1;
int n;
int d[maxn][maxn];
int dp[2][maxn][maxn];
int s[1010],m;

int Min(int a,int b){
	if(a==-1||b<a) return b;
		return a;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&d[i][j]);
	m=0;int x;
	while(scanf("%d",&x)!=EOF){
		s[++m]=x;
	}
	s[0]=1;
	int now=1,next;
	memset(dp[0],-1,sizeof(dp[0]));
	dp[0][2][3]=0;
	for(int i=0;i<m;i++){
		now=!now;next=!now;
		memset(dp[next],-1,sizeof(dp[next]));
		for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
			if(dp[now][j][k]!=-1){
				dp[next][j][k]=Min(dp[next][j][k],dp[now][j][k]+d[s[i]][s[i+1]]);
				dp[next][s[i]][k]=Min(dp[next][s[i]][k],dp[now][j][k]+d[j][s[i+1]]);
				dp[next][s[i]][j]=Min(dp[next][s[i]][j],dp[now][j][k]+d[k][s[i+1]]);
			}
	}
	int ans=INF;
	for(int j=1;j<=n;j++)
			for(int k=1;k<=n;k++)
				if(dp[next][j][k]!=-1)
					ans=min(ans,dp[next][j][k]);
				printf("%d\n",ans);
	return 0;
}
