# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=410;
const int maxm=3010;
const double eps=1e-8;
int n,m;
struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y){}
}p[maxn];
Point p1,p2;

typedef Point Vector;

Vector operator + (Vector A, Vector B) {return Vector(A.x + B.x, A.y + B.y);  }
Vector operator - (Vector A, Vector B) {return Vector(A.x - B.x, A.y - B.y);  }
Vector operator * (Vector A, double p) {return Vector(A.x * p, A.y * p);  }
Vector operator / (Vector A, double p) {return Vector(A.x / p, A.y / p);  }
double Cross(Vector A,Vector B){return A.x*B.y-A.y*B.x;}
double Dot(Point A,Point B){return A.x*B.x+A.y*B.y;}
int dcmp(double a){if(fabs(a)<eps) return 0;return a<0?-1:1;}
double Length(Vector v){return sqrt(v.x*v.x+v.y*v.y);}

bool OnSegment(Point p,Point a1,Point a2){//不包括线段的端点
    return dcmp(Cross(a1-p,a2-p)==0)&&dcmp(Dot(a1-p,a2-p))<0;
}

bool same_point(Point A,Point B){
    return dcmp(A.x-B.x)==0&&dcmp(A.y-B.y)==0;
}

Point GetLine(Point P,Vector v,Point Q,Vector w){
    Vector u=P-Q;
    double t=Cross(w,u)/Cross(v,w);
    return P+v*t;
}

bool SegmentIntersection(Point a1,Point a2,Point b1,Point b2){
    double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1),
           c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
    return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}

int isPointInPolygon(Point p,Point *poly){
    int wn=0;
    for(int i=1;i<=n;i++){
        if(same_point(p,poly[i])) return -1;
        if(OnSegment(p,poly[i],poly[i+1])) return -1;
        int k=dcmp(Cross(poly[i+1]-poly[i],p-poly[i]));
        int d1=dcmp(poly[i].y-p.y);
        int d2=dcmp(poly[i+1].y-p.y);
        if(k>0&&d1<=0&&d2>0) wn++;
        if(k<0&&d2<=0&&d1>0) wn--;
    }
    if(wn!=0) return 1;
    return 0;
}

int nowp;
Point a,b;

void update(Point c){if(nowp==0) a=c;else b=c;nowp++;}

bool cmp(Point A,Point B){return Cross(A-p[1],B-p[1])<0;}
void get_Convex(){
    int minf=1;
    for(int i=2;i<=n;i++)
        if(p[i].x<p[minf].x||(p[i].x==p[minf].x&&p[i].y<p[minf].y)) minf=i;
    swap(p[1],p[minf]);
    sort(p+2,p+n+1,cmp);
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%lf%lf",&p[i].x,&p[i].y);
    get_Convex();p[n+1]=p[1];
    //for(int i=1;i<=n;i++) printf("%.3lf %.3lf\n",p[i].x,p[i].y);
    scanf("%d",&m);
    double ans=0;

    for(int tt=1;tt<=m;tt++){
        scanf("%lf%lf%lf%lf",&p1.x,&p1.y,&p2.x,&p2.y);nowp=0;ans=0;
        for(int i=1;i<=n;i++)
            if(dcmp(Cross(p1-p[i],p2-p[i]))==0&&dcmp(Cross(p1-p[i+1],p2-p[i+1]))==0) nowp=5;
        for(int i=1;i<=n;i++){
            if(same_point(p[i],p1)) {update(p1);}//避免两个都在顶点上
            if(same_point(p[i],p2)) {update(p2);}
        }
        for(int i=1;i<=n;i++){
            if(OnSegment(p1,p[i],p[i+1])) update(p1);
            if(OnSegment(p2,p[i],p[i+1])) update(p2);//同一个线段的话不算
        }
        for(int i=1;i<=n;i++){
            if(OnSegment(p[i],p1,p2)) update(p[i]);
            if(SegmentIntersection(p1,p2,p[i],p[i+1])) update(GetLine(p2,p2-p1,p[i],p[i+1]-p[i]));
        }
       // printf("nowp:%d\n",nowp);
        if(nowp==2) {
            ans+=Length(b-a);
        }
        else if(nowp==1){
            if(isPointInPolygon(p1,p)==1) ans+=Length(p1-a);
            else if(isPointInPolygon(p2,p)==1) ans+=Length(p2-a);
        }
        else if(nowp==0){
            if(isPointInPolygon(p1,p)==1&&isPointInPolygon(p2,p)==1) ans+=Length(p2-p1);
        }
        else {}
        printf("%.2lf\n",ans);
    }
    return 0;
}
