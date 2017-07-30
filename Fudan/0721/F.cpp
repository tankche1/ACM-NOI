# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int tcase,n;
double a[maxn],b[maxn],c[maxn];
double eps=0.00000001;

double get(double x){
	double ans=-1000000000.0,t;
	for(int i=1;i<=n;i++){
		t=x*x*a[i]+x*b[i]+c[i];
		if(t>ans) ans=t;
	}
	//printf("x:%.4lf ans:%.4lf\n",x,ans);
	return ans;
}

int main(){
	int aa,bb,cc;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			//scanf("%d%d%d",&aa,&bb,&cc);
			//a[i]=(double)aa;b[i]=double(bb);c[i]=(double)cc;
			scanf("%lf%lf%lf",&a[i],&b[i],&c[i]);
		}
		double L=0.0000,R=1000.0000,M1,M2;
		while(L+eps<R){
			M1=L+(R-L)/3.0;M2=R-(R-L)/3.0;//printf("L:%.4lf R:%.4lf M1:%.4lf M2:%.4lf\n",L,R,M1,M2);
			if(get(M1)<get(M2)) R=M2;
			else L=M1;
		}
		printf("%.4lf\n",get((L+R)/2.0));
	}
	return 0;
}
