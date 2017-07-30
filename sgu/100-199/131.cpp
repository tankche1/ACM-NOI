# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
//dp[i][j] 表示i-1 已填完 第i行状态为j 
typedef long long LL;
LL dp[11][1<<9];
int m,n;
int maxstate;

inline void dfs(int row,int now,int next,LL num){
	//printf("now:%d next:%d\n",now,next);
	if(now==maxstate){
		dp[row+1][next]+=num;//printf("next:%d dp:%d\n",next,dp[row+1][next]);
		return;
	}
	for(int i=1;i<=n;i++)
		if(((now>>(n-i))&1)==0){
			//puts("fuck");
			if((i<n)&&(((now>>(n-(i+1)))&1)==0)){
				dfs(row,now|(1<<(n-i))|(1<<(n-(i+1))),next,num);
				if(((next>>(n-i))&1)==0) dfs(row,now|(1<<(n-i))|(1<<(n-(i+1))),next|(1<<(n-i)),num);
				if(((next>>(n-(i+1)))&1)==0) dfs(row,now|(1<<(n-i))|(1<<(n-(i+1))),next|(1<<(n-(i+1))),num);
			}
			if(((next>>(n-i))&1)==0){
				dfs(row,now|(1<<(n-i)),next|(1<<(n-i)),num);
				if((i>1)&&(((next>>(n-(i-1)))&1)==0)) dfs(row,now|(1<<(n-i)),next|(1<<(n-i))|(1<<(n-(i-1))),num);
				if((i<n)&&(((next>>(n-(i+1)))&1)==0)) dfs(row,now|(1<<(n-i)),next|(1<<(n-i))|(1<<(n-(i+1))),num);
			}
			break;
		}
}

int main(){
	scanf("%d%d",&m,&n);
	memset(dp,0,sizeof(dp));
	dp[1][0]=1;
	maxstate=(1<<n)-1;
	for(int i=1;i<=m;i++){
		for(int j=0;j<=maxstate;j++)
			if(dp[i][j]) 
				//printf("dp[%d][%d]:%d\n",i,j,dp[i][j]),
			dfs(i,j,0,dp[i][j]);
	}
	printf("%lld\n",dp[m+1][0]);
	return 0;
}
