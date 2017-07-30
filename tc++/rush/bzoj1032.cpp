# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=505;
const int INF=~0U>>1;
int dp[maxn][maxn];
int a[maxn],n;
int left[maxn],right[maxn];//

int Dfs(int l,int r){
	if(r==l) return 2;
	if(r-l==1) {return a[l]==a[r]?1:4;}
	if(dp[l][r]!=-1) return dp[l][r];
	int &ans=dp[l][r];ans=INF;
	if(a[l]==a[r]){
		if(right[l]>=r) return ans=1;
		ans=min(ans,Dfs(right[l]+1,left[r]-1)+((right[l]-l+1+r-left[r]+1)>2?0:1));
	//	printf("l:%d r:%d ans:%d ll:%d rr:%dfuck\n",l,r,ans,right[l]+1,left[r]-1);
	}
	for(int k=l;k<r;k++)
		ans=min(ans,Dfs(l,k)+Dfs(k+1,r));
	//printf("dp[%d][%d]:%d\n",l,r,ans);
	return ans;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	memset(dp,-1,sizeof(dp));
	left[0]=-1;right[n+1]=-1;
	for(int i=1;i<=n;i++)
		left[i]=a[i]==a[i-1]?left[i-1]:i;
	for(int i=n;i>=1;i--)
		right[i]=a[i]==a[i+1]?right[i+1]:i;
	printf("%d\n",Dfs(1,n));
	return 0;
}
