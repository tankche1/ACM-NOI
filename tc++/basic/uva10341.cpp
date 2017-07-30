# include<stdio.h>
# include<math.h>
# include<string.h>
# include<algorithm>
using namespace std;
const double eps=1e-14;
int p,q,r,s,t,u;
//#define F(x) (p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*(x)*(x)+u)
double F(double x){
	return p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u;
}
int main(){
	while(scanf("%d%d%d%d%d%d",&p,&q,&r,&s,&t,&u)!=EOF){
	double f0 = F(0), f1 = F(1);
    if(f1 > eps || f0 < -eps) printf("No solution\n");
			else{
				double l=0.0,r=1.0;
				for(int i=0;i<100;i++){
					if(F((l+r)*0.5)>=0) l=(l+r)*0.5;
						else r=(l+r)*0.5;
							//printf("l:%.4lf r:%.4lf\n",l,r);
				}
				printf("%.4lf\n",l);
			}
	}
	return 0;
}
