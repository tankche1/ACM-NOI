# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=50010;
const int mod=98765431;
const int maxl=2;
typedef LL Matrix[3][3];
typedef LL Vector[3];
Matrix mem;
LL n,T;
LL C[maxn];

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

int main(){
	scanf("%lld%lld",&n,&T);
	mem[1][1]=mem[2][2]=1;mem[1][2]=mem[2][1]=0;
	LL sum=0;
	for(int i=1;i<=n;i++)
		scanf("%lld",&C[i]),sum+=C[i];
	sum%=mod;
	Matrix A;Vector start;
	start[1]=0;start[2]=-1;
	A[1][1]=n-1;A[1][2]=0;A[2][1]=1-n;A[2][2]=-1;
	Matrix_pow(A,(int)T-1,A);
	Vector_mul(start,A,start);
	for(int i=1;i<=n;i++){
		if(T%2==1)
			printf("%lld\n",(sum*(start[1]+1)-C[i])%mod);
		else
			printf("%lld\n",(sum*(start[1]-1)+C[i])%mod);
	}
	return 0;
}
