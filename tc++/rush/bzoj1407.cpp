# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=17;
typedef long long LL;
int n;
LL C[maxn],P[maxn],L[maxn];

void gcd(LL a,LL b,LL &d,LL &x,LL &y){
	if(b==0){
		d=a;x=1;y=0;return;
	}
	gcd(b,a%b,d,y,x);
	y-=a/b*x;
}

LL Line_mod(LL a,LL b,LL n){//ax=b(mod n)
	LL d,x,y;
	gcd(a,n,d,x,y);
	if(b%d) return -1;
	x%=n;x+=n;x%=n;x=(x*b/d)%(n/d);
	return x;
}

bool check(LL m){
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			LL ans=Line_mod((P[j]-P[i]+m)%m,(C[i]-C[j]+m)%m,m);
			if(ans==-1) continue;
			if(ans<=L[i]&&ans<=L[j]) return false;
		}
	return true;
}

int main(){
	scanf("%d",&n);LL start=0;
	for(int i=1;i<=n;i++)
		scanf("%lld%lld%lld",&C[i],&P[i],&L[i]),start=max(start,C[i]);
	for(LL m=start;m<=1000000;m++){
		if(check(m)) {printf("%lld\n",m);break;}
	}
	return 0;
}
