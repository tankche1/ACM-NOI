# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
LL f[maxn];
int n,m;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=min(n,m);i>=1;i--){
		f[i]=(LL)(n/i)*(m/i);
		for(int j=2;i*j<=min(n,m);j++)
			f[i]-=f[i*j];
	}
	LL ans=0;
	for(int i=1;i<=min(n,m);i++){
		ans+=f[i]*(i*2-1);
	}
	printf("%lld\n",ans);
	return 0;
}
