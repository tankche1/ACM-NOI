# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const double eps=1.5e-6;

struct Point{
    double x,y;
    Point(double x=0,double y=0):x(x),y(y) {}
};

int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

typedef Point Vector;

Vector operator + (Vector A, Vector B) {return Vector(A.x + B.x, A.y + B.y);  }
Vector operator - (Vector A, Vector B) {return Vector(A.x - B.x, A.y - B.y);  }
Vector operator * (Vector A, double p) {return Vector(A.x * p, A.y * p);  }
Vector operator / (Vector A, double p) {return Vector(A.x / p, A.y / p);  }


double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

struct Circle {
  Point c;
  double r;
  Circle(Point c, double r):c(c),r(r) {}
  Point point(double a) {
    return Point(c.x + cos(a)*r, c.y + sin(a)*r);
  }
};

double angle(Vector v) {
  return atan2(v.y, v.x);
}

int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
  double d = Length(C1.c - C2.c);
   if( dcmp(C1.r - C2.r)>0)
        swap(C1,C2);
  if(dcmp(d) == 0) {
    //if(dcmp(C1.r - C2.r) == 0) return -1; // 重合，无穷多交点
    if(dcmp(C1.r - C2.r) == 0) {
        sol.push_back(C1.c+Point(0,C1.r)),sol.push_back(C1.c-Point(0,C1.r));return 2;
    }
    return 0;
  }
  if(dcmp(C1.r + C2.r - d) < 0) return 0;
  if(dcmp(fabs(C1.r-C2.r) - d) > 0) return 0;
  if(dcmp(C1.r + C2.r - d) == 0 || dcmp(fabs(C1.r - C2.r)-d) == 0){
        Point p = C1.c-C2.c;
        sol.push_back(C2.c + p / Length(p) * C2.r);
        return 1;
    }

  double a = angle(C2.c - C1.c);
  double da = acos((C1.r*C1.r + d*d - C2.r*C2.r) / (2*C1.r*d));
  Point p1 = C1.point(a-da), p2 = C1.point(a+da);

  sol.push_back(p1);
  if(p1 == p2) return 1;
  sol.push_back(p2);
  return 2;
}

vector<Point> A2,vD;
Point A,B,C,D,_A,G;
double AB,BC,CD,DA,EF;

int main(){
    int tcase,tnum=0;
    bool ok;
    scanf("%d",&tcase);
    while(tcase--){
            tnum++;
        scanf("%lf%lf%lf%lf%lf",&AB,&BC,&CD,&DA,&EF);
        B.x=0;B.y=0;C.x=0;C.y=BC;
        A2.clear();
        ok=false;
        int flag=getCircleCircleIntersection(Circle(B,2*EF),Circle(C,DA),A2);
        //printf("flag:%d\n",flag);
        for(int i=0;i<(int)A2.size();i++){
            if(ok) break;
            _A=A2[i];
            //printf("_A %.6lf %.6lf\n",_A.x,_A.y);
            G=_A+(B-C);
            vD.clear();
            getCircleCircleIntersection(Circle(G,AB),Circle(C,CD),vD);
            //printf("vD:%d\n",(int)vD.size());
            for(int j=0;j<(int)vD.size();j++){
                D=vD[j];
                A=B+(D-G);
                ok=true;
                printf("Case #%d:\n",tnum);
                printf("%.6lf %.6lf\n",A.x,A.y);
                printf("%.6lf %.6lf\n",B.x,B.y);
                printf("%.6lf %.6lf\n",C.x,C.y);
                printf("%.6lf %.6lf\n",D.x,D.y);
                Point E = (A + B)/2.0,F = (C + D)/2.0;
                /*printf("AB:%lf BC:%lf CD:%lf DA:%lf EF:%lf\n",
                    Length(A-B),Length(B-C),Length(C-D),
                    Length(D-A),Length(E-F));*/
                break;
            }
        }
    }
    return 0;
}
