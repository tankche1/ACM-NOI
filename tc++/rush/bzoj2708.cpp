#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=60;
int n;
int p[maxn];
int dp[maxn],cost[maxn][maxn];

int match(int L,int R){
	int ans=0;
	if(p[R]-p[L]<=1) return 0;
	for(int k=1;k*2<=R-L+1;k++){
		bool ok=true;
		if(p[R-k+1]-p[L+k-1]<=1) {ok=false;break;}
		for(int i=L+k;i<=R;i++)
			if(p[i]-p[i-k]>1) {ok=false;break;}
		if(ok) ans=k;
		else break;
	}
	return ans;
}

int main(){
	while(scanf("%d",&n)==1){
		for(int i=1;i<=n;i++) scanf("%d",&p[i]);
		sort(p+1,p+n+1);
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
				cost[i][j]=match(i,j);
		dp[0]=0;
		for(int i=1;i<=n;i++){
			dp[i]=0;
			for(int j=0;j<i;j++)
				dp[i]=max(dp[i],dp[j]+cost[j+1][i]);
		}
		printf("%d\n",dp[n]);
	}
	return 0;
}
