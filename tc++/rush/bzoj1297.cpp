# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxnode=10*9+1;
const int mod=2009;
int n,t;
int g[12+1][12+1];
typedef int Matrix[maxnode][maxnode];
typedef int Vector[maxnode];
Matrix A;
Vector start;
int maxn;

void matrix_mul(Matrix A,Matrix B,Matrix res){
	Matrix C;
	/*puts("mul1:");
		for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",A[i][j]);puts("");}puts("");
		for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",B[i][j]);puts("");}puts("");*/
		//for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",C[i][j]);puts("");}puts("");
	for(int i=1;i<=maxn;i++)
		for(int j=1;j<=maxn;j++){
			C[i][j]=0;
			for(int k=1;k<=maxn;k++)
				C[i][j]+=A[i][k]*B[k][j];
			C[i][j]%=mod;
			//res[i][j]=C[i][j];
		}
		for(int i=1;i<=maxn;i++) for(int j=1;j<=maxn;j++) res[i][j]=C[i][j];
		/*puts("mul2:");
		for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",A[i][j]);puts("");}puts("");
		for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",B[i][j]);puts("");}puts("");
		for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",C[i][j]);puts("");}puts("");
		int fuck;scanf("%d",&fuck);*/
}

void matrix_pow(Matrix A,int p,Matrix res){
	Matrix C,mul;
	int num=1;
	memset(C,0,sizeof(C));
	for(int i=1;i<=maxn;i++) C[i][i]=1;
			//for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",mul[i][j]);puts("");}puts("");
	for(int i=1;i<=maxn;i++) for(int j=1;j<=maxn;j++) mul[i][j]=A[i][j];
	//for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",mul[i][j]);puts("");}puts("");
	while(num<=p){
		//printf("p:%d num:%d\n",p,num);int fuck;scanf("%d",&fuck);
		//for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",mul[i][j]);puts("");}puts("");
		if(p&num)
		matrix_mul(C,mul,C);
		matrix_mul(mul,mul,mul);
		num=num<<1;
	}
	for(int i=1;i<=maxn;i++) for(int j=1;j<=maxn;j++) res[i][j]=C[i][j];
}

void vector_mul(Vector A,Matrix B,Vector res){
	Vector C;
	for(int i=1;i<=maxn;i++){
		C[i]=0;
		for(int j=1;j<=maxn;j++)
			C[i]+=A[j]*B[j][i];
		C[i]%=mod;
	}
	for(int i=1;i<=maxn;i++) res[i]=C[i];
}
int main(){
	char ch;
	scanf("%d%d",&n,&t);
		maxn=n*9;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			while((ch=getchar())&&(ch<'0'||ch>'9'));
			g[i][j]=ch-'0';
		}
		memset(A,0,sizeof(A));
	for(int i=1;i<=n;i++){
		for(int j=1;j<9;j++){
			A[(i-1)*9+j][(i-1)*9+j+1]=1;//printf("%d %d %d\n",(i-1)*9+j,(i-1)*9+j+1,A[(i-1)*9+j][(i-1)*9+j+1]);
			}
		for(int j=1;j<=n;j++)
			if(g[i][j]!=0){
				int dist=g[i][j];
				A[(i-1)*9+dist+1-1][(j-1)*9+1]=1;
				//printf("%d %d A:%d\n",(i-1)*9+dist+1-1,(j-1)*9+1,A[(i-1)*9+dist-1][(j-1)*9+1]);
			}
		//	for(int ii=1;ii<=maxn;ii++) {for(int jj=1;jj<=maxn;jj++) printf("%d ",A[ii][jj]);puts("");}puts("");
	}
//	printf("%d %d\n",A[1][1],A[1][10]);
	//for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",A[i][j]);puts("");}puts("");
	matrix_pow(A,t,A);
	//for(int i=1;i<=maxn;i++) {for(int j=1;j<=maxn;j++) printf("%d ",A[i][j]);puts("");}puts("");
	start[1]=1;for(int i=2;i<=n;i++) start[i]=0;
	vector_mul(start,A,start);
	printf("%d\n",start[(n-1)*9+1]);
	return 0;
}
