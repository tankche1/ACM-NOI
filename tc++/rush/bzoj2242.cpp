#include<stdio.h>
#include<string.h>
# include<math.h>
# include<map>
#include<algorithm>
using namespace std;
typedef long long LL;
LL y,z,p;

LL pow_mod(LL a,LL b,LL n){
	if(b==0) return 1;
	LL half=pow_mod(a,b>>1,n);
	//printf("a:%lld b:%lld half:%lld n:%lld %lld %lld\n",a,b,half,n,(half*half%n),(half*half%n)*a%n);
	if(b&1) {//printf("%lld\n",(half*half%n)*a%n);
		return (half*half%n)*a%n;}
	else {//printf("%lld\n",(half*half%n));
		return (half*half%n);}
}

map<int,int> x;
LL log_mod(LL a,LL b,LL n){
	if(a==0&&b==0) return 1;
	if(a==0) return -1;
	//if(b==1) return pow_mod(a,n-2,n);
	x.clear();
	LL m,v,e=b,i;
	m=sqrt(n)+1;v=pow_mod(pow_mod(a,m,n),n-2,n);
	for(int i=0;i<m;i++){
		LL t=pow_mod(a,i,n);
		if(!x.count(t)) x[t]=i;
	}
	for(int i=0;i<m;i++){
		if(x.count(e)&&i*m+x[e]!=0) return i*m+x[e];
		e=e*v%n;
	}
	return -1;
}
int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int tcase,op;
	scanf("%d%d",&tcase,&op);
	while(tcase--){
		scanf("%lld%lld%lld",&y,&z,&p);
		if(op==1){
			printf("%lld\n",pow_mod(y,z,p));
		}
		else if(op==2){
			z%=p;y%=p;
			if(!y&&z) {puts("Orz, I cannot find x!");continue;}
			LL t=pow_mod(y,p-2,p);//printf("t:%lld\n",t);
			printf("%lld\n",t*z%p);
		}
		else{
			y%=p;z%=p;LL ans=log_mod(y,z,p);
			if(ans==-1) puts("Orz, I cannot find x!");
			else printf("%lld\n",ans);
		}
	}
	return 0;
}
