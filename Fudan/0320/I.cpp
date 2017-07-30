# include<stdio.h>
# include<string.h>
# include<vector>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=5010;
int n;
int fa[maxn];

const double PI = acos(-1);

const double eps = 1e-12;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
}p[maxn];

struct Circle {
  Point c;
  double r;
  Circle() {}
  Circle(Point c, double r):c(c),r(r) {}
  Point point(double a) {
    return Point(c.x + cos(a)*r, c.y + sin(a)*r);
  }
}C1,C2;


typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Angle(Vector A, Vector B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }

Point Get(Point c,double a) {
    return Point(c.x + cos(a)*2.0, c.y + sin(a)*2.0);
}

double angle(Vector v) {
  return atan2(v.y, v.x);
}



int getCircleCircleIntersection(Circle C1, Circle C2, vector<Point>& sol) {
  double d = Length(C1.c - C2.c);
  if( dcmp(C1.r - C2.r)>0)
        swap(C1,C2);
  if(dcmp(d) == 0) {
    if(dcmp(C1.r - C2.r) == 0) return -1; // 重合，无穷多交点
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

int find(int x){
    if(fa[x]==x) return x;
    return fa[x]=find(fa[x]);
}
int size[maxn];
int vis[maxn];

int block=0,tmp,ans=2;

void update(){
    int tx;
    ++block;tmp=1;
    for(int k=1;k<=n;k++){
        if(Length(p[k]-p[n+1])<=2+eps){
            tx=find(k);
            if(vis[tx]!=block){
                vis[tx]=block;tmp+=size[tx];
            }
        }
    }
    ans=max(ans,tmp);
}

vector<Point> sol;
int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%lf%lf",&p[i].x,&p[i].y);fa[i]=i;size[i]=1;
    }

    int tx,ty;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(Length(p[i]-p[j])<=2){
                tx=find(i);ty=find(j);
                if(tx!=ty) fa[tx]=ty,size[ty]+=size[tx];
            }
        }
    }

    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            if(Length(p[i]-p[j])<=4+eps){
                C1.c=p[i];C1.r=2.0;C2.c=p[j];C2.r=2.0;sol.clear();
                if(getCircleCircleIntersection(C1,C2,sol)<=0) continue;
                for(int i=0;i<(int)sol.size();i++){
                    p[n+1]=sol[i];
                    update();
                }
            }
        }
    }
    printf("%d\n",ans);
    return 0;
}
