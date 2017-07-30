# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
typedef long long LL;

LL tt;
LL gcd(LL a,LL b){
	return b==0?a:gcd(b,a%b);
}

int main(){
	//freopen("in.txt","r",stdin);
	int tcase,tnum=0;
	LL n,s1,v1,s2,v2,ans,lcm,val,lcmnum,weight;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%lld%lld%lld%lld%lld",&n,&s1,&v1,&s2,&v2);
		if(!(v1*s2>=v2*s1)) {swap(s1,s2),swap(v1,v2);}
		//printf("%I64d %I64d %I64d %I64d %I64d\n",n,s1,v1,s2,v2);
		lcm=s1/gcd(s1,s2)*s2;
		lcmnum=n/lcm;
		if(lcmnum)
			lcmnum--;
		val=lcmnum*(lcm/s1)*v1;
		n-=lcmnum*lcm;
		if(s1>s2) swap(s1,s2),swap(v1,v2);
		ans=0;
		for(LL i=0;i<=n/s2;i++){
			ans=max(ans,i*v2+((n-s2*i)/s1)*v1);
		}
		val+=ans;
		printf("Case #%d: ",++tnum);
		printf("%lld\n",val);
	}
	return 0;
}
