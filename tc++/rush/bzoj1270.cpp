# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2005;
int n,h,delta;
int floor[maxn<<1];
int dp[maxn][maxn];
int A[maxn][maxn];
int main(){
	scanf("%d%d%d",&n,&h,&delta);
	memset(A,0,sizeof(A));memset(floor,0,sizeof(floor));
	for(int i=1;i<=n;i++){
		int num,x;
		scanf("%d",&num);
		while(num--){
			scanf("%d",&x);A[i][x]++;
		}
	}
	for(int i=1;i<=n;i++) dp[i][h]=A[i][h],floor[h]=max(floor[h],dp[i][h]);
	for(int nowh=h-1;nowh>=1;nowh--){
		for(int i=1;i<=n;i++){
			dp[i][nowh]=max(dp[i][nowh+1],floor[nowh+delta])+A[i][nowh];
			floor[nowh]=max(floor[nowh],dp[i][nowh]);
			//printf("dp[%d][%d]:%d\n",i,nowh,dp[i][nowh]);
		}
	}
	printf("%d\n",floor[1]);
	return 0;
}
/*
3 10 2
3 1 4 10
6 3 5 9 7 8 9
5 4 5 3 6 9
*/
