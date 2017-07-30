# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=105;
int n,m,t;
char s[maxn][maxn];
int dp[17][maxn][maxn];
int stx,sty,edx,edy;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int main(){
	scanf("%d%d%d",&n,&m,&t);
	for(int i=1;i<=n;i++)
		scanf("%s",s[i]+1);
	scanf("%d%d%d%d",&stx,&sty,&edx,&edy);
	memset(dp,0,sizeof(dp));
	dp[0][stx][sty]=1;
	for(int tt=0;tt<t;tt++){
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(dp[tt][i][j]){
					for(int k=0;k<4;k++){
						int x=i+dx[k],y=j+dy[k];
						//printf("x:%d y:%d\n",x,y);
						if(s[x][y]!='.') continue;//printf("x:%d y:%d\n",x,y);
						dp[tt+1][x][y]+=dp[tt][i][j];
					}
					//printf("dp[%d][%d][%d]:%d\n",tt,i,j,dp[tt][i][j]);
				}
			}
	}
	printf("%d\n",dp[t][edx][edy]);
	return 0;
}
