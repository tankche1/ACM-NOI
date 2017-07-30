# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL P,K;
LL j1,j2;
LL a,b,x,y,d;
LL p1,p2,n1,n2;

inline void gcd(LL a,LL &x,LL b,LL &y,LL &d){
	if(!b){
		d=a;x=1;y=0;return;
	}
	gcd(b,y,a%b,x,d);
	y-=a/b*x;
}

//# define abs(x) (x>0?x:-x)
int main(){
	scanf("%lld%lld%lld%lld",&j1,&j2,&P,&K);
//	if(j1>j2) swap(j1,j2);
	gcd(j1,x,j2,y,d);x*=P/d;y*=P/d;//printf("%lld %lld %lld %d %d %d\n",x,y,d,abs(0),abs(999),abs(-9989));
	LL d1=j2/d,d2=j1/d;//scanf("%d",&K);
	if(abs(P)%d) goto Loop;
	while((abs(x+d1)+abs(y-d2))<(abs(x)+abs(y))) x+=d1,y-=d2;//printf("%lld %lld\n",x,y);;
	while((abs(x-d1)+abs(y+d2))<(abs(x)+abs(y))) x-=d1,y+=d2;//printf("%lld %lld\n",x,y);
	 /* for(;abs(x-d1)+abs(y+d2)<abs(x)+abs(y);x-=d1,y+=d2); //printf("%lld %lld\n",a,b);
        for(;abs(x+d1)+abs(y-d2)<abs(x)+abs(y);x+=d1,y-=d2);// printf("%lld %lld\n",a,b);;*/
	//printf("%lld %lld %lld\n",x,y,d);
	if(((abs(x)+abs(y))>K)) {Loop:
		puts("NO");return 0;}
		if(1>2){
			Tank:
		int a=(K-abs(x)-abs(y))/2;
		p1=x>0?x+a:a;n1=x<0?-x+a:a;
		p2=y>0?y:0;n2=y<0?-y:0;
		printf("YES\n%lld %lld %lld %lld\n",p1,n1,p2,n2);
		return 0;
	}
	if((abs(x+y)%2)==(abs(K)%2)){//puts("shit");
		goto Tank;
	}
	else if((j1/d+j2/d)%2==0) goto Loop;
	else{
		if(abs(x+j2/d)+abs(y-j1/d)<=K) {x+=j2/d,y-=j1/d;goto Tank;}
		else if(abs(x-j2/d)+abs(y+j1/d)<=K) {x-=j2/d,y+=j1/d;goto Tank;}
		else goto Loop;
	}
	return 0;
}
