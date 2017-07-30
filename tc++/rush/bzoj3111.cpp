#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=105;
const int INF=3*(1e+8);
int f[2][maxn][maxn][maxn],_max[2][maxn][maxn][maxn];
int sum[maxn][maxn],A[maxn][maxn];
int n,m,K;
int main(){
	scanf("%d%d%d",&n,&m,&K);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&A[i][j]);
	for(int j=1;j<=m;j++){
		sum[0][j]=0;
		for(int i=1;i<=n;i++)
			sum[i][j]=sum[i-1][j]+A[i][j];//printf("sum[%d][%d]:%d\n",i,j,sum[i][j]);
	}
	//memset(f[0],0,sizeof(f[0]));
	for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) for(int l=0;l<=n+1;l++) {_max[1][i][j][l]=-INF;f[1][i][j][l]=-INF;}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			for(int l=0;l<i;l++){
				f[1][i][j][l]=max(f[1][i][j-1][l],0)+sum[i][j]-sum[l][j];
			//	printf("f[%d][%d][%d][%d]:%d\n",1,i,j,l,f[1][i][j][l]);
			}
			for(int l=1;l<=n;l++)
					_max[1][i][j][l]=max(_max[1][i][j][l-1],f[1][i][j][l-1]);
		}
	for(int k=2;k<=2*K+1;k++){
		int now=k&1;int last=now^1;
		//memset(f[now],0,sizeof(f[now]));
		for(int i=0;i<=n+1;i++) for(int j=0;j<=m+1;j++) for(int l=0;l<=n+1;l++) {_max[now][i][j][l]=-INF;f[now][i][j][l]=-INF;}
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				for(int l=0;l<i;l++){
					f[now][i][j][l]=max(f[now][i][j][l],f[now][i][j-1][l]+sum[i][j]-sum[l][j]);
					f[now][i][j][l]=max(f[now][i][j][l],_max[last][i][j-1][l]+sum[i][j]-sum[l][j]);
				//	printf("f[%d][%d][%d][%d]:%d\n",k,i,j,l,f[now][i][j][l]);
				}
				if(k&1){
					for(int l=1;l<=n;l++)
						_max[now][i][j][l]=max(_max[now][i][j][l-1],f[now][i][j][l-1]);
				}
				else{
					for(int l=i-2;l>=0;l--){
						_max[now][i][j][l]=max(_max[now][i][j][l+1],f[now][i][j][l+1]);
					}
				}
			}
	}
	int ans=-INF;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int l=0;l<i;l++)
				ans=max(ans,f[1][i][j][l]);
	printf("%d\n",ans);
	return 0;
}
/*
2 5 2
-1 -1 -1 -1 -1 
-1 -1 -1 -1 -1

3 3 1
-1 -1 1
1 -1 1
1 1 1
*/
