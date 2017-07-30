#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=45;
typedef long long LL;
int m,n;
LL A[maxn][maxn];
LL B[maxn];
int a[maxn][maxn];
int ans[maxn][maxn];
int x[maxn];

void gaoss(int n){
	memset(x,0,sizeof(x));
	for(int i=1;i<=n;i++){
		int t=i;
		for(int j=i;j<=n;j++)
			if(a[j][i]==1)
				t=j;
		if(a[t][i]==0) {x[i]=1;continue;}
		if(t!=i) for(int j=1;j<=n+1;j++) swap(a[i][j],a[t][j]);
		for(int j=i+1;j<=n;j++){
				if(a[j][i])
				for(int l=1;l<=n+1;l++)
					a[j][l]^=a[i][l];
		}
	}
	for(int i=n;i>=1;i--){
		if(!x[i]){
			for(int j=i+1;j<=n;j++)
				if(a[i][j])
				x[i]^=x[j];
		}
	}
}

int main(){
	scanf("%d%d",&m,&n);
	memset(A,0,sizeof(A));
	for(int j=1;j<=n;j++) A[1][j]=(LL)1<<(j-1);
	for(int i=2;i<=m+1;i++)
		for(int j=1;j<=n;j++){
			A[i][j]=A[i-1][j]^A[i-2][j]^A[i-1][j-1]^A[i-1][j+1];
			//printf("A[%d][%d]:%lld\n",i,j,A[i][j]);
		}
	for(int j=1;j<=n;j++)
		B[j]=A[m+1][j];//printf("B[%d]:%lld\n",j,B[j]);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			a[i][j]=((B[i]>>(j-1))&1);
			//printf("a[%d][%d]:%d\n",i,j,a[i][j]);
		}
		a[i][n+1]=0;
	}
	gaoss(n);
	memset(ans,0,sizeof(ans));
	for(int j=1;j<=n;j++)
		ans[1][j]=x[j];
	for(int i=2;i<=m;i++)
		for(int j=1;j<=n;j++)
			ans[i][j]=ans[i-1][j]^ans[i-1][j-1]^ans[i-1][j+1]^ans[i-2][j];
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)
			printf("%d%c",ans[i][j],j!=n?' ':'\n');
	}
	return 0;
}
