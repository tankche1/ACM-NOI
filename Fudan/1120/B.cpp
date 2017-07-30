# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
double x1,y1,x2,y2,v,t;
double vx,vy,wx,wy;

double calc(double ti){
    double res=((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2))/((ti*ti)*1.0);
    res+=vx*vx+vy*vy;
    res+=(2*vx*(x1-x2)+2*vy*(y1-y2))/(ti*1.0);
    return res;
}

double calc2(double ti){
    double res=((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)-v*v*t*t)/((ti*ti)*1.0);
    res+=wx*wx+wy*wy;
    res+=(2*wx*(x1-x2)+2*wy*(y1-y2)-2*v*v*t)/(ti*1.0);
    return res;
}
int main(){
    scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&v,&t,&vx,&vy,&wx,&wy);
    double l,r,mid;
    l=0,r=t;
    if(calc(t)<=v*v){
        for(int i=1;i<=200;i++){
            mid=(l+r)/2.0;
            if(calc(mid)<=v*v) r=mid;
            else l=mid;
        }
    }
    else{
        x1=x1+t*vx;y1=y1+t*vy;
        l=0;r=INF*1.0;
        for(int i=1;i<=200;i++){
            mid=(l+r)/2.0;
            if(calc2(mid)<=v*v) r=mid;
            else l=mid;
        }
        l+=t;
    }
    printf("%.18lf\n",l);
    return 0;
}
