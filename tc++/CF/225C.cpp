#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=200010;
int n,a[maxn];
int zero=0;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	long long ans=0;
	for(int i=n;i>=1;i--)
		if(a[i]==0) zero++;
			else ans+=zero;
				printf("%lld\n",ans);
	return 0;
}
