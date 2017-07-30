# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int dp[2][11];
int mod=2007;
typedef int Matrix[11][11];
Matrix A,C;

void Copy(Matrix A,Matrix B){
	for(int i=1;i<=10;i++)
		for(int j=1;j<=10;j++)
			A[i][j]=B[i][j];
}

void Matrix_mul(Matrix A,Matrix B,Matrix ans){
	for(int i=1;i<=10;i++)
		for(int j=1;j<=10;j++){
			C[i][j]=0;
			for(int k=1;k<=10;k++)
				C[i][j]+=A[i][k]*B[k][j];
			C[i][j]%=mod;
		}
	Copy(ans,C);
}

void Matrix_pow(Matrix A,int p,Matrix ans){
	if(p==1) {Copy(ans,A);return;}
	Matrix half;
	//printf("p:%d\n",p);
	Matrix_pow(A,p/2,half);
	/*puts("half:");
	for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++)
			printf("%d ",half[i][j]);puts("");}*/
	//		puts("////");
	Matrix_mul(half,half,ans);
	/*		for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++)
			printf("%d ",ans[i][j]);puts("");}
			puts("ans");*/
	if(p&1) Matrix_mul(A,ans,ans);
	return;
}

int main()
{
	memset(dp,0,sizeof(dp));
	dp[1][1]=1;
	int n,m;
	scanf("%d%d",&n,&m);
	if(n==1) {puts("1");return 0;}
	memset(A,0,sizeof(A));//memset(B,0,sizeof(B));
	for(int i=1;i<=10;i++){
		A[i][i]=i;A[i-1][i]=1;
	}
	Matrix Ans;
	/*for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++)
			printf("%d ",A[i][j]);puts("");}*/
	Matrix_pow(A,n-1,Ans);
	/*for(int i=1;i<=10;i++){
		for(int j=1;j<=10;j++)
			printf("%d ",Ans[i][j]);puts("");}*/
	
	/*for(int i=2;i<=n;i++){
		now=i%2;last=now^1;
		for(int j=1;j<=10;j++){
			dp[now][j]=(dp[last][j]*j+dp[last][j-1]);
			if(dp[now][j]) printf("dp[%d][%d]:%d\n",i,j,dp[now][j]);
			}
		}*/
	printf("%d\n",Ans[1][m]);
	return 0;
}
