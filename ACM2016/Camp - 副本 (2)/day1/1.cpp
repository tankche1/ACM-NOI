/*
sgu 111
高精度开方
*/

# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
double xA,xB,xC,yA,yB,yC;
double xP,yP;
int main(){
    scanf("%lf%lf%lf%lf%lf%lf",&xA,&yA,&xB,&yB,&xC,&yC);
    xP=xC;yP=yC;
    double ans=sqrt((xP-xA)*(xP-xA)+(yP-yA)*(yP-yA))+2*sqrt((xP-xB)*(xP-xB)+(yP-yB)*(yP-yB))+3*sqrt((xP-xC)*(xP-xC)+(yP-yC)*(yP-yC));
    printf("%.10lf\n",ans);
	return 0;
}
