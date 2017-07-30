# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
int n,k;
int s[110];
int dp[105][105][6];
int dfs(int l,int r,int t){
	if(t>k) t=k;
	int &res=dp[l][r][t];
	if(res!=-1) return res;
	if(l==r) return res=k-t;
	res=INF;
	if(s[l]==s[l+1]) return res=min(res,dfs(l+1,r,t+1));
	res=min(res,dfs(l+1,r,1)+k-t);//消掉
	for(int p=l+1;p<=r;p++)
		if(s[l]==s[p])
			res=min(res,dfs(l+1,p-1,1)+dfs(p,r,t+1));//不一起消
	return res;
}

int main(){
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)
		scanf("%d",&s[i]);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(1,n,1));
	return 0;
}
