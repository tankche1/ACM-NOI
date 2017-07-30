# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=200000000;
int A[maxn][maxn],f[maxn][maxn][2];//0 right 1 down
int m,n;

int update(int x,int to){
	if(x==-1||x>to) return to;
		else return x;
}
int main(){
	scanf("%d%d",&m,&n);
	memset(A,0,sizeof(A));
	memset(f,-1,sizeof(f));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			scanf("%d",&A[i][j]);
	f[1][1][0]=A[1][1]+A[1][2]+A[2][1];
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			for(int k=0;k<=1;k++){
				if(f[i][j][k]==-1) continue;
			//right
			if(j<n) {
				if(k==0) f[i][j+1][0]=update(f[i][j+1][0],A[i-1][j+1]+A[i][j+2]+A[i+1][j+1]+f[i][j][0]);
					else f[i][j+1][0]=update(f[i][j+1][0],A[i+1][j+1]+A[i][j+2]+f[i][j][1]);
			}
			//down
			if(i<m){
				if(k==0) f[i+1][j][1]=update(f[i+1][j][1],A[i+1][j+1]+A[i+2][j]+f[i][j][0]);
					else f[i+1][j][1]=update(f[i+1][j][1],A[i+1][j-1]+A[i+1][j+1]+A[i+2][j]+f[i][j][1]);
			}
			//printf("f[%d][%d][%d]:%d\n",i,j,k,f[i][j][k]);
		}
		int ans=min(f[m][n][0],f[m][n][1]);
		printf("%d\n",ans);
	return 0;
}
/*
3 3
2 2 2
1 1 1
1 1 1
*/
