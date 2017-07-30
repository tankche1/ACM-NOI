# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=9;
typedef long long LL;
bool deliver[1<<maxn][1<<maxn];
int Count[1<<maxn];
int n,K;

void prepare(){
	memset(deliver,false,sizeof(deliver));
	for(int i=0;i<(1<<n);i++){
		if(((i<<1)&i)!=0) continue;
		for(int j=i;j<(1<<n);j++){
			//printf("i:%d j:%d i&j:%d %d %d\n",i,j,i&j,(i<<1)&j,(i>>1)&j);
			if((((j<<1)&j)==0)&&((i&j)==0)&&(((i<<1)&j)==0)&&(((i>>1)&j)==0))
				deliver[i][j]=deliver[j][i]=true;//printf("i:%d j:%d\n",i,j);
		}
		Count[i]=0;
		for(int j=1;j<=i;j<<=1)
			if(i&j) Count[i]++;
			//	printf("Count[%d]:%d\n",i,Count[i]);
	}
}
LL dp[maxn+1][maxn*maxn+1][1<<maxn];

int main(){
	scanf("%d%d",&n,&K);
	prepare();
	memset(dp,0,sizeof(dp));
	dp[0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int k=0;k<=K;k++){
			for(int j=0;j<(1<<n);j++){
				if(dp[i][k][j]){
					//printf("dp[%d][%d][%d]:%d\n",i,k,j,dp[i][k][j]);
					for(int next=0;next<(1<<n);next++){
						if(deliver[j][next]&&k+Count[next]<=K){
							//printf("next : dp[%d][%d][%d]\n",i+1,k+Count[next],next);
							dp[i+1][k+Count[next]][next]+=dp[i][k][j];
						}
					}
				}
			}
		}
	}
	LL ans=0;
	for(int j=0;j<(1<<n);j++)
		ans+=dp[n][K][j];
	printf("%lld\n",ans);
	return 0;
}
