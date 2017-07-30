# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
typedef long long LL;
LL n,P,B;
LL a[maxn];
LL b[maxn],c[maxn];
LL ans[maxn];

inline void gcd(LL a,LL &x,LL b,LL &y,LL &d){
	if(b==0){
		d=a;x=1;y=0;return;
	}
	gcd(b,y,a%b,x,d);
	y-=a/b*x;
}

int main(){
	LL x,y,d,dd;
	scanf("%lld%lld%lld",&n,&P,&B);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	//gcd(a[1],x,a[2],y,d);
	//b[1]=x;//b[2]=y;
	d=a[1];
	a[n+1]=P;
	c[1]=c[2]=1;b[1]=1;
	for(int i=2;i<=n+1;i++)
	{	dd=d,gcd(dd,x,a[i],y,d);while(x<0||y<0) x+=P,y+=P;
		c[i]=x%P,b[i]=y%P;}
	//printf("dd:%lld\n",dd);
	if((B%d)!=0) {puts("NO");return 0;}
	c[n+1]*=B/d;c[n+1]%=P;
	int now=c[n+1]%P;
	for(int i=n;i>=1;i--){
		ans[i]=(now*b[i])%P;
		now=(now*c[i])%P;
	}
	printf("YES\n%lld",ans[1]);
	for(int i=2;i<=n;i++)
		printf(" %lld",ans[i]);puts("");
	return 0;
}
