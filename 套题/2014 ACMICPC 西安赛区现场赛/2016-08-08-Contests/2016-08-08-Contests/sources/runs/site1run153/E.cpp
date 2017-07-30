#include <bits/stdc++.h>
using namespace std;

const double PI = acos(-1.0);
const double eps = 1e-8;
const int MAXN = 22222;
int sig(double x) {
    if (fabs(x)<eps) return 0;
    return x<0?-1:1;
}
void reg(double &t) {
    t=t/180*PI;
}
struct Point {
    double x,y;
    Point (double _x=0,double _y=0):x(_x),y(_y){}
    double len() const {
        return sqrt(x*x+y*y);
    }
    Point unit() const  {
        double l=len();
        return Point(x/l,y/l);
    }
    void read() {
        scanf("%lf%lf",&x,&y);
    }
    Point turn(double t) { ///counter-clockerwise
        return Point(x*cos(t)-y*sin(t),x*sin(t)+y*cos(t));
    }
    Point operator*(double a) const {
        return Point(a*x,a*y);
    }
    double dot(Point b) const {
        return x*b.x+y*b.y;
    }
    double operator*(Point b) const {
        return x*b.y-b.x*y;
    }
    Point operator-(Point b) const {
        return Point(x-b.x,y-b.y);
    }
    Point operator+(Point b) const {
        return Point(x+b.x,y+b.y);
    }
};

struct Shan {
    Point o,d;
    double t;
    Shan(Point _o=Point(),Point _d=Point(),double _t=0):o(_o),d(_d),t(_t){}
    bool in (Point a) {
        Point v=d.turn(t),cl=a-o;
        if (sig(cl.len()-d.len())==1) return false;
        if (sig(cl*v)==0&&sig(cl.dot(v))>=0||sig(cl*d)==0&&sig(cl.dot(d))>=0) return true;
        return sig(d*cl)==1&&sig(cl*v)==1;
    }
    pair<bool,Point> qie(Point ve) {
        ve=ve.unit()*(d.len()/2);
        Point tmp=ve.turn(PI/2);
        if (in(o+tmp)) {
            return make_pair(1,o+tmp*2);
        }
        tmp=tmp*-1;
        if (in(o+tmp)) {
            return make_pair(1,o+tmp*2);
        }
        return make_pair(0,Point());
    }

};

Point pos,P[MAXN];
Shan sa[MAXN*2];int sn;

struct Sbx {
    Point a,b,c,d;
    Sbx(Point _a=Point(),Point _b=Point(),Point _c=Point(),Point _d=Point()):
        a(_a),b(_b),c(_c),d(_d){}
    bool in(Point v) {
        int s1= sig((a-v)*(b-v)),s2=sig((b-v)*(c-v)),s3=sig((c-v)*(d-v)),s4=sig((d-v)*(a-v));
        if (s1==0&&sig((a-v).dot(b-v))<=0) return true;
        if (s2==0&&sig((b-v).dot(c-v))<=0) return true;
        if (s3==0&&sig((c-v).dot(d-v))<=0) return true;
        if (s4==0&&sig((d-v).dot(a-v))<=0) return true;
        return s1==s2&&s2==s3&&s3==s4&&s4==s1;
    }
};
Sbx sba[MAXN*2];int sbn;
Sbx gen(Point a,Point b,Point v) {
    return Sbx(a,b,b+v,a+v);
}

bool ans[MAXN];

int main() {
    int casen;
    scanf("%d",&casen);
    for (int pp=1;pp<=casen;pp++) {
        int N,M;double theta,R;
        Point V,D;Shan ns;
        scanf("%d%d%lf%lf",&N,&M,&theta,&R);
        reg(theta);
        pos.read();
        V.read();
        D.read();
        for (int i=1;i<=N;i++) P[i].read();

        ns=Shan(pos,(D.unit().turn(-theta/2))*R,theta);
        double lt=0;
        for (int i=1,typ;i<=M;i++) {
            double nt;
            scanf("%d%lf",&typ,&nt);
            pair<bool,Point> tt=ns.qie(V);
            Point v=V.unit()*(nt-lt);
            sa[sn++]=ns;
            sba[sbn++]=gen(ns.o,ns.o+ns.d,v);
            sba[sbn++]=gen(ns.o,ns.o+ns.d.turn(ns.t),v);
            ns.o=ns.o+v;
            sa[sn++]=ns;
            if (tt.first) {
                Point qp=tt.second;
                sba[sbn++]=gen(ns.o,qp,v);
            }
            if (typ==1) {
                double t;
                scanf("%lf",&t);
                reg(t);
                t=-t;
                ns.d=ns.d.turn(t);
                sa[sn++]=ns;
            }
            else if (typ==2) {
                double t;
                scanf("%lf",&t);
                reg(t);
                t=-t;
                V=V.turn(t);
            }
            lt=nt;
        }

        for (int i=1;i<=N;i++) {
            for (int j=0;j<sn;j++) ans[i]|=sa[j].in(P[i]);
            for (int j=0;j<sbn;j++) ans[i]|=sba[j].in(P[i]);
        }

        printf("Case #%d: ",pp);
        for (int i=1;i<=N;i++) putchar('1'-ans[i]);
        printf("\n");

        for (int i=0;i<=N;i++) ans[i]=0;
        sbn=sn=0;
    }
}
/*
100
3 2 90 3
0 0 0 1 0 1
50 1
-1 0
-100 0
1 1 180
1 100 0
*/
