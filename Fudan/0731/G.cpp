# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
double w,h,W,H;
double now;
const double eps=1e-6;
int main(){
    freopen("garage.in","r",stdin);
    freopen("garage.out","w",stdout);
    scanf("%lf%lf%lf%lf",&W,&H,&w,&h);
    now=0;int needx=0,needy=0;
    while(now+w<=W){
        needx++;
        now=now+w-eps+w;
    }
    now=0;
    while(now+h<=H){
        needy++;
        now=now+h-eps+h;
    }
    int ans=needx*needy;
    printf("%d\n",ans);
    return 0;
}
