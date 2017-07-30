#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
LL n,m,v,k;
int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		scanf("%lld%lld%lld%lld",&n,&m,&v,&k);
		if(m>=n) {printf("0\n");continue;}
		if((m-v)*k<=m) {puts("-1");continue;}
		LL now=m;
		for(int ans=1;ans;ans++){
			now=(now-v)*k;//printf("now:%lld\n",now);
			if(now>=n) {printf("%d\n",ans);break;}
			if(ans>n) {puts("-1");break;}
		}
	}
	return 0;
}
