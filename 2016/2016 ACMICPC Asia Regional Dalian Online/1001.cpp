# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int mod=1000000007;
int n;

typedef long long LL;

typedef LL Mat[2][2];

void init(Mat A){
    A[0][0]=A[1][1]=1;A[0][1]=A[1][0]=0;
}

void copy(Mat A,Mat B){
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            A[i][j]=B[i][j];
        }
    }
}

Mat C;

void matrix_mul(Mat A,Mat B,Mat ans){
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            C[i][j]=0;
            for(int k=0;k<2;k++){
                C[i][j]+=A[i][k]*B[k][j];
            }
            if(C[i][j]>=mod) C[i][j]%=mod;
        }
    }
    copy(ans,C);
}

void Matrix_pow(Mat A,int p,Mat ans){
	if(p==0) {init(ans);return;}
	Mat half;
	Matrix_pow(A,p>>1,half);
	matrix_mul(half,half,half);
	if(p&1) matrix_mul(half,A,half);
	copy(ans,half);
	return;
}

LL fast_pow(int a,int b){
    LL res=1,tmp=a;
    while(b>0){
        if(b&1) res=res*tmp%mod;
        tmp=tmp*tmp%mod;
        b>>=1;
    }
    return res;
}

LL f[2];
void get_f(int n){
    //f[0]=2;f[1]=1;
    Mat A,B;
    A[0][0]=A[0][1]=A[1][0]=1;A[1][1]=0;
    Matrix_pow(A,n-1,B);
    f[0]=2*B[0][0]+B[1][0];
    f[1]=2*B[0][1]+B[1][1];
    if(f[0]>=mod) f[0]%=mod;if(f[1]>=mod) f[1]%=mod;
}

int get_g(int n){
    if(n==1) return 1;
    if(n==2) return 3;
    get_f(n-2);
    return (f[0]+f[1]*2)%mod;
}

int Euler(int n){
    //printf("Euler: n:%d ",n);
    int m=sqrt(n+0.5);
    int ans=n;
    for(int i=2;i<=m;i++){
        if(n%i==0){
            ans=ans/i*(i-1);
            while(n%i==0) n/=i;
        }
    }
    if(n>1) ans=ans/n*(n-1);
    //printf("ans:%d\n",ans);
    return ans;
}

int main(){
    /*for(int i=1;i<=5;i++){
        get_f(i);printf("i:%d f:%d ",i,f[0]);
        printf("g:%d\n",get_g(i));
    }*/
    while(scanf("%d",&n)!=EOF){
        if(n==1) {puts("2");continue;}
        LL ans=0;
        for(int x=1;x*x<=n;x++){
            if(n%x==0){
               // printf("x:%d g:%d g:%d\n",x,get_g(x),get_g(n/x));
                ans+=(LL)Euler(n/x)*get_g(x);ans%=mod;
                //printf("add:%d \n",Euler(n/x)*get_g(x));
                if(x*x==n) continue;
                ans+=(LL)Euler(x)*get_g(n/x);
                //printf("add:%d \n",Euler(x)*get_g(n/x));
                ans%=mod;
            }
        }
        //printf("ans:%I64d\n",ans);
        ans=ans*fast_pow(n,mod-2)%mod;
        printf("%I64d\n",ans);
    }
    return 0;
}
