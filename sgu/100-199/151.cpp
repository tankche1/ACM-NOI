# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
double c,b,m;
const double eps=1e-8;
int dcmp(double a){
    if(a<-eps) return -1;
    else if(a>eps) return 1;
    else return 0;
}
int main(){
    scanf("%lf%lf%lf",&c,&b,&m);
    double x=(4*m*m-b*b-c*c)/2/c;
    double y=b*b-x*x;
    if(dcmp(y)<0) puts("Mission impossible");
    if(dcmp(y)==0) y=0;
    if(dcmp(x)==0) x=0;
    if(y!=0) y=sqrt(y);
    printf("0.00000 0.00000\n");
    printf("%.5lf 0.00000\n",c);
    printf("%.5lf %.5lf\n",x,y);
    return 0;
}
