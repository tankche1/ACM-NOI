# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=10010;
const int maxl=2;
typedef LL Matrix[3][3];
typedef LL Vector[3];

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

int lena,lenb,lenc,knowa,knowb,knowc,a[maxn],b[maxn],c[maxn];

struct Digit{
    int pos,val,type;
}digit[maxn*3];

int main(){
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&lena,&knowa);
        for(int i=1;i<=knowa;i++){
            scanf("%d",&a[i]);
        }
    }
    return 0;
}
