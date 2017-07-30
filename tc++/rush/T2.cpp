#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1000010;
const int mod=1000000007;
LL f[maxn];

LL pow_mod(LL a,LL b){
	if(b==0) return 1;
	LL half=pow_mod(a,b>>1);
	if(b&1) return (half*half%mod)*a%mod;
	else return half*half%mod;
}

LL inv(LL x){
	return pow_mod(x,mod-2);
}

int main(){
	int n=1000000,a;
	f[0]=1;f[1]=1;
	for(int i=2;i<=n;i++)
		f[i]=(f[i-1]*(4*i-2)%mod)*inv(i+1)%mod;//printf("f[%d]:%lld\n",i,f[i]);
	int T;scanf("%d",&T);
	int t=0;
	while(T--){
		printf("Case #%d:\n",++t);
		scanf("%d",&a);
		printf("%lld\n",f[a]);
	}
	return 0;
}
