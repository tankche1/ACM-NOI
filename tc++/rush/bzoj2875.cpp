# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int Step=63;
LL m,a,c,X0,n,g;
typedef LL Matrix[3][3];
typedef LL Vector[3];
LL Two[70];

void Copy(Matrix res,Matrix A){
	for(int i=1;i<=2;i++) for(int j=1;j<=2;j++) res[i][j]=A[i][j];
}

LL mul(LL a,LL b){
	if(a<Two[32]&&b<Two[32]){
		//printf("%lld * %lld = %lld\n",a,b,(a*b)%m);
		return (a*b)%m;
	}
	LL ans=0;
	if(b==0) return 0;
	LL half=mul(a,b/2);
	ans=(half+half)%m;
	//printf("ans:%lld\n",ans);
	if(b&1) ans=(ans+a)%m;
		//printf("ss:%lld * %lld = %lld\n",a,b,ans);
	return ans;
}

/*LL mul(LL a,LL b) {    
	LL res=0;     
	while(b){      
		if(b&1) 
			res=(res+a)%m;        
		a=(a+a)%m; b>>=1;    
		}     
		return res; 
		} */

void Matrix_mul(Matrix ans,Matrix A,Matrix B){
	Matrix C;
	for(int i=1;i<=2;i++)
		for(int j=1;j<=2;j++){
			C[i][j]=0;
			for(int k=1;k<=2;k++)
				C[i][j]=(C[i][j]+mul(A[i][k],B[k][j]))%m;
		}
	Copy(ans,C);
}

void Matrix_pow(Matrix tt,Matrix A,LL p){
	Matrix res;
	Matrix ans;
	ans[1][1]=ans[2][2]=1;ans[1][2]=ans[2][1]=0;
	Copy(res,A);
	while(p){
		if(p&1)
			Matrix_mul(ans,ans,res);
		Matrix_mul(res,res,res);
		p>>=1;
	}
	Copy(tt,ans);
}

void Vector_mul(Vector ans,Vector A,Matrix B){
	Vector C;
	for(int i=1;i<=2;i++){
		C[i]=0;
		for(int k=1;k<=2;k++)
			C[i]=(C[i]+mul(A[k],B[k][i]))%m;
	}
	ans[1]=C[1];ans[2]=C[2];
}

int main(){
	freopen("random.in","r",stdin);
	freopen("random.out","w",stdout);
//	m=99999997;
	//printf("mul:%lld\n",mul((LL)999982347,(LL)999982347));
	Two[0]=1;
	for(int i=1;i<=Step;i++) Two[i]=Two[i-1]<<1;
	scanf("%lld%lld%lld%lld%lld%lld",&m,&a,&c,&X0,&n,&g);
	a%=m;c%=m;
	Matrix A;
	A[1][1]=1;A[2][1]=0;A[1][2]=c;A[2][2]=a;
	Vector start;
	start[1]=1;start[2]=X0;
	Matrix_pow(A,A,n);//puts("e");
	Vector_mul(start,start,A);
	printf("%lld\n",start[2]%g);
	return 0;
}
