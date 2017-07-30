# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=200010;
LL dp[70][maxn];
int maxbit=61;
int n;
LL a[maxn],b[maxn];
int one[70],zero[70];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%I64d",&a[i]);
		while(a[i]<=((long long)1<<maxbit)) maxbit--;
	}maxbit=61;
	memset(one,0,sizeof(one));memset(zero,0,sizeof(zero));
	for(int i=1;i<=n;i++){
		for(int j=1;j<=maxbit;j++){
			if((a[i]>>(j-1))&1) one[j]++;
			else zero[j]++;
		}
	}
	memset(dp,0,sizeof(dp));
	dp[0][0]=1;
	int s0,s1,top,jw;
	for(int i=0;i<=maxbit;i++){
			
		s0=zero[i+1];s1=one[i+1];jw=0;
		for(int j=0;j<=n;j++){
			if(j){//要退位
				int t=((a[j])>>(i))&1;
				if(t) s1--,s0++;
				else s0--,s1++,jw++;
			}
			//printf("dp[%d ][%d]:%I64d\n",i,j,dp[i][j]);
			if(dp[i][j]==0) continue;
			if(!(s1&1)) dp[i+1][jw]+=dp[i][j];//选0
			if(!(s0&1)) dp[i+1][s0+jw]+=dp[i][j];//选1
		}
			//排序
		top=0;
		for(int j=1;j<=n;j++)
			if(!((a[j]>>i)&1)) b[++top]=a[j];
		for(int j=1;j<=n;j++)
			if(((a[j]>>i)&1)) b[++top]=a[j];
		for(int j=1;j<=n;j++) a[j]=b[j];
	}
	long long sg=0;
	for(int i=1;i<=n;i++) sg^=(a[i]-a[1]);
	if(!sg) dp[maxbit][0]--;
	printf("%I64d\n",dp[maxbit][0]);
	return 0;
}
