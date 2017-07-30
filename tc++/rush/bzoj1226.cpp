#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=~0U>>2;
int B[maxn],T[maxn];
int n;
int dp[maxn][1<<8][17];
inline int cal(int i,int j){
	//return (T[i]|T[j])-(T[i]&T[j]);
	return T[i]^T[j];
}

void update(int &x,int y){
	if(x==-1) x=y;
		else
	x=min(x,y);
}

int main(){
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		int maxs=1<<8;
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%d%d",&T[i],&B[i]);
		memset(dp,-1,sizeof(dp));
		int _min=1+B[1];
		for(int i=2;i<=min(n,_min);i++){
			_min=min(_min,i+B[i]);
			dp[1][1<<(i-1)][i-1+8]=0;
		}//printf("_min:%d\n",_min);
		dp[2][0][-1+8]=0;
		for(int i=1;i<=n;i++){
			for(int j=0;j<maxs;j++)
				for(int k=-8;k<=7;k++)
					if(dp[i][j][k+8]!=-1){
						//printf("dp[%d][%d][%d]:%d\n",i,j,k,dp[i][j][k+8]);
						//if(j&1) {puts("fuck");return 0;}
						int state=j|1;
						int t=0;
						while(state&(1<<t)) t++;t--;
						update(dp[i+t+1][j>>(t+1)][-t-1+8],dp[i][j][k+8]+cal(i+k,i));
						int _min=i+B[i];
						for(int l=i+1;l<=min(n,_min);l++){
							if((j&(1<<(l-i)))==0){
								_min=min(_min,l+B[l]);
								//if(l==8&&i==1)
								//printf("l:%d ",l);
								update(dp[i][j|(1<<(l-i))][l-i+8],dp[i][j][k+8]+cal(i+k,l));
							}
						}//puts("");
					}
		}
		int ans=INF;
		for(int i=-8;i<0;i++)
			if(dp[n+1][0][i+8]!=-1) ans=min(ans,dp[n+1][0][i+8]);
		printf("%d\n",ans);
	}
	return 0;
}
