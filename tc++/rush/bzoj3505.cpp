#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=1010;
typedef long long LL;
int m,n;
LL point,ans;

inline LL gcd(LL a,LL b){
	if(b==0) return a;
	return gcd(b,a%b);
}
int main(){
	scanf("%d%d",&m,&n);if(m>n) swap(m,n);
	point=(m+1)*(n+1);
	ans=point*(point-1)*(point-2)/6;//printf("ans:%lld\n",ans);
	LL xie=0;
	for(int i=2;i<=m;i++){
		for(int j=2;j<=n;j++){
			LL num=(m+1-i)*(n+1-j);
			ans-=num*2*(gcd(i,j)-1);xie+=num*2*(gcd(i,j)-1);
		//printf("len:%d %lld\n",len,num*2*(len-1));
		}
	}
	ans-=(LL)(n+1)*(m+1)*m*(m-1)/6;
	ans-=(LL)(m+1)*(n+1)*n*(n-1)/6;
	//printf("xie:%lld shu:%d heng:%d\n",xie,(n+1)*(m+1)*m*(m-1)/6,(m+1)*(n+1)*n*(n-1)/6);
	printf("%lld\n",ans);
	return 0;
}
