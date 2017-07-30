#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxn=10010;
const double eps=1e-12;
int n;
double Eu,s[maxn],v[maxn],k[maxn];
int main(){
	scanf("%d%lf",&n,&Eu);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf",&s[i],&k[i],&v[i]);
	double El=-10000,Er=0,t;
	while(El+eps<Er){
		 double E=(El+Er)/2.0;
		//	printf("El:%.15lf Er:%.15lf E:%.15lf\n",El,Er,E);
		double power=0;
		double V;
		t=0;
		for(int i=1;i<=n;i++){
			double vl=v[i],vr=s[i]!=0?sqrt(Eu/s[i]/k[i])+v[i]:0;V=(vl+vr)/2.0;
			while(vr-vl>eps){
				V=(vl+vr)/2.0;
				if(V*(V-v[i])*V*k[i]*E*2+1>0)
					vl=V;
				else vr=V;
			}
			V=(vl+vr)/2.0;
			t+=s[i]/(V*1.0);
			power+=k[i]*(V-v[i])*(V-v[i])*s[i];
		}
		if(power<Eu)
			El=E;
		else Er=E;
	}
	printf("%.10lf\n",t);
	return 0;
}
