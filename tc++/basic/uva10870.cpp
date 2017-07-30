# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxd=20;
int sz,mod;
typedef long long Matrix[maxd][maxd];
typedef long long Vector[maxd];

void matrix_mul(Matrix A, Matrix B, Matrix res) {
  Matrix C;
  memset(C, 0, sizeof(C));
  for(int i = 0; i < sz; i++)
    for(int j = 0; j < sz; j++)
      for(int k = 0; k < sz; k++) C[i][j] = (C[i][j] + A[i][k] * B[k][j]) % mod;
  memcpy(res, C, sizeof(C));
}


void matrix_pow(Matrix A,int num,Matrix res){
	Matrix a,r;
	//printf("sizeof(a):%d sizeof(A):%d\n",sizeof(a),sizeof(A));
	memcpy(a,A,sizeof(a));
	memset(r,0,sizeof(r));
	for(int i=0;i<sz;i++) r[i][i]=1;
	while(num){
		//printf("num:%d\n",num);int bb;scanf("%d",&bb);
		if(num&1) matrix_mul(r,a,r);
		num>>=1;
		matrix_mul(a,a,a);
	}
	//printf("sizeof(r):%d sizeof(res):%d\n",sizeof(r),sizeof(res));
	memcpy(res,r,sizeof(r));//sizeof(res) 会错
}

void transform(Vector F,Matrix A,Vector res){
	Vector C;
	for(int i=0;i<sz;i++){
		C[i]=0;
		for(int j=0;j<sz;j++)
			C[i]=(C[i]+F[j]*A[j][i])%mod;
	}
	memcpy(res,C,sizeof(C));
}

int n,d,m;
int main(){
	while(scanf("%d%d%d",&d,&n,&m)!=EOF){
		if(!n&&!d&&!m) break;
		Matrix A;
		Vector a,f;
		for(int i=0;i<d;i++) scanf("%lld",&a[i]);
		for(int i=d-1;i>=0;i--) {scanf("%lld",&f[i]);f[i]=f[i]%m;}
			
		memset(A,0,sizeof(A));
		for(int i=0;i<d;i++) A[i][0]=a[i]%m;
		for(int i=1;i<d;i++) A[i-1][i]=1;
		
		sz=d;mod=m;//printf("aa");
		matrix_pow(A,n-d,A);//printf("aa");
		transform(f,A,f);//printf("aa");
	/*	for(int i=0;i<sz;i++) {
			for(int j=0;j<sz;j++) printf("%lld ",A[i][j]);printf("\n");
			}*/
		printf("%lld\n",f[0]);
	}
	return 0;
}
