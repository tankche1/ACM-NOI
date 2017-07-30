# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=110;
const int INF=~0U>>1;
LL f[maxn][maxn],g[maxn][maxn];
LL n,m;
int main(){
	LL a,b,c;
	scanf("%lld%lld",&n,&m);
	for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=INF;
		for(int i=1;i<=n;i++) f[i][i]=g[i][i]=1;
	for(int i=1;i<=m;i++){
		scanf("%lld%lld%lld",&a,&b,&c);
		f[a][b]=f[b][a]=c;
		g[a][b]=g[b][a]=1;
	}
	for(int k=1;k<=n;k++)
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				if(f[i][k]<f[i][j]-f[k][j]){
					f[i][j]=f[i][k]+f[k][j];
					g[i][j]=g[i][k]*g[k][j];
				}
				else if(f[i][k]==f[i][j]-f[k][j]){
					g[i][j]+=g[i][k]*g[k][j];
				}
			}
		/*	for(int i=1;i<=n;i++)
				for(int j=i+1;j<=n;j++)
					printf("i:%d j:%d f:%d g:%d\n",i,j,f[i][j],g[i][j]);*/
	for(int i=1;i<=n;i++){
		double ans=0;
		for(int j=1;j<=n;j++)
			for(int k=j+1;k<=n;k++){
				if(i==j||i==k) continue;
				if(f[j][i]==f[j][k]-f[i][k]){
					ans+=(g[j][i]*g[i][k])/(g[j][k]*1.0);
						//printf("%d %d %d\n",g[j][i],g[i][k],g[j][k]);
				}
			}
			printf("%.3lf\n",ans*2);
	}
	return 0;
}
