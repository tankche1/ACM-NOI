# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxlen=1000010;
const int mod=1000000007;
typedef long long LL;
char s[maxlen],t[maxlen];
LL a,b,c,d,len;

LL fast_pow(LL a,LL p){
	if(p==0) return 1;
	LL half=fast_pow(a,p>>1);
	if(p&1) return ((half*half%mod)*a%mod);
		else return half*half%mod;
}

LL rev(LL a){
	return fast_pow(a,mod-2);
}

LL plus(LL a,LL b){
	return (a+b+mod)%mod;
}

LL mul(LL a,LL b){
	LL c=a*b;
	if(c>=mod) return c%mod;
	return c;
}

LL nx,ny,mx,my;
int main(){
	scanf("%s%s",s,t);
	scanf("%lld%lld%lld%lld",&a,&b,&c,&d);
	len=strlen(s);nx=0;ny=0;
	for(int i=0;i<len;i++) {nx=nx*10+s[i]-'0';ny=ny*10+s[i]-'0';if(nx>=mod-1) nx%=mod-1;if(ny>=mod) ny%=mod;}
	len=strlen(t);mx=0;my=0;
	for(int i=0;i<len;i++) {mx=mx*10+t[i]-'0';if(mx>=mod-1) mx%=mod-1;my=my*10+t[i]-'0';if(my>=mod) my%=mod;}
	
	if(a!=1){//puts("hei");
		LL aa=a,bb=b,now=1;
		//printf("n:%lld m:%lld\n",n,m);puts(s);puts(t);
		//printf("nx:%lld mx:%lld\n",nx,mx);
		LL k=fast_pow(a,plus(mx,-1));
		LL p=b*rev(a-1)%mod;
		a=k*c%mod;b=((((k-1)*p)%mod)*c+d)%mod;//printf("a:%lld b:%lld\n",a,b);
		now=((now*fast_pow(a,plus(nx,-1))%mod)+(b*rev(a-1)%mod)*((fast_pow(a,plus(nx,-1))-1+mod)%mod))%mod;//printf("now:%lld\n",now);
		now=((now*fast_pow(aa,plus(mx,-1))%mod)+(bb*rev(aa-1)%mod)*((fast_pow(aa,plus(mx,-1))-1)+mod)%mod)%mod;
		printf("%lld\n",now);
	}
	else{
		LL aa=a,bb=b,now=1;
		a=c;b=((b*c%mod)*(plus(my,-1))+d)%mod;
		if(a==1){
			now=(now+(plus(ny,-1))*b)%mod;
		}
		else{
			now=((now*fast_pow(a,plus(nx,-1))%mod)+(b*rev(a-1)%mod)*((fast_pow(a,plus(nx,-1))-1+mod)%mod))%mod;
		}
		now=(now+bb*(plus(my,-1)))%mod;
		printf("%lld\n",now);
	}
	return 0;
}
/*
2 2 2 3 2 3
*/
