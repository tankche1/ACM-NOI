#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int dp[2][4][4][4][4];
int A[maxn];
bool vis[4];
void update(int &x,int y){
	x=max(x,y);
}
int main(){
	char t;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		while((t=getchar())&&t!='B'&&t!='M'&&t!='F');
		A[i]=t=='B'?1:t=='M'?2:3;
		//printf("A[%d]:%d\n",i,A[i]);
	}
	memset(dp,-1,sizeof(dp));dp[0][0][0][0][0]=0;
	//for(int i=1;i<=n;i++) printf("A[%d]:%d\n",i,A[i]);
	for(int i=0;i<n;i++){
		int now=i%2;int next=now^1;//for(int i=1;i<=n;i++) printf("A[%d]:%d\n",i,A[i]);
		memset(dp[next],-1,sizeof(dp[next]));
		for(int j=0;j<4;j++)
			for(int k=0;k<4;k++)
				for(int x=0;x<4;x++)
					for(int y=0;y<4;y++){
						if(dp[now][j][k][x][y]!=-1){
							//printf("i:%d now:%d next:%d A[i+1]:%d\n",i,now,next,A[i+1] );
							//printf("dp[%d][%d][%d][%d][%d]:%d\n",i,j,k,x,y,dp[now][j][k][x][y]);
							memset(vis,false,sizeof(vis));
							vis[j]=vis[k]=vis[A[i+1]]=1;
							int num=0;
							for(int p=1;p<=3;p++) num+=vis[p];
							update(dp[next][A[i+1]][j][x][y],dp[now][j][k][x][y]+num);
							//printf("godp[%d][%d][%d][%d][%d]:%d\n",next,A[i+1],j,x,y,dp[next][A[i+1]][j][x][y]);
							memset(vis,false,sizeof(vis));
							vis[x]=vis[y]=vis[A[i+1]]=1;num=0;
							for(int p=1;p<=3;p++) num+=vis[p];
							update(dp[next][j][k][A[i+1]][x],dp[now][j][k][x][y]+num);
							//printf("godp[%d][%d][%d][%d][%d]:%d\n",next,i,j,A[i+1],x,dp[next][i][j][A[i+1]][x]);
						}
					}
	}
	int ans=0;
	for(int j=0;j<4;j++)
			for(int k=0;k<4;k++)
				for(int x=0;x<4;x++)
					for(int y=0;y<4;y++)
						ans=max(ans,dp[n%2][j][k][x][y]);
					printf("%d\n",ans);
	return 0;
}
