# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL INF=1000000000;
#define pos(a,b) (a-1)*(a-1)+b
struct Pos{
	LL x,y,z;
	void getpos(LL n){
		x=(LL)sqrt(n-1)+1;
		y=(n-(x-1)*(x-1)+1)/2;
		z=(x*x-n+1+1)/2;
	}
};
Pos start,end;
LL ans;
LL n,m;
LL ansa,ansb;
int main(){
	scanf("%lld%lld",&n,&m);
	LL a,b;
	scanf("%lld%lld",&a,&b);
	start.getpos((LL)(pos(a,b)));
		//printf("%lld x:%lld y:%lld z:%lld\n",pos(a,b),start.x,start.y,start.z);
	ans=-1;
	for(LL i=1;i<=m;i++){
		scanf("%lld%lld",&a,&b);
		end.getpos((LL)(pos(a,b)));
		//printf("%lld x:%lld y:%lld z:%lld\n",pos(a,b),end.x,end.y,end.z);
		if(ans==-1||(LL)(abs(start.x-end.x)+abs(start.y-end.y)+abs(start.z-end.z))<ans)
			ans=(LL)(abs(start.x-end.x)+abs(start.y-end.y)+abs(start.z-end.z)),ansa=a,ansb=b;
		//ans=min(ans,(LL)(abs(start.x-end.x)+abs(start.y-end.y)+abs(start.z-end.z)));
	}
	printf("%lld %lld\n%lld\n",ansa,ansb,ans+1);
	return 0;
}
