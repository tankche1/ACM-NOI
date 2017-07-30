# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=50010;

typedef long long LL;

LL n,L,SL[maxn],f[maxn];
int q[maxn],head=0,tail=-1;//q保存的是决策

LL F(int i) {return SL[i];}
LL X(int j,int k) {return 2*(F(k)-F(j));}
LL Y(int j,int k) {return f[k]-f[j]+(F(k)+L)*(F(k)+L)-(F(j)+L)*(F(j)+L);}

void init(){
	int a;
	scanf("%lld%lld",&n,&L);L++;
	SL[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&a);SL[i]=SL[i-1]+a+1;
	}
}

int main(){
	init();
	f[0]=0;
	q[++tail]=0;
	for(int i=1;i<=n;i++){
		while(head<tail&&(Y(q[head],q[head+1])<=F(i)*X(q[head],q[head+1]))) head++;
		f[i]=f[q[head]]+(SL[i]-SL[q[head]]-L)*(SL[i]-SL[q[head]]-L);
		while(head<tail&&(!(Y(q[tail],i)*X(q[tail-1],q[tail])>Y(q[tail-1],q[tail])*X(q[tail],i)))) tail--;
		q[++tail]=i;
	}
	printf("%lld\n",f[n]);
	return 0;
}
