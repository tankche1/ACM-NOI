# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=510;
typedef long long LL;
typedef long long vector[maxn];
int mod;

void matrix_mul(vector A,int n,vector B,vector res){
	vector C;
	for(int i=0;i<n;i++){
		C[i]=0;
		for(int j=0;j<n;j++){
			C[i]=(C[i]+A[j]*B[(j-i+n)%n])%mod;
		}
	}
	for(int i=0;i<n;i++) res[i]=C[i];
}

void matrix_mod(vector A,int n,int num,vector res){
	vector a,r;
	memset(r,0,sizeof(r));r[0]=1;
	for(int i=0;i<n;i++) a[i]=A[i];
	while(num){
		if(num&1) matrix_mul(r,n,a,r);
		num>>=1;
		matrix_mul(a,n,a,a);
	}
	for(int i=0;i<n;i++) res[i]=r[i];
}
int n,m,d,k;
vector first;
vector A;
int main(){
	while(scanf("%d%d%d%d",&n,&m,&d,&k)!=EOF){
		for(int i=0;i<n;i++) scanf("%lld",&first[i]);
			mod=m;
		memset(A,0,sizeof(A));
		for(int i=0;i<n;i++) if(min(i,n-i)<=d) A[i]=1;
	//	for(int i=0;i<n;i++) printf("%d ",A[i]);printf("\n");
		matrix_mod(A,n,k,A);
	//	for(int i=0;i<n;i++) printf("%d ",A[i]);printf("\n");
		matrix_mul(first,n,A,first);
		for(int i=0;i<n;i++){
			if(i) printf(" ");
				printf("%lld",first[i]);
			}printf("\n");
	}
	return 0;
}
/*
5 3 1 1
1 2 2 1 2
*/
