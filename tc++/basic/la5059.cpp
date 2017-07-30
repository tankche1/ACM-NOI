# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
long long SG(long long a){
	if(a%2==0) return a/2;
		return SG(a/2);
}
int main(){
	int T,n;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		long long a,v=0;
		while(n--){
			scanf("%lld",&a);
			v=v^(SG(a));
		}
		if(!v) printf("NO\n");
			else printf("YES\n");
	}
	return 0;
}
