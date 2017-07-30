# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=30;
long long d[40][40];
long long f[40];

long long C(long long n,long long m){
	double ans=1;
	for(int i=1;i<=m;i++)
		ans*=(n-i+1);
	for(int i=1;i<=m;i++) ans/=i;
		return (long long)(ans+0.5);
}

void dp(int i,int j){
	d[i][j]=0;
	for(int p=0;p*i<=j;p++){
		d[i][j]+=d[i-1][j-p*i]*C(f[i]+p-1,p);
	}
}

int main(){
	memset(d,0,sizeof(d));
	for(int i=0;i<=30;i++) d[i][0]=d[i][1]=1;
	d[0][1]=0;
	f[1]=1;
	for(int i=1;i<=30;i++){
		for(int j=2;j<=30;j++){
			dp(i,j);
		}
		f[i+1]=d[i][i+1];
	}
		int n;
		while(scanf("%d",&n)==1&&n){
			printf("%lld\n",n==1?1:2*f[n]);
		}
	return 0;
}
