# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxk=10;
const int mod=9973;

int Euler(int n){
	int ans=n;
	for(int i=2;i*i<=n;i++){
		if(n%i==0){
			ans=ans/i*(i-1);
			while(n%i==0) n/=i;
		}
	}
	if(n>1) ans=ans/n*(n-1);
	return ans%mod;
}

struct Matrix{
	int A[maxk][maxk];
};
int m;

void matrix_mul(Matrix& A,Matrix B){
	Matrix C;
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++){
			C.A[i][j]=0;
			for(int k=0;k<m;k++)
				C.A[i][j]=(C.A[i][j]+A.A[i][k]*B.A[k][j]);
			C.A[i][j]%=mod;
		}
	for(int i=0;i<m;i++) for(int j=0;j<m;j++) A.A[i][j]=C.A[i][j];
}

void matrix_pow(Matrix& A,int k){
	if(k==1) return;
	Matrix C,R;
	for(int i=0;i<m;i++) for(int j=0;j<m;j++) {R.A[i][j]=A.A[i][j];C.A[i][j]=0;}
	for(int i=0;i<m;i++) C.A[i][i]=1;
	//printf("k:%d\n",k);
	while(k){
		/*printf("k:%d C:\n",k);
		for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)
			printf("%d ",C.A[i][j]);printf("\n");}*/
		if(k&1) matrix_mul(C,R);
		k>>=1;
		matrix_mul(R,R);
	}
/*	for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)
			printf("%d ",A.A[i][j]);printf("\n");}
			printf("ans:\n");
			for(int i=0;i<m;i++){
		for(int j=0;j<m;j++)
			printf("%d ",C.A[i][j]);printf("\n");}*/
	for(int i=0;i<m;i++)
		for(int j=0;j<m;j++)
			A.A[i][j]=C.A[i][j];
}

int matrix_sum(Matrix A,int k){
	matrix_pow(A,k);
	int ans=0;
	for(int i=0;i<m;i++)
		ans=(ans+A.A[i][i])%mod;
	return ans;
}

int n,k;
Matrix A;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%d%d%d",&n,&m,&k);
		int a,b;
		for(int i=0;i<m;i++) for(int j=0;j<m;j++) A.A[i][j]=1;
		for(int i=1;i<=k;i++){
			scanf("%d%d",&a,&b);a--;b--;
			A.A[a][b]=A.A[b][a]=0;
		}
		int ans=0;
		for(int L=1;L*L<=n;L++)
		if(n%L==0){
			//printf("ans:%d L:%d Euler(L):%d matrix_sum:%d\n",ans,L,Euler(L),matrix_sum(A,n/L));
			if(L*L!=n){
				ans=(ans+(Euler(L))*matrix_sum(A,n/L)+(Euler(n/L))*matrix_sum(A,L))%mod;
				//printf("ans:%d L:%d Euler(L):%d matrix_sum:%d\n",ans,n/L,Euler(n/L),matrix_sum(A,L));
			}
			else
				ans=(ans+(Euler(L))*matrix_sum(A,n/L))%mod;
		}
		int mod_n=n%mod,p;
		for(p=1;p<mod;p++) if((p*mod_n)%mod==1) break;//p是n的逆
			//printf("p:%d\n",p);
		ans=(ans*p)%mod;
		printf("%d\n",ans);
	}
	return 0;
}
