# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
double a,b,c,d,e,f;
int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&a,&b,&c,&f,&e,&d);
    double D=b*b+c*c-d*d;
    double E=a*a+c*c-e*e;
    double F=a*a+b*b-f*f;
    double V;
    V=4*a*a*b*b*c*c-a*a*D*D-b*b*E*E-c*c*F*F+D*E*F;
    V=sqrt(V);
    V=V/12.0;
    printf("%.4lf\n",V);
    return 0;
}
