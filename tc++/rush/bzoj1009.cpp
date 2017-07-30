# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1000000010;
const int maxm=21;
int f[maxm];
char s[maxm+2];
int n,m,mod;

void kmp(){
	f[0]=f[1]=0;
	for(int i=2;i<=m;i++){
		int j=f[i-1];
		while(j&&s[j+1]!=s[i]) j=f[j];
		f[i]=s[j+1]==s[i]?j+1:0;
	}
	//for(int i=0;i<=m;i++)
		//printf("f[%d]:%d\n",i,f[i]);
}

struct Matrix{
	int A[maxm][maxm];
};

Matrix matrix_mul(Matrix A,Matrix B){
	Matrix C;
	for(int i=0;i<=m;i++)
		for(int j=0;j<=m;j++){
			C.A[i][j]=0;
			for(int k=0;k<=m;k++)
				C.A[i][j]+=A.A[i][k]*B.A[k][j];
			C.A[i][j]%=mod;
		}
		return C;
}

Matrix matrix_pow(Matrix A,int k){
	Matrix res,r;
	for(int i=0;i<=m;i++) for(int j=0;j<=m;j++) {res.A[i][j]=0;r.A[i][j]=A.A[i][j];}
	for(int i=0;i<=m;i++) res.A[i][i]=1;
	while(k){
		if(k&1) res=matrix_mul(res,r);
		k>>=1;
		r=matrix_mul(r,r);
	}
	return res;
}

Matrix A;
int main(){
	scanf("%d%d%d",&n,&m,&mod);
	scanf("%s",s+1);
	kmp();
	s[m+1]='a';
	//printf("fuck\n");
	memset(A.A,0,sizeof(A.A));
	for(int i=0;i<m;i++){
		for(int j=0;j<=9;j++){
			if(i+1==m&&j+'0'==s[m]) continue;
			if(s[i+1]==j+'0') {A.A[i][i+1]++;continue;}
			int k=f[i];
			while(k&&s[k+1]!=j+'0') k=f[k];
			if(s[k+1]!=j+'0') A.A[i][0]++;
			else A.A[i][k+1]++;
		}
	}
	/*for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)
			printf("%d ",A.A[i][j]);
		printf("\n");
	}*/
	Matrix B=matrix_pow(A,n);
/*	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)
			printf("%d ",B.A[i][j]);
		printf("\n");
	}*/
	int ans=0,first[maxm];memset(first,0,sizeof(first));first[0]=1;
	for(int i=0;i<=m;i++){
		for(int j=0;j<=m;j++)
			ans+=first[j]*B.A[j][i];
	//	printf("ans:%d\n",ans);
		ans=ans%mod;
	}
	printf("%d\n",ans);
	return 0;
}
/*
1000000000 17 997
98765432112345678

*/
