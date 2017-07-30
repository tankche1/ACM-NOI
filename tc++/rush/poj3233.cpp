# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=31;
//typedef int Matrix[maxn][maxn];
int n,k,mod;
struct Matrix{
	int A[maxn][maxn];
};

Matrix matrix_add(Matrix A,Matrix B){
	Matrix C;
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
			C.A[i][j]=(A.A[i][j]+B.A[i][j])%mod;
	return C;
}

Matrix matrix_mul(Matrix A,Matrix B){
	Matrix C;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			C.A[i][j]=0;
			for(int k=0;k<n;k++)
				C.A[i][j]=(C.A[i][j]+A.A[i][k]*B.A[k][j])%mod;
		}
	}
	return C;
}

Matrix matrix_pow(Matrix A,int x){
	if(x==1) return A;
	Matrix B=matrix_pow(A,x/2);
	B=matrix_mul(B,B);
	if(x%2==1) B=matrix_mul(B,A);
	return B;
}

Matrix B,C;
void get_sum(Matrix A,int k,Matrix& ret){
	if(k==1){
		for(int i=0;i<n;i++) for(int j=0;j<n;j++) ret.A[i][j]=A.A[i][j];return;
	}
	if(k&1){
		int M=k/2+1;
		get_sum(A,M-1,B);
		C=matrix_pow(A,M);
		ret=matrix_add(B,matrix_mul(B,C));
		ret=matrix_add(ret,C);
	}
	else{
		int M=k/2;
		get_sum(A,M,B);
		C=matrix_pow(A,M);
		ret=matrix_add(B,matrix_mul(B,C));
	}
}

Matrix A,ans;
int main(){
	scanf("%d%d%d",&n,&k,&mod);
	for(int i=0;i<n;i++)
		for(int j=0;j<n;j++)
		{scanf("%d",&A.A[i][j]);A.A[i][j]=A.A[i][j]%mod;}
	get_sum(A,k,ans);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			if(j!=0) printf(" ");
			printf("%d",ans.A[i][j]);
		}
		printf("\n");
	}
	return 0;
}

