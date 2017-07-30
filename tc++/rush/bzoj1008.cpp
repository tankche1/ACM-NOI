# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=100003;

int get_pow(LL a,LL b){
	LL r=a%mod,res=1;
	while(b){
		if(b&1) res=(res*r)%mod;
		b>>=1;
		r=(r*r)%mod;
	}
	return (int)res;
}

LL m,n;
int main(){
	scanf("%lld%lld",&m,&n);
	int ans=(get_pow(m,n)-(((LL)(m%mod)*get_pow(m-1,n-1))%mod)+mod)%mod;
	printf("%d\n",ans);
	return 0;
}
// 100000000 1000000000000