# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxl=15;
LL a,b;
LL dp[maxl][10][10];//
LL power[maxl];

void Dp(){
	LL sum[10];memset(sum,0,sizeof(sum));power[0]=1;sum[0]=1;
	for(int i=1;i<maxl;i++) power[i]=power[i-1]*10;
	for(int i=1;i<=13;i++){
		for(int k=0;k<10;k++)
			dp[i][0][k]=sum[k];
		//memset(sum,0,sizeof(sum));
		for(int j=0;j<10;j++){
			for(int k=0;k<10;k++){
				dp[i][j][k]=0;
				for(int l=0;l<10;l++)
					dp[i][j][k]+=dp[i-1][l][k];
				if(k==j) dp[i][j][k]+=power[i-1];
				//sum[k]+=dp[i][j][k];
				//printf("%d %d %d %lld\n",i,j,k,dp[i][j][k]);
			}
		}
	}
}

LL sum[13],ans[13];

void Count(LL x){
	bool first=false;
	LL xx=x;
	memset(sum,0,sizeof(sum));
	for(int i=maxl-2;i>=1;i--){
		if(x/power[i-1]>0||first){
			first=true;
			int num=x/power[i-1];
			for(int k=0;k<10;k++)
			for(int j=0;j<num;j++){
				sum[k]+=dp[i][j][k];
			}
			sum[num]+=x-power[i-1]*(num)+1;
			x-=power[i-1]*num;
		}
	}
	for(int i=maxl-2;i>=1;i--)
		if(xx/power[i-1]>0){
			for(int j=i;j>=1;j--)
				sum[0]-=power[j-1];
			break;
		}
}

int main(){
	Dp();
	scanf("%lld %lld",&a,&b);
	Count(b);memcpy(ans,sum,sizeof(sum));
	Count(a-1);
	printf("%lld",ans[0]-sum[0]);
	for(int i=1;i<10;i++) printf(" %lld",ans[i]-sum[i]);puts("");
	return 0;
}
