// LA2218 Triathlon
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<vector>
#include<algorithm>
using namespace std;

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
Vector Normal(const Vector& A) { double L = Length(A); return Vector(-A.y/L, A.x/L); }

double PolygonArea(vector<Point> p) {
  int n = p.size();
  double area = 0;
  for(int i = 1; i < n-1; i++)
    area += Cross(p[i]-p[0], p[i+1]-p[0]);
  return area/2;
}

// ����ֱ�ߡ�������߾��Ƕ�Ӧ�İ�ƽ��
struct Line {
  Point P;    // ֱ��������һ��
  Vector v;   // ��������
  double ang; // ���ǣ�����x��������ת������v����Ҫ�Ľǣ����ȣ�
  Line() {}
  Line(Point P, Vector v):P(P),v(v){ ang = atan2(v.y, v.x); }
  bool operator < (const Line& L) const {
    return ang < L.ang;
  }
};

// ��p������ֱ��L����ߣ����ϲ��㣩
bool OnLeft(const Line& L, const Point& p) {
  return Cross(L.v, p-L.P) > 0;
}

// ��ֱ�߽��㣬�ٶ�����Ωһ����
Point GetLineIntersection(const Line& a, const Line& b) {
  Vector u = a.P-b.P;
  double t = Cross(b.v, u) / Cross(a.v, b.v);
  return a.P+a.v*t;
}

const double INF = 1e8;
const double eps = 1e-6;

// ��ƽ�潻������
vector<Point> HalfplaneIntersection(vector<Line> L) {
  int n = L.size();
  sort(L.begin(), L.end()); // ����������
  
  int first, last;         // ˫�˶��еĵ�һ��Ԫ�غ����һ��Ԫ�ص��±�
  vector<Point> p(n);      // p[i]Ϊq[i]��q[i+1]�Ľ���
  vector<Line> q(n);       // ˫�˶���
  vector<Point> ans;       // ���

  q[first=last=0] = L[0];  // ˫�˶��г�ʼ��Ϊֻ��һ����ƽ��L[0]
  for(int i = 1; i < n; i++) {
    while(first < last && !OnLeft(L[i], p[last-1])) last--;
    while(first < last && !OnLeft(L[i], p[first])) first++;
    q[++last] = L[i];
    if(fabs(Cross(q[last].v, q[last-1].v)) < eps) { // ������ƽ����ͬ��ȡ�ڲ��һ��
      last--;
      if(OnLeft(q[last], L[i].P)) q[last] = L[i];
    }
    if(first < last) p[last-1] = GetLineIntersection(q[last-1], q[last]);
  }
  while(first < last && !OnLeft(q[first], p[last-1])) last--; // ɾ������ƽ��
  if(last - first <= 1) return ans; // �ռ�
  p[last] = GetLineIntersection(q[last], q[first]); // ������β������ƽ��Ľ���

  // ��deque���Ƶ������
  for(int i = first; i <= last; i++) ans.push_back(p[i]);
  return ans;
}

const int maxn = 100 + 10;
int V[maxn], U[maxn], W[maxn];
int main() {
  int n;
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) scanf("%d%d%d", &V[i], &U[i], &W[i]);
    for(int i = 0; i < n; i++) {
      int ok = 1;
      double k = 10000;
      vector<Line> L;
      for(int j = 0; j < n; j++) if(i != j) {
        if(V[i] <= V[j] && U[i] <= U[j] && W[i] <= W[j]) { ok = 0; break; }
        if(V[i] >= V[j] && U[i] >= U[j] && W[i] >= W[j]) continue;
        // x/V[i]+y/U[i]+(1-x-y)/W[i] < x/V[j]+y/U[j]+(1-x-y)/W[j]
        // ax+by+c>0
        double a = (k/V[j]-k/W[j]) - (k/V[i]-k/W[i]);
        double b = (k/U[j]-k/W[j]) - (k/U[i]-k/W[i]);
        double c = k/W[j] - k/W[i];
        Point P;
        Vector v(b, -a);
        if(fabs(a) > fabs(b)) P = Point(-c/a, 0);
        else P = Point(0, -c/b);
        L.push_back(Line(P, v));
      }
      if(ok) {
        // x>0, y>0, x+y<1 ==> -x-y+1>0
        L.push_back(Line(Point(0, 0), Vector(0, -1)));
        L.push_back(Line(Point(0, 0), Vector(1, 0)));
        L.push_back(Line(Point(0, 1), Vector(-1, 1)));
        vector<Point> poly = HalfplaneIntersection(L);
        if(poly.empty()) ok = 0;
      }
      if(ok) printf("Yes\n"); else printf("No\n");
    }
  }
  return 0;
}
