# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=4205;
int f[2][maxn][2];//0表示下一个下降
int n,mod;
int main(){
	scanf("%d%d",&n,&mod);
	if(n==1) {printf("%d\n",1%mod);return 0;}
	memset(f,0,sizeof(f));
	for(int i=0;i<n;i++)
		f[1][i][0]=f[1][i][1]=1;
	for(int i=1;i<n;i++){
		int now=i%2;int next=!now;
		memset(f[next],0,sizeof(f[next]));
		int sum=0;
		for(int j=n-i;j>0;j--){
			sum+=f[now][j][0];if(sum>=mod) sum%=mod;
			f[next][j-1][1]=sum;
			//printf("f[%d][%d][%d]:%d\n",i+1,j-1,1,f[next][j-1][1]);
		}
		sum=0;
		for(int j=0;j<n-i;j++){
			sum+=f[now][j][1];if(sum>=mod) sum%=mod;
			f[next][j][0]=sum;
			//printf("f[%d][%d][%d]:%d\n",i+1,j,0,f[next][j][0]);
		}
	}
	int ans=0;
	for(int i=0;i<n;i++)
		ans=(ans+(f[n%2][i][0]+f[n%2][i][1])%mod)%mod;
	printf("%d\n",ans%mod);
	return 0;
}
