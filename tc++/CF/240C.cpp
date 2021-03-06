#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=21;
typedef long long LL;
LL big[maxn],small[maxn];
int n,A[1<<maxn],m;

void divide(int l,int r,int dep){
	if(l==r) return;
	int m=(l+r)>>1;
	divide(l,m,dep+1);
	divide(m+1,r,dep+1);
	sort(A+m+1,A+r+1);
	for(int i=l;i<=m;i++){
		small[dep]+=lower_bound(A+m+1,A+r+1,A[i])-(A+m)-1;
		big[dep]+=(r-m)-(upper_bound(A+m+1,A+r+1,A[i])-(A+m))+1;
	}
}

int main(){
	int x;
	scanf("%d",&n);
	for(int i=1;i<=(1<<n);i++)
		scanf("%d",&A[i]);
	divide(1,1<<n,0);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		for(int i=n-x;i<n;i++)
			swap(small[i],big[i]);
		LL ans=0;
		for(int i=0;i<n;i++) ans+=small[i];
		printf("%lld\n",ans);
	}
	return 0;
}
