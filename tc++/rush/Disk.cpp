#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=~0U>>1;
typedef pair<int,int> pi;
int n,L,ans=0;
int pos[maxn];
//queue<pi> Q;
int f[maxn][maxn],d[maxn][maxn];
int main(){
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);n++;pos[1]=0;
		for(int i=2;i<=n;i++)
			scanf("%d%d",&L,&pos[i]);
		ans=L*400*2+(n-1)*10;
		for(int i=1;i<=n;i++)
			for(int j=i;j<=n;j++)
				d[i][j]=d[j][i]=min(abs(pos[i]-pos[j]),360-abs(pos[i]-pos[j]));
		for(int i=1;i<=n;i++) for(int j=1;j<=n;j++) f[i][j]=INF;
		f[1][1]=0;
		for(int i=1;i<=n;i++){
			for(int k=1;k<i;k++)
				f[i][i]=min(f[k][i]+d[k][i],f[i][i]);
			if(i!=n)
			for(int k=1;k<=i;k++)
				f[i][i+1]=min(f[i][i+1],f[k][i]+d[k][i+1]);
			for(int j=i+2;j<=n;j++)
				f[i][j]=min(f[i][j],f[i][j-1]+d[j-1][j]);
		}
		printf("%d\n",f[n][n]+ans);
	}
	return 0;
}
/*
100
8
1 20
2 50
3 40
4 70
5 55
6 80
7 10
8 100

*/
