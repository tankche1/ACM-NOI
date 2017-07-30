# include<stdio.h>
# include<string.h>
# include<iostream>
# include<vector>
# include<bitset>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxl=4;
typedef LL Matrix[4][4];
typedef LL Vector[4];
Matrix mem;
LL mod;

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
	Matrix res,tmp;copy(res,mem);copy(tmp,A);
	while(p>0){
        if(p&1) Matrix_mul(res,tmp,res);
        p>>=1;Matrix_mul(tmp,tmp,tmp);
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

LL n,y,x,s;
Vector init,ans;
Matrix A,B;

LL Euler(LL x){
    LL res=x;
    for(LL i=2;i*i<=x;i++){
        if(x%i==0){
            res=res/i*(i-1);
            while(x%i==0) x/=i;
        }
    }
    if(x>1) res=res/x*(x-1);
    return res;
}

LL fast_pow(LL a,LL b){
    LL res=1,tmp=a;
    while(b>0){
        if(b&1) res=res*tmp%mod;
        b>>=1;tmp=tmp*tmp%mod;
    }
    return res;
}

int main(){
    memset(mem,0,sizeof(mem));for(int i=0;i<maxl;i++) mem[i][i]=1;
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%I64d%I64d%I64d%I64d",&n,&y,&x,&s);
        init[0]=1;init[1]=1;init[2]=0;init[3]=0;
        A[0][0]=1;A[0][1]=A[0][2]=A[0][3]=0;
        A[1][0]=4;A[1][1]=4;A[1][2]=1;A[1][3]=2;
        A[2][0]=1;A[2][1]=1;A[2][2]=0;A[2][3]=0;
        A[3][0]=4;A[3][1]=4;A[3][2]=0;A[3][3]=1;

        mod=Euler(s+1);LL t=mod;
        Matrix_pow(A,n*y-1,B);
        Vector_mul(init,B,ans);

        mod=s+1;
        LL _ans=fast_pow(x,ans[0]%t+t);
        printf("%I64d\n",_ans);
    }

    return 0;
}
