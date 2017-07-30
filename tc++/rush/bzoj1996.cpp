#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int mod=19650827;
int n;
int A[maxn];
int dp[maxn][maxn][2];

int dfs(int l,int r,int d){
	if(dp[l][r][d]!=-1) return dp[l][r][d];
	if(l==r) return d==0;
	int &res=dp[l][r][d];res=0;
	if(d==0){
		if(A[l]<A[l+1]) res+=dfs(l+1,r,0);
		if(A[l]<A[r]) res+=dfs(l+1,r,1);
	}
	else{
		if(A[r]>A[l]) res+=dfs(l,r-1,0);
		if(A[r]>A[r-1]) res+=dfs(l,r-1,1);
	}
	res%=mod;
	return res;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	memset(dp,-1,sizeof(dp));
	printf("%d\n",(dfs(1,n,0)+dfs(1,n,1))%mod);
	return 0;
}
