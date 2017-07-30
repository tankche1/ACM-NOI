# include<stdio.h>
# include<string.h>
# include<iostream>
# include<math.h>
# include<algorithm>
using namespace std;
const double pi=acos(-1.0);
const double eps=1e-10;
int n,r,v;
double s;

double cal(double x){
    //printf("x:%.3lf cal:%.3lf\n",x,sin(x)*r+(pi/2.0-x)*r);
    return cos(x)*r+(pi/2.0-x)*r;
}

int main(){
    double t;
    int st,ed;
    scanf("%d%d%d",&n,&r,&v);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&st,&ed);s=ed-st;
        int quan=(int)(s/(2*pi*r));
        //printf("quan:%d\n",quan);
        t=quan*2*pi*r/(v*1.0);
        //printf("t:%Lf\n",t);
        s=s-quan*2*pi*r;
        //printf("s:%.3lf\n",s);
        double ll=-pi/2.0,rr=pi/2.0,m;
        for(int ttt=1;ttt<=100;ttt++){
            m=(ll+rr)/2.0;
            //printf("ll:%.3lf rr:%.3lf m:%.3lf\n",ll,rr,m);
            if(cal(m)*2<(s)) rr=m;
            else ll=m;
        }
       // printf("ll:%.3lf cal:%.3lf\n",ll,cal(ll));
        //t+=(pi-2*ll)*r/(v*1.0);
        t+=(s/2-r*cos(ll))*2/(v*1.0);
        printf("%.12lf\n",t);
        //cout << t << endl;
    }
    return 0;
}
