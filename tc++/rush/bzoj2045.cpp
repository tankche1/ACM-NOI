#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1000010;
LL A,B,d;
LL n;
LL p[maxn];
LL f[maxn];
int main(){
	scanf("%lld%lld%lld",&A,&B,&d);
	n=min(A,B);
	for(LL i=2;i<=n;i++){
		LL x=i,num=0;
		for(LL j=2;j*j<=x;j++)
			while(x%j==0) x/=j,num++;
		if(x>1) num++;
		p[i]=num%2==0?1:-1;
	}
	for(LL i=n;i>=d;i--){
		f[i]=(A/i)*(B/i);
		for(LL j=2;i*j<=n;j++){
			f[i]-=f[i*j];
		}
		//printf("f[%lld]:%lld\n",i,f[i]);
	}
	printf("%lld\n",f[d]);
	return 0;
}
