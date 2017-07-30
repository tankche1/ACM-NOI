# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
int mod=107;

typedef long long LL;
const int maxl=2;
typedef LL Matrix[3][3];
typedef LL Vector[3];

Matrix mem;

void copy(Matrix A,Matrix B){
	for(int i=1;i<=maxl;i++)
		for(int j=1;j<=maxl;j++)
			A[i][j]=B[i][j];
}

void Matrix_mul(Matrix A,Matrix B,Matrix ans){
	Matrix C;
	for(int i=1;i<=maxl;i++)
		for(int j=1;j<=maxl;j++){
			C[i][j]=0;
			for(int k=1;k<=maxl;k++)
				C[i][j]+=A[i][k]*B[k][j];
			C[i][j]%=mod;
		}
		copy(ans,C);
}

void Matrix_pow(Matrix A,int p,Matrix ans){
	if(p==0) {copy(ans,mem);return;}
	Matrix half;
	Matrix_pow(A,p>>1,half);
	Matrix_mul(half,half,half);
	if(p&1) Matrix_mul(half,A,half);
	copy(ans,half);
	return;
}

void Vector_mul(Vector A,Matrix B,Vector ans){
	Vector C;
	for(int i=1;i<=maxl;i++){
		C[i]=0;
		for(int j=1;j<=maxl;j++)
			C[i]+=A[j]*B[j][i];
		C[i]%=mod;
	}
	for(int i=1;i<=maxl;i++)
		ans[i]=C[i];
}

Matrix g,ans;
int n;

int main(){
    memset(mem,0,sizeof(mem));
    for(int i=1;i<=maxl;i++) mem[i][i]=1;
    g[1][1]=2;g[2][2]=3;g[1][2]=0;g[2][1]=0;
    int n=10;
    Matrix_pow(g,n,ans);
    return 0;
}
