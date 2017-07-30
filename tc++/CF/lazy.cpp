#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=410;
int n,k;
int a[maxn][maxn];
int sum[maxn][maxn];
int area[4][maxn][maxn];
int get(int a) {if(a<0) return 0;return a;}
int got(int a) {if(a>n) return n;return a;}
int main(){
	freopen("lazy.in","r",stdin);
	freopen("lazy.out","w",stdout);
	scanf("%d%d",&n,&k);k++;
	memset(sum,0,sizeof(sum));memset(a,0,sizeof(a));
	for(int i=1;i<=n;i++){sum[i][0]=0;
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]),sum[i][j]=sum[i][j-1]+a[i][j];
	}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			area[0][i][j]=0;
			for(int kk=1;kk<=k;kk++){
				area[0][i][j]+=sum[get(i-kk+1)][j]-sum[get(i-kk+1)][get(j-(k-kk+1))];
			}
		//	printf("area[0][%d][%d]:%d\n",i,j,area[0][i][j]);
		}
	
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			area[1][i][j]=0;
			for(int kk=1;kk<=k;kk++){
				area[1][i][j]+=sum[get(i-kk+1)][got(j+k-kk)]-sum[get(i-kk+1)][j-1];
			}
		}
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			area[2][i][j]=0;
			for(int kk=1;kk<=k;kk++)
				if(i+kk-1<=n)
				area[2][i][j]+=sum[i+kk-1][j]-sum[i+kk-1][get(j-k+kk-1)];
		}
		
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			area[3][i][j]=0;
			for(int kk=1;kk<=k;kk++)
				if(i+kk-1<=n)
				area[3][i][j]+=sum[i+kk-1][got(j+k-kk)]-sum[i+kk-1][j-1];
		}
		
		/*for(int p=0;p<4;p++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					printf("area[%d][%d][%d]:%d\n",p,i,j,area[p][i][j]);*/
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			int now=area[0][i][j]+area[1][i][j]+area[2][i][j]+area[3][i][j];
			for(int kk=1;kk<=k;kk++)
				now-=a[i-kk+1<0?0:i-kk+1][j]+a[i+kk-1>n?n+1:i+kk-1][j]+a[i][j-kk+1<0?0:j-kk+1]+a[i][j+kk-1>n?n+1:j+kk-1];
			now+=a[i][j];
			if(ans<now)
				ans=now;//printf("i:%d j:%d\n",i,j);
			//ans=max(ans,);
		}
	printf("%d\n",ans);
	return 0;
}
