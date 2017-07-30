#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
LL n,m,L;
LL mod;
LL fast_pow(LL a,LL p){
	if(!p) return 1;
	LL x=fast_pow(a,p>>1);
	x=x*x%mod;
	if(p&1) x=x*a%mod;
		//printf("a:%lld p:%lld res:%lld\n",a,p,x%mod);
	return x%mod;
}

void gcd(LL &x,LL &y,LL a,LL b,LL &d){
	if(!b){
		d=a,x=1,y=0;return;
	}
	gcd(y,x,b,a%b,d);
	y-=(a/b)*x;
}

int main(){
	scanf("%lld%lld%lld",&n,&m,&L);
	mod=n+1;
	LL x=fast_pow(2,m);
	//printf("x:%lld\n",x);
	LL d;
	LL a,b;
	gcd(a,b,x,mod,d);
	a%=mod;
	while(a<0) a+=(n+1);
	a=(a*L)%mod;
	printf("%lld\n",a);
	return 0;
}
