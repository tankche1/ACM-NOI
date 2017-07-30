# include<stdio.h>
# include<string.h>
# include<algorithm>
# define tot(x,y) sum[a][b]-sum[x-1][b]-sum[a][y-1]+sum[x-1][y-1]
using namespace std;
const int maxn=20;

int a,b,n;
int dp[maxn][maxn][maxn],sum[maxn][maxn];
int main(){
	int x;
	scanf("%d%d%d",&a,&b,&n);
	memset(sum,0,sizeof(sum));
	for(int i=1;i<=a;i++)
		for(int j=1;j<=b;j++){
			scanf("%d",&x);
			sum[i][j]=sum[i-1][j]+sum[i][j-1]-sum[i-1][j-1]+a;
		}
	return 0;
}
