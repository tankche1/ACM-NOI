/*
f[1324]-f[1243]-f[1432]=f[1x2x]+f[1234]-f[12xx]-f[14xx]=F(1*2*)-F(1***)+F(13**)+F(1234)。
*/
# include<stdio.h>
# include<string.h>
# include<algorithm>
# define lowbit(x) (x&(-x))
using namespace std;
const int maxn=200010;
const int mod=16777216;
typedef long long LL;
struct FenwickTree{
	LL c[maxn],n;
	
	void init(LL nn){
		n=nn;
		memset(c,0,sizeof(c));
	}
	
	void add(LL x,LL d){
		while(x<=n){
			c[x]+=d;
			x+=lowbit(x);
		}
	}
	
	LL sum(int x){
		LL res=0;
		while(x>0){
			res+=c[x];
			x-=lowbit(x);
		}
		return res;
	}
	
};
FenwickTree f1,f2,f3;
int less_l[maxn],less_r[maxn];
LL s[maxn];
LL n,a[maxn];
int main(){
	scanf("%lld",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld",&a[i]);
	LL ans=0;
	f1.init(n);
	for(int i=1;i<=n;i++){
		less_l[i]=f1.sum(a[i]);
		f1.add(a[i],1);
	}
	f1.init(n);
	for(int i=n;i>=1;i--){
		less_r[i]=f1.sum(a[i]);
		f1.add(a[i],1);
	}
	//1x2x
	f3.init(n);
	for(int i=1;i<=n;i++){
		LL s=f3.sum(a[i]);
		s=(i-1)*less_l[i]-s;
		f3.add(a[i],i);
		s-=less_l[i]*(less_l[i]-1)/2;
		ans+=s*(n-i-less_r[i]);
		ans=(ans+mod)%mod;
		//printf("i:%d %lld\n",i,ans);
	}
	//printf("%lld\n",ans);
	//13xx
	f1.init(n);
	for(int i=n;i>=1;i--){
		LL s=f1.sum(a[i]);
		s-=less_r[i]*(less_r[i]-1)/2;
		ans+=s*(n-i-less_r[i]);
		f1.add(a[i],a[i]-1);
		ans=(ans+mod)%mod;
	}//printf("%lld\n",ans);
	//F1***
	for(int i=1;i<=n;i++){
		LL big=n-i-less_r[i];
		ans-=big*(big-1)/2*(big-2)/3;
		ans=(ans+mod)%mod;
	}
	//printf("%lld\n",ans);
	//F1234
	f2.init(n);f3.init(n);//f4.init(n);
	for(int i=1;i<=n;i++){
		LL s1=less_l[i];
		LL s2=f2.sum(a[i]);
		LL s=f3.sum(a[i]);
		f3.add(a[i],s2);
		f2.add(a[i],s1);
		ans+=s;
		ans=(ans+mod)%mod;
	}
	printf("%lld\n",ans);
	return 0;
}
