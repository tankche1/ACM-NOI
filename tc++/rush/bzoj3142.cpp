#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
LL n,k,m,p;

LL Mul(LL a,LL num){
	if(num==0) return 0;
	LL ans=Mul(a,num>>1);
	ans+=ans;ans%=p;
	if(num&1) ans+=a,ans%=p;
	return ans;
}

LL fast_pow(LL a,LL num){
	if(num==0) return 1;
	LL half=fast_pow(a,num>>1);
	half*=half;half%=p;if(num&1) half*=a,half%=p;
	return half;
}

int main(){
	scanf("%lld%lld%lld%lld",&n,&k,&m,&p);
	LL ans=fast_pow(m,k-1);
	ans=Mul(ans,n);
	if(k>1){
	ans-=fast_pow(m,k-2)*(((k-1)*((m*(m+1)/2)%p))%p);ans%=p;
	}
	if(ans<0) ans+=p;
	printf("%lld\n",ans);
	return 0;
}
