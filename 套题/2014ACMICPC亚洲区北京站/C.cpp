# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
int w,h;
int x1,y1,x2,y2;
double tx,ty;

double getx(double a){
    a=a-(LL)a/(2*w)*2*w;
    if(a<=w) return a;
    else return 2*w-a;
}

double gety(double a){
    a=a-(LL)a/(2*h)*2*h;
    if(a<=h) return a;
    else return 2*h-a;
}

int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}

void exgcd(int a,int b,int &d,LL &x,LL &y){
    if(!b) {d=a;x=1;y=0;}
    else{
        exgcd(b,a%b,d,y,x);y-=x*(a/b);
    }
}

int main(){
    LL a,b;
    int T;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d%d",&w,&h);
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        printf("Case #%d:\n",Tcase);

        if(x1==x2&&y1==y2){
            printf("%.1lf %.1lf\n",x1,y1);continue;
        }

        tx=(2*w-x1-x2)/2.0;
        ty=(2*h-y1-y2)/2.0;

        if(x1==x2){
            printf("%.1lf %.1lf\n",getx(x1+ty),gety(y1+ty));
            continue;
        }

        if(y1==y2){
            printf("%.1lf %.1lf\n",getx(x1+tx),gety(y1+tx));
            continue;
        }

        if(tx-(int)tx!=ty-(int)ty) {puts("Collision will not happen.");continue;}

        //printf("tx:%.1lf ty:%.1lf\n",tx,ty);
        if(tx==ty) {
            printf("%.1lf %.1lf\n",getx(x1+tx),gety(y1+tx));
            continue;
        }

        int d=gcd(w,h);
        LL gd=(LL)w*h/d;
        if((LL)(ty-tx)%d) {puts("Collision will not happen.");continue;}
        exgcd(w,-h,d,a,b);
        /*while(a<0||b<0){
            a+=gd/w;b+=gd/h;//puts("hei");
        }*/
        //printf("a:%d b:%d xt:%I64d yt:%I64d\n",w,-h,a,b);
        a=a*(LL)(ty-tx)/d;b=b*(LL)(ty-tx)/d;

        double ti=tx+a*w;
        ti=ti-((LL)ti/(gd)*gd);
        if(ti<0) ti+=gd;
        //printf("a:%I64d b:%I64d\n",a,b);
        //printf("tt:%.1lf\n",ti);
        printf("%.1lf %.1lf\n",getx(x1+ti),gety(y1+ti));
    }
    return 0;
}
