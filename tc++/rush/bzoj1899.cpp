#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=202;
const int INF=~0U>>1;
void update(int &x,int y){
	if(x==-1||y<x) x=y;
}
int dp[2][maxn*maxn];
int n;
struct state{
	int A,B;
};
state people[maxn];
bool cmp(state a,state b){
	return a.B>b.B;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&people[i].A,&people[i].B);
	sort(people+1,people+n+1,cmp);
	memset(dp,-1,sizeof(dp));
	dp[1][0]=0;
	int sum=0;
	for(int i=1;i<=n;i++){
		int now=i&1;int next=!now;
		memset(dp[next],-1,sizeof(dp[next]));
		for(int j=0;j<=sum;j++)
			if(dp[now][j]!=-1){
				//printf("dp[%d][%d]:%d\n",i,j,dp[now][j]);
				update(dp[next][j],max(dp[now][j],sum-j+people[i].A+people[i].B));
				update(dp[next][j+people[i].A],max(dp[now][j],j+people[i].A+people[i].B));
			}
		sum+=people[i].A;
	}
	int ans=INF;
	for(int i=0;i<=sum;i++)
		if(dp[(n+1)&1][i]!=-1) ans=min(ans,dp[(n+1)&1][i]);//printf("dp[%d][%d]:%d,ans:%d \n",(n+1),i,dp[(n+1)&1][i],ans);
	printf("%d\n",ans);
	return 0;
}
