# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=13;
double eps=1e-12;
double A[13][13];
double a[13][13];
	

void Gaoss(int n){
	for(int i=0;i<n;i++){
		int r=i;
		double d=fabs(A[i][i]);
		for(int j=i+1;j<n;j++) if(fabs(A[j][i])>d) {r=j;d=fabs(A[j][i]);}
		if(r!=i) for(int j=0;j<=n;j++) swap(A[i][j],A[r][j]);
		for(int j=i+1;j<n;j++){
			double f=(double)A[j][i]/A[i][i];
			for(int k=i;k<=n;k++)
				A[j][k]-=f*A[i][k];
		}
	}
	for(int i=n-1;i>=0;i--){
		for(int j=i+1;j<n;j++)
			A[i][n]-=A[i][j]*A[j][n];
		A[i][n]/=A[i][i];
	}
}

int n;
int main(){
	scanf("%d",&n);
	for(int i=0;i<n+1;i++)
		for(int j=0;j<n;j++)
			scanf("%lf",&a[i][j]);
	for(int i=0;i<n;i++){
		A[i][n]=0.0;
		for(int j=0;j<n;j++){
			A[i][j]=2*(a[i][j]-a[i+1][j]);
			A[i][n]+=a[i][j]*a[i][j]-a[i+1][j]*a[i+1][j];
		}
	}
	Gaoss(n);
	printf("%.3lf",A[0][n]);
	for(int i=1;i<n;i++) printf(" %.3lf",A[i][n]);
		printf("\n");
	return 0;
}
