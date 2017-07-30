# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

const int maxn=75;
int dp[2][1<<7][1<<7];
int maxstate;
int m,n;
int map[maxn];
char s[maxn][10];
inline bool check(int x) {for(int i=1;i<n;i++) if(((x>>(n-i))&1)==0&&((x>>(n-(i+1)))&1)==0) return 0;return 1;}
inline void dfs(int start,int pre,int now,int next,int want,int num){
	if(((pre|now)==maxstate)&&check(pre)&&check(now)){
		if(dp[want][now][next]==-1) dp[want][now][next]=num;
			else dp[want][now][next]=min(dp[want][now][next],num);
		//printf("now:%d next:%d dp:%d\n",now,next,dp[want][now][next]);
	}
	for(int i=start;i<=n;i++)
		if(((now>>(n-i))&1)==0){
			if((i<n)&&((now>>(n-(i+1)))&1)==0)
				dfs(i+2,pre,now|(1<<(n-i))|(1<<(n-(i+1))),next,want,num+1);
			if(((next>>(n-i))&1)==0)
				dfs(i+1,pre,now|(1<<(n-i)),next|(1<<(n-i)),want,num+1);
			if(((pre>>(n-i))&1)==1)
				continue;
			break;
		}
}

int main(){
	scanf("%d %d\n",&m,&n);
	maxstate=(1<<n)-1;
	for(int i=1;i<=m;i++)
		scanf("%s",s[i]);
	for(int i=1;i<=m;i++){
		map[i]=0;
		for(int j=0;j<n;j++)
			map[i]<<=1,map[i]+=s[i][j]=='*';
	}
	map[m+1]=maxstate;map[m+2]=maxstate;
	memset(dp,-1,sizeof(dp));
	dp[1][maxstate][map[1]]=0;
	for(int i=1;i<=m+1;i++){
		int now=(i%2);int next=!now;memset(dp[next],-1,sizeof(dp[next]));
		for(int j=0;j<=maxstate;j++) for(int k=0;k<=maxstate;k++){
			if(dp[now][j][k]!=-1){//printf("dp[%d][%d][%d]:%d\n",i,j,k,dp[now][j][k]);
				dfs(1,j,k,map[i+1],next,dp[now][j][k]);
			}
		}
	}
	m=(m+2)%2;/*int ans=INF;
	for(int j=0;j<=maxstate;j++)
		if((((j|(j>>1))==maxstate)||((j|(j<<1))==maxstate))&&dp[m][j][maxstate]<ans){
			ans=dp[m][j][maxstate];
		}*/
		printf("%d\n",dp[m][maxstate][maxstate]);
	return 0;
}
