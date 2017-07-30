# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=1000000007;
int n,m;
const int maxn=1010,maxm=55;
LL f[maxm][maxn],sum[maxm][maxn];
int main(){
	scanf("%d%d",&n,&m);
	memset(f,0,sizeof(f));
	memset(sum,0,sizeof(sum));
	int half=n%2==0?n/2-1:n/2;
	for(int j=1;j<=half;j++){
		f[1][j]=1;sum[1][j]=sum[1][j-1]+f[1][j];
	}
	for(int j=half+1;j<=n;j++) sum[1][j]=sum[1][j-1];
	for(int i=2;i<=m;i++){
		for(int j=i;j<=min(i*half,n);j++){
			f[i][j]=(mod+sum[i-1][j-1]-sum[i-1][max(j-half-1,0)])%mod;
			//printf("f[%d][%d]:%d\n",i,j,f[i][j]);
			sum[i][j]=(sum[i][j-1]+f[i][j])%mod;
		}
		for(int j=min(i*half,n)+1;j<=n;j++)
			sum[i][j]=sum[i][j-1];
	}
	LL ans=f[m][n];
	printf("%lld\n",ans);
	return 0;
}
