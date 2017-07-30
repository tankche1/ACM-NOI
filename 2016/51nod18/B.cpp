# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
const int mod=1000000007;

typedef long long LL;
const int maxl=8;
typedef LL Matrix[8][8];
typedef LL Vector[8];

Matrix mem;

void copy(Matrix A,Matrix B){
	for(int i=0;i<maxl;i++)
		for(int j=0;j<maxl;j++)
			A[i][j]=B[i][j];
}

void Matrix_mul(Matrix A,Matrix B,Matrix ans){
	Matrix C;
	for(int i=0;i<maxl;i++)
		for(int j=0;j<maxl;j++){
			C[i][j]=0;
			for(int k=0;k<maxl;k++)
				C[i][j]+=A[i][k]*B[k][j];
			C[i][j]%=mod;
		}
		copy(ans,C);
}


void Matrix_pow(Matrix A,LL p,Matrix ans){
	Matrix tmp,res;
	copy(tmp,A);copy(res,mem);
	while(p>0){
            //printf("p:%I64d\n",p);
        if(p&1) Matrix_mul(res,tmp,res);
        p>>=1;
        Matrix_mul(tmp,tmp,tmp);
	}
	copy(ans,res);
	return;
}

void Vector_mul(Vector A,Matrix B,Vector ans){
	Vector C;
	for(int i=0;i<maxl;i++){
		C[i]=0;
		for(int j=0;j<maxl;j++)
			C[i]+=A[j]*B[j][i];
		C[i]%=mod;
	}
	for(int i=0;i<maxl;i++)
		ans[i]=C[i];
}

Matrix A,B;
Vector init;
Vector ans;

LL n;

int main(){
    scanf("%I64d",&n);
    if(n==1) {puts("2");return 0;}
    else if(n==2) {puts("4");return 0;}
    else if(n==3) {puts("7");return 0;}

    memset(A,0,sizeof(A));
    //A[0][1]=A[1][1]=A[2][3]=A[3][6]=A[3][7]=A[4][1]=A[4][2]=A[5][3]=A[6][4]=A[6][5]=A[7][6]=A[7][7]=1;
    A[0][0]=A[0][1]=A[1][3]=A[3][6]=A[3][7]=A[4][0]=A[4][1]=A[5][3]=A[6][4]=A[6][5]=A[7][6]=A[7][7]=1;

    memset(mem,0,sizeof(mem));
    for(int i=0;i<8;i++) init[i]=1,mem[i][i]=1;
    init[2]=0;

    //puts("fuck");
    Matrix_pow(A,n-3,B);
    Vector_mul(init,B,ans);
    LL sum=0;
    for(int i=0;i<8;i++) sum+=ans[i];
    sum%=mod;
    printf("%I64d\n",sum);
    return 0;
}
