#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const LL INF=(LL)1<<60;
LL x[maxn],y[maxn],n;
inline LL sqr(LL x) {return x*x;}
LL p[maxn],cnt;LL ans;
bool cmpy(int a,int b) {return y[a]<y[b];}

void solve(int l,int r){
	if(l==r) return;
	int m=(l+r)>>1;
	solve(l,m);solve(m+1,r);cnt=0;
	for(int i=l;i<=r;i++){
		if(sqr(x[m]-x[i])>=ans) continue;
		p[cnt++]=i;
	}
	sort(p,p+cnt,cmpy);
	for(int i=0;i<cnt;i++){
		for(int j=i+1;j<cnt&&sqr(y[p[j]]-y[p[i]])<ans;j++)
			ans=min(ans,sqr(y[p[j]]-y[p[i]])+sqr(x[p[j]]-x[p[i]]));
	}
}
int main(){
	scanf("%lld",&n);y[0]=0;
	for(int i=1;i<=n;i++) scanf("%lld",&y[i]),x[i]=i,y[i]+=y[i-1];ans=INF;
	solve(1,n);
	printf("%lld\n",ans);
	return 0;
}
