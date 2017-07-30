# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
long long m,n;
int main(){
	int kase=0;
	while(scanf("%lld%lld",&m,&n)!=EOF){
		if(!m&&!n) break;
		m++;n++;
		long long ans=0;
		ans=m*n*(m*n-1)/2*(m*n-2)/3;
		ans-=m*(m-1)/2*(m-2)/3*n;ans-=n*(n-1)/2*(n-2)/3*m;
		printf("Case %d: %lld\n",++kase,ans);
	}
	return 0;
}
