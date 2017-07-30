# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
typedef long long Matrix[50][50];
typedef LL Vector[50];
const LL mod=95041567;
int Mod,maxn;
LL p[5]={31,37,41,43,47};
LL Bell[6][60],C[60];
LL a[10];
int T;
int n;

void matrix_mul(Matrix A,Matrix B,Matrix C){
	Matrix res;
	for(int i=1;i<=maxn;i++)
		for(int j=1;j<=maxn;j++){
			res[i][j]=0;
			for(int k=1;k<=maxn;k++)
				res[i][j]=(res[i][j]+A[i][k]*B[k][j])%Mod;
		}
	memcpy(C,res,sizeof(res));
}

void vector_mul(Vector A,Matrix B,Vector C){
	Vector res;
	for(int i=1;i<=maxn;i++){
		res[i]=0;
		for(int j=1;j<=maxn;j++)
			res[i]=(res[i]+A[j]*B[j][i])%Mod;
	}
	memcpy(C,res,sizeof(res));
}

void matrix_pow(Matrix A,LL num,Matrix C){
	Matrix res;
	if(!num) {memset(res,0,sizeof(res));for(int i=1;i<=maxn;i++) res[i][i]=1;memcpy(C,res,sizeof(res));return;}
	matrix_pow(A,num>>1,res);
	matrix_mul(res,res,res);
	if(num&1) matrix_mul(res,A,res);
	memcpy(C,res,sizeof(res));
}

void gcd(LL a,LL b,LL &x,LL &y,LL &d){
	if(!b) {d=a;x=1;y=0;return;}
	gcd(b,a%b,y,x,d);y-=x*(a/b);
}

LL china(int n,LL *a,LL *m){
	LL M=mod;
	LL ans=0;LL x,y,d;
	for(int i=0;i<n;i++){
		gcd(M/m[i],m[i],x,y,d);
		ans=(ans+M/m[i]*x*a[i])%mod;
		//printf("ans:%lld\n",ans);
	}
	return (ans+mod)%mod;
}

int main(){
	scanf("%d",&T);
	for(int pp=0;pp<5;pp++){
		Bell[pp][0]=1;//Bell[pp][1]=1;
		for(int i=1;i<=p[pp];i++){
			C[0]=1;Bell[pp][i]=0;
			for(int k=1;k<i;k++){
				C[k]=C[k-1]*(i-1-k+1)/k;
			}
			for(int j=1;j<=i;j++){
				Bell[pp][i]+=Bell[pp][i-j]*C[i-j];if(Bell[pp][i]>=p[pp]) Bell[pp][i]%=p[pp];
			}
		//	printf("Bellp[%d][%d]:%lld\n",pp,i,Bell[pp][i]);
		}
	}
	//printf("%lld\n",Bell[50]);
	while(T--){
		scanf("%d",&n);
		//if(n<=50) {printf("%lld\n",Bell[n]);continue;}
		for(int pp=0;pp<5;pp++){
			if(n<=p[pp]) {a[pp]=Bell[pp][n];continue;}
			Matrix A;memset(A,0,sizeof(A));
			for(int i=1;i<p[pp];i++){
				A[i+1][i]=1;
			}
			A[1][p[pp]]=A[2][p[pp]]=1;
			Mod=p[pp];maxn=p[pp];
			/*for(int i=1;i<=maxn;i++){
				for(int j=1;j<=maxn;j++) printf("%lld ",A[i][j]);printf("\n");}*/
				//puts("");
			matrix_pow(A,n-p[pp],A);
				/*for(int i=1;i<=maxn;i++){
				for(int j=1;j<=maxn;j++) printf("%lld ",A[i][j]);printf("\n");}*/
			Vector V;
			for(int i=1;i<=p[pp];i++) V[i]=Bell[pp][i];
			vector_mul(V,A,V);
			a[pp]=V[p[pp]];
			//printf("%lld\n",a[pp]);
		}
		//for(int pp=0;pp<5;pp++) printf("a[%d]:%lld\n",pp,a[pp]);
		printf("%lld\n",china(5,a,p));
	}
	return 0;
}
