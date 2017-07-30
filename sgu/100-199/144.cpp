# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
int main(){
    double x,y,z,a1,a2;
    scanf("%lf%lf%lf",&x,&y,&z);
    x*=60;y*=60;
    a1=(y-x-z)*(y-x-z);
    a2=(y-x)*(y-x);
    double ans=1-a1/a2;
    printf("%.7lf\n",ans);
    return 0;
}
