# include<stdio.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const  double eps=(double)0.01;
const int maxn=510;
double a,b,c,d;
double num[maxn];
	
bool equal(double a,double b){
	if(a>b) return a-b<eps;
		else return b-a<eps;
}
int main()
{
	int T,n;
	double x,y,w,z;
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
				scanf("%lf",&num[i]);
		if(n<=4) puts("YES");
		else{
			x=num[2]-num[1];y=num[3]-num[2];w=num[4]-num[3];z=num[1];
			a=(double)(w+x-2.0*y)/6.0;
			b=(double)(y-x-12.0*a)/2.0;
			c=(double)x-7.0*a-3.0*b;
			d=(double)z-a-b-c;
			bool ok=true;
			for(int i=5;i<=n;i++){
				if(!equal(a*(((double)i*i*i))+b*i*i+c*i+d,num[i])) {ok=false;break;}
			}
			if(ok) puts("YES");
				else puts("NO");
		}
	}
	return 0;
}
