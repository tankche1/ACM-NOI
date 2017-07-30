#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
LL a,b,x,y,d;
LL A1,A2,B1,B2;

void gcd(LL a,LL b,LL &d,LL &x,LL &y){
	if(b==0){
		x=1;y=0;d=a;return;
	}
	gcd(b,a%b,d,y,x);
	y-=a/b*x;
}

int main(){
	int tcase;scanf("%d",&tcase);
	while(tcase--){
		scanf("%lld%lld%lld%lld",&a,&b,&x,&y);
		if(a==0&&b==0){
			if(x==0&&y==0) puts("Y");
				else puts("N");
			continue;
		}
		gcd(a,b,d,A1,A2);
		if(x%d!=0) {puts("N");continue;}
		x/=d;A1*=x;A2*=x;
		gcd(a,b,d,B2,B1);
		if(y%d!=0) {puts("N");continue;}
		y/=d;B1*=y;B2*=y;
		//printf("A1:%lld A2:%lld B1:%lld B2:%lld\n",A1,A2,B1,B2);
		bool ok=false;
		for(int i=0;i<2;i++)
				for(int k=0;k<2;k++){
						LL AA1=A1+i*b/d,AA2=A2-i*a/d,BB2=B2+k*b/d,BB1=B1-k*a/d;
						if(((AA1&1)==(BB1&1))&&((AA2&1)==(BB2&1))) {ok=true;goto Loop;}
					}
					Loop:
					//printf("oh\n");
					if(ok) puts("Y");
						else puts("N");
	}
	return 0;
}
