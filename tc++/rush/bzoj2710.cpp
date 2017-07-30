#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const double eps=1e-12;
const double INF=~0U>>1;
double px[2],py[2],pv;
double wx[2],wy[2],wv;
double close,far;
double pgx,pgy,wgx,wgy;
double tim;
	
double calc(double t){
	double tt=t-((int)(t/(tim*2.0)))*2.0*tim;
	if(tt>tim) tt=2.0*tim-tt;
	//printf("t:%.5lf tt:%.5lf\n",t,tt);
	return (wx[0]+tt*wgx-px[0]-t*pgx)*(wx[0]+tt*wgx-px[0]-t*pgx)+(wy[0]+tt*wgy-py[0]-t*pgy)*(wy[0]+tt*wgy-py[0]-t*pgy);
}

int main(){
	while(scanf("%lf%lf%lf%lf%lf",&px[0],&py[0],&px[1],&py[1],&pv)==5){
	scanf("%lf%lf%lf%lf%lf",&wx[0],&wy[0],&wx[1],&wy[1],&wv);
	scanf("%lf%lf",&close,&far);
	double aa=sqrt((px[1]-px[0])*(px[1]-px[0])+(py[1]-py[0])*(py[1]-py[0]));
	if(aa==0) pgx=0,pgy=0;else pgx=(px[1]-px[0])/(aa*1.0),pgy=(py[1]-py[0])/(aa*1.0);
	
	aa=sqrt((wx[1]-wx[0])*(wx[1]-wx[0])+(wy[1]-wy[0])*(wy[1]-wy[0]));
	if(aa==0) wgx=0,wgy=0;else wgx=(wx[1]-wx[0])/(aa*1.0),wgy=(wy[1]-wy[0])/(aa*1.0);
		
	tim=sqrt((wx[1]-wx[0])*(wx[1]-wx[0])+(wy[1]-wy[0])*(wy[1]-wy[0]))/(wv*1.0);
	printf("tim:%.6lf\n",tim);
	
	double L=0,R=INF,M1,M2;
	while(R-L>eps){
		M1=L+(R-L)/3.0;
		M2=L+(R-L)/1.5;
		if(calc(M1)<calc(M2)) R=M2;
		else L=M1;
	}
	double dis=sqrt(calc((L+R)/2.0));
	printf("%.7lf\n",dis);
	if(dis<=close) printf("Dangerous\n");
	else if(dis>far) puts("Miss");
	else puts("Perfect");
	}
	return 0;
}
