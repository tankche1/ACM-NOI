# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int mod=9999991;
LL ans,n;

LL fast_pow(int x,int p){
	LL num=1,mul=x;
	LL res=1;
	while(p>=num){
		if(p&num){
			res=(res*mul)%mod;
		}
		mul=(mul*mul)%mod;
		num<<=1;
	}
	return res;
}
int main(){
	scanf("%d",&n);
	ans=fast_pow(n,n-2);
	for(int i=2;i<=n-1;i++)
		ans=(ans*i)%mod;
	printf("%lld\n",ans);
	return 0;
}
