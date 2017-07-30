# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef unsigned long long LL;
const int maxlen=3;
typedef LL Matrix[maxlen+5][maxlen+5];
typedef LL Vector[maxlen];

LL n,m;
LL Ten[25];

void matrix_mul(Matrix A,Matrix B,Matrix ans){
	Matrix C;/*printf("A:\n");
	for(int i=1;i<=3;i++) {for(int j=1;j<=3;j++) printf("%d ",A[i][j]);printf("\n");}printf("B:\n");
	for(int i=1;i<=3;i++) {for(int j=1;j<=3;j++) printf("%d ",B[i][j]);printf("\n");}*/
	for(int i=1;i<=maxlen;i++)
		for(int j=1;j<=maxlen;j++){
			C[i][j]=0;
			for(int k=1;k<=maxlen;k++)
			{C[i][j]+=A[i][k]*B[k][j];//if(C[i][j]>=m) C[i][j]%=m;
				}
			//printf("%llu\n",C[i][j]);
			C[i][j]%=m;
		}
		//printf("C:\n");
		//for(int i=1;i<=3;i++) {for(int j=1;j<=3;j++) printf("%d ",C[i][j]);printf("\n");}
	memcpy(ans,C,sizeof(C));
}

void vector_mul(Vector A,Matrix B,Vector res){
	Vector C;
	for(int i=1;i<=maxlen;i++){
		C[i]=0;
		for(int j=1;j<=maxlen;j++){
			C[i]+=A[j]*B[j][i];//if(C[i]>=m) C[i]%=m;
		}
		C[i]%=m;
	}
	memcpy(res,C,sizeof(C));
}

void fast_pow(Matrix A,LL p,Matrix res){
	Matrix C;
	memset(C,0,sizeof(C)); for(int i=1;i<=maxlen;i++) C[i][i]=1;
	if(p==0) {}
	else{
	fast_pow(A,p/2,C);
	matrix_mul(C,C,C);
	if(p&1) matrix_mul(C,A,C);
	}
	memcpy(res,C,sizeof(C));
	/*printf("p:%d A:\n",p);
	for(int i=1;i<=3;i++) {for(int j=1;j<=3;j++) printf("%d ",A[i][j]);printf("\n");}
	printf("C:\n");
	for(int i=1;i<=3;i++) {for(int j=1;j<=3;j++) printf("%d ",C[i][j]);printf("\n");}*/
}

int main(){
	scanf("%llu%llu",&n,&m);
	LL num;
	Vector now;now[1]=0;now[2]=0;now[3]=1;
	Ten[0]=1;
	for(int i=1;i<22;i++)
	{Ten[i]=(Ten[i-1]*10)%m;}
	int k=1;
	num=0;
	while(1){
		Matrix A;
		A[1][1]=A[1][2]=A[3][1]=A[3][2]=A[3][3]=1;A[1][3]=A[2][1]=A[2][3]=0;A[2][2]=Ten[k];
		if((LL)((num+1)*10-1)<n){
			//puts("a");
			LL p=10*(num+1)-1-num;
			//printf("%llu\n",p);
			fast_pow(A,p,A);
			vector_mul(now,A,now);
			num=(num+1)*10-1;
		}
		else{
			//puts("b");
			LL p=n-num;
			//for(int i=1;i<=3;i++) {for(int j=1;j<=3;j++) printf("%d ",A[i][j]);printf("\n");}
			fast_pow(A,p,A);
		//	for(int i=1;i<=3;i++) {for(int j=1;j<=3;j++) printf("%d ",A[i][j]);printf("\n");}
			vector_mul(now,A,now);
			break;
		}
		k++;
	//	printf("num:%llu now:%llu %llu %llu\n",num,now[1],now[2],now[3]);
		//int fuck;scanf("%d",&fuck);
	}
	printf("%llu\n",now[2]);
	return 0;
}
//12345678910 1000000000
//999999999 997
//10000000000 997
