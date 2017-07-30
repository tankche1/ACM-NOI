//f[i][j]=min(f[i-1][k]+abs(a[i]-b[j]))
# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=2010;
const int INF=~0U>>1;
int n;
int a[maxn],b[maxn];
LL f[maxn][maxn],g[maxn][maxn];
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d",&a[i]);b[i]=a[i];
	}
	sort(b+1,b+n+1);
	int cnt=unique(b+1,b+n+1)-(b+1);
	memset(f,0,sizeof(f));memset(g,0,sizeof(g));
	for(int i=1;i<=n;i++){
		g[i][0]=INF;
		for(int j=1;j<=cnt;j++){
			f[i][j]=g[i-1][j]+abs(a[i]-b[j]);
			g[i][j]=min(g[i][j-1],f[i][j]);
			//printf("f[%d][%d]:%d g:%d\n",i,j,f[i][j],g[i][j]);
		}
	}
	LL ans=g[n][cnt];
	for(int i=1;i<=n;i++){
		g[i][cnt+1]=INF;
		for(int j=cnt;j>=1;j--){
			f[i][j]=g[i-1][j]+abs(a[i]-b[j]);
			g[i][j]=min(g[i][j+1],f[i][j]);
		}
	}
	ans=min(ans,g[n][1]);
	printf("%lld\n",ans);
	return 0;
}
