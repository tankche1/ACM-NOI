# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1000010;
double pi=acos(-1.0);
double eps=1e-10;
struct point{
    double x,y;
    point(){}
    point(double x,double y):x(x),y(y) {}
};
point ori;
int n;
point p[maxn];
point operator - (point A,point B){return point(A.x-B.x,A.y-B.y);}
bool operator == (const point A,const point B) {return A.x==B.x&&A.y==B.y;}

double Dot(point A,point B){return A.x*B.x+A.y*B.y;}
double Cross(point A,point B){return A.x*B.y-A.y*B.x;}
double Length(point A) {return sqrt(A.x*A.x+A.y*A.y);}

int dcmp(double x){
    if(fabs(x)<eps) return 0;
    return x<0?-1:1;
}

double r1=0,r2=1<<31;

double DistanceToSegment(point P,point A,point B){
    if(A==B) return Length(P-A);
    if(dcmp(Dot(B-A,P-A))<0) return Length(P-A);
    if(dcmp(Dot(A-B,P-B))<0) return Length(P-B);
    return fabs(Cross(B-A,P-A))/Length(B-A);
}

int main(){
    scanf("%d",&n);
    scanf("%lf%lf",&ori.x,&ori.y);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf",&p[i].x,&p[i].y);
        r1=max(r1,Length(p[i]-ori));
    }r2=r1;
    p[n+1]=p[1];
    for(int i=1;i<=n;i++){
        r2=min(r2,DistanceToSegment(ori,p[i],p[i+1]));
    }
    printf("%.8lf\n",(r1*r1-r2*r2)*pi);
    return 0;
}
