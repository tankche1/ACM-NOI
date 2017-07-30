// UVa11921 Save the Princess
// Rujia Liu
#include<cstdio>
#include<cstring>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

const double INF = 1e9;
const int maxn = 5200; // ÿ����Բ�����4�����ߣ��ܵ������ᳬ��50*49/2*4 + 50*2*2 + 2 =5102

struct Edge {
  int from, to;
  double dist;
};

struct HeapNode {
  double d;
  int u;
  bool operator < (const HeapNode& rhs) const {
    return d > rhs.d;
  }
};

struct Dijkstra {
  int n, m;
  vector<Edge> edges;
  vector<int> G[maxn];
  bool done[maxn];    // �Ƿ������ñ��
  double d[maxn];     // s��������ľ���
  int p[maxn];        // ���·�е���һ����

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
  }

  void AddEdge(int from, int to, double dist) {
    edges.push_back((Edge){from, to, dist});
    m = edges.size();
    G[from].push_back(m-1);
  }

  void dijkstra(int s) {
    priority_queue<HeapNode> Q;
    for(int i = 0; i < n; i++) d[i] = INF;
    d[s] = 0;
    memset(done, 0, sizeof(done));
    Q.push((HeapNode){0, s});
    while(!Q.empty()) {
      HeapNode x = Q.top(); Q.pop();
      int u = x.u;
      if(done[u]) continue;
      done[u] = true;
      for(int i = 0; i < G[u].size(); i++) {
        Edge& e = edges[G[u][i]];
        if(d[e.to] > d[u] + e.dist) {
          d[e.to] = d[u] + e.dist;
          p[e.to] = G[u][i];
          Q.push((HeapNode){d[e.to], e.to});
        }
      }
    }
  }
};

#include<cmath>

const double eps = 1e-8;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

const double PI = acos(-1);
const double TWO_PI = PI * 2;

double NormalizeAngle(double rad, double center = PI) {
  return rad - TWO_PI * floor((rad + PI - center) / TWO_PI);
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (Point A, Point B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (Vector A, double p) { return Vector(A.x*p, A.y*p); }
Vector operator / (Vector A, double p) { return Vector(A.x/p, A.y/p); }

// �����������С�ڡ�������Ǵ�ģ���Ϊ������������a, b, c, a��b�ܽӽ�����a<b��b<a������������b��c�ܽӽ�����a��c���ӽ�
// ����ʹ�����֡�С�ڡ��������ǰ�������ų��������
bool operator < (const Point& a, const Point& b) {
  return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}

bool operator == (Point A, Point B) {
  return dcmp(A.x - B.x) == 0 && dcmp(A.y - B.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Length(Vector A) { return sqrt(Dot(A, A)); }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
Vector Rotate(Vector A, double rad) {
  return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

double angle(Vector v) {
  return atan2(v.y, v.x);
}

Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B-A;
  return A+v*(Dot(v, P-A) / Dot(v, v));
}

double DistanceToSegment(const Point& P, const Point& A, const Point& B) {
  if(A == B) return Length(P-A);
  Vector v1 = B - A, v2 = P - A, v3 = P - B;
  if(dcmp(Dot(v1, v2)) < 0) return Length(v2);
  else if(dcmp(Dot(v1, v3)) > 0) return Length(v3);
  else return fabs(Cross(v1, v2)) / Length(v1);
}

// ����p��ԲC�����ߡ�v[i]�ǵ�i�����ߵ�������������������
int getTangents(Point p, Point c, double r, vector<Vector>& v) {
  Vector u = c - p;
  double dist = Length(u);
  if(dist < r) return 0;
  else if(dcmp(dist - r) == 0) { // p��Բ�ϣ�ֻ��һ������
    v.push_back(Rotate(u, PI/2));
    return 1;
  } else {
    double ang = asin(r / dist);
    v.push_back(Rotate(u, -ang));
    v.push_back(Rotate(u, +ang));
    return 2;
  }
}

// �㵽Բ���е㡣�����е����
// ���Զ�getTangents���������޸�����е㣬��������͵�˸��������Բ���������ϵ�ͶӰ�������е�
int getTangentPoints(Point p, Point c, double r, vector<Point>& out) {
  vector<Vector> v;
  int cnt = getTangents(p, c, r, v);
  for(int i = 0; i < cnt; i++)
    out.push_back(GetLineProjection(c, p, p+v[i]));
  return cnt;
}

// ȡԲ(C, r)����Ϊrad�ĵ�
Point getCirclePoint(Point C, double r, double rad) {
  return Point(C.x + cos(rad)*r, C.y + sin(rad)*r);
}

// ����Բ��Բ�����ߵ�������-1��ʾ����������ߡ�
// a[i]��b[i]�ֱ��ǵ�i��������Բ(c1, r1)��Բ(c2, r2)�ϵ��е�
int getTangentPoints(Point c1, double r1, Point c2, double r2, Point* a, Point* b) {
  int cnt = 0;
  if(r1 < r2) { swap(c1, c2); swap(r1, r2); swap(a, b); }
  int d2 = (c1.x-c2.x)*(c1.x-c2.x) + (c1.y-c2.y)*(c1.y-c2.y);
  int rdiff = r1-r2;
  int rsum = r1+r2;
  if(d2 < rdiff*rdiff) return 0; // �ں�

  double base = atan2(c2.y-c1.y, c2.x-c1.x);
  if(d2 == 0 && r1 == r2) return -1; // ���޶�������
  if(d2 == rdiff*rdiff) { // ���У�1������
    a[cnt] = getCirclePoint(c1, r1, base); b[cnt] = getCirclePoint(c2, r2, base); cnt++;
    return 1;
  }
  // ���⹫����
  double ang = acos((r1-r2) / sqrt(d2));
  a[cnt] = getCirclePoint(c1, r1, base+ang); b[cnt] = getCirclePoint(c2, r2, base+ang); cnt++;
  a[cnt] = getCirclePoint(c1, r1, base-ang); b[cnt] = getCirclePoint(c2, r2, base-ang); cnt++;
  if(d2 == rsum*rsum) { // һ���ڹ�����
    a[cnt] = getCirclePoint(c1, r1, base); b[cnt] = getCirclePoint(c2, r2, PI+base); cnt++;
  }
  else if(d2 > rsum*rsum) { // �����ڹ�����
    double ang = acos((r1+r2) / sqrt(d2));
    a[cnt] = getCirclePoint(c1, r1, base+ang); b[cnt] = getCirclePoint(c2, r2, PI+base+ang); cnt++;
    a[cnt] = getCirclePoint(c1, r1, base-ang); b[cnt] = getCirclePoint(c2, r2, PI+base-ang); cnt++;
  }
  return cnt;
}

////////////// ��Ŀ���
#include<map>
const int maxp = 50 + 10;

int n;                    // �ϰ��ĸ���
Point C[maxp], src, dest; // �ϰ�Բ�ģ������յ�
double r[maxp];           // �ϰ��뾶

vector<Edge> e;           // ��ʱ������
vector<Point> points;     // ������ͼ�ĵ㣨��㡢�յ㡢�е㣩
map<Point, int> idx;      // �㵽ͼ�Ľ���ŵ�ӳ��

Dijkstra dijkstra;

// ���ص�pӳ�䵽�ı��
int ID(Point p) {
  if(idx.count(p)) return idx[p];
  points.push_back(p);
  idx[p] = points.size() - 1;
}

// ����a����b���߶��Ƿ񲻺�����Բ�ཻ��������maxtangent��Բ���С�
// ����ǣ��ӱ�a-b
void checkSegment(Point a, Point b, int maxtangent) {
  for(int i = 0; i < n; i++) {
    int d = dcmp(DistanceToSegment(C[i], a, b) - r[i]);
    if(d < 0) return; // Բi���߶�ab�ཻ
    if(d == 0) { if(maxtangent-- == 0) return; } // Բi���߶�ab���У�ͳ�Ƹ���
  }
  int ia = ID(a), ib = ID(b);
  if(ia >= 0 && ib >= 0 && ia != ib) e.push_back((Edge){ia, ib, Length(a-b)});
}

// ��������յ㵽ÿ��Բ���������ߣ���Ϊ�����յ��ϸ���Բ�⣬����ǡ�����������ߣ�
void checkPointToCircle(Point p) {
  for(int i = 0; i < n; i++) {
    vector<Point> t;
    getTangentPoints(p, C[i], r[i], t);
    checkSegment(p, t[0], 1);
    checkSegment(p, t[1], 1);
  }
}

// �������Բ�������������
// �����е�Բ��Բֻ�����к����룬��Ϊ����ʾģ����÷�����Ȼʹ���ˡ�δɾ�ڰ桱��Բ��Բ�����ߵķ��� ;-)
void checkCircleToCircle() {
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++) {
      Point a[4], b[4];
      int cnt = getTangentPoints(C[i], r[i], C[j], r[j], a, b);
      for(int k = 0; k < cnt; k++)
        checkSegment(a[k], b[k], 2);
    }
}

// ͬһ��Բ������������һ����
void checkPointOnCircle() {
  for(int i = 0; i < n; i++) {
    vector<double> on; // Բi�����е�ļ���
    int m = points.size();
    for(int j = 0; j < m; j++)
      if(dcmp(Length(points[j] - C[i]) - r[i]) == 0) on.push_back(angle(points[j] - C[i]));
    if(on.size() < 2) continue; // ����Ҫ���������������

    sort(on.begin(), on.end());
    on.erase(unique(on.begin(), on.end()), on.end());
    m = on.size();
    for(int j = 0; j < m; j++) {
      Point a = getCirclePoint(C[i], r[i], on[j]);
      Point b = getCirclePoint(C[i], r[i], on[(j+1)%m]);
      double dist = NormalizeAngle(on[(j+1)%m] - on[j]) * r[i];
      int ia = ID(a), ib = ID(b);
      if(ia >= 0 && ib >= 0 && ia != ib) e.push_back((Edge){ia, ib, dist});
    }
  }
}

// p�Ƿ�����������Բ���ϣ������Ļ�������㽫�������ߣ�
bool isForbidden(Point p) {
  int cnt = 0;
  for(int i = 0; i < n; i++)
    if(dcmp(Length(C[i] - p) - r[i]) == 0)
      if(++cnt == 2) return true;
  return false;
}

/*
  �������⣺
  1. �����յ��ϸ���Բ��
  2. �ϰ�Բ�����ཻ�����������У����е㲻��ͨ����
  �ٶ������ϰ�Բ���С���Ȼ���ԡ������е��ߡ����������е㣬���������϶��������ŵ�
  ���ԡ�������2��Բ���ϡ��ĵ�϶���������·���ϣ����ڡ��ϵ㡱 ;-)

  ��ô���Ƿ������ID(p)��ֱ���ж�p�Ƿ�������2��Բ���ϣ�������򷵻�-1����������㲻��Ҫ�����С�
  �ٶ���һ��Բ����������a, b, c������b������2��Բ���ϡ�
  ��������ɾ���˵�b����checkPointOnCircle()�л���ΪԲ��ֻ��������a��c��Ȼ����һ���ߡ���������ʵ���ϴ����˵�b����˷Ƿ���

  ��ȷ����������points�����б�����Щ�㣬ֻ�ǲ�Ҫ����������ڽӵı�
*/
double solve() {
  idx.clear();
  points.clear();
  e.clear();
  int s = ID(src);
  int t = ID(dest);

  checkSegment(src, dest, 0);
  checkPointToCircle(src);
  checkPointToCircle(dest);
  checkCircleToCircle();
  checkPointOnCircle();

  dijkstra.init(points.size());
  for(int i = 0; i < e.size(); i++) {
    int a = e[i].from, b = e[i].to;
    if(isForbidden(points[a]) || isForbidden(points[b])) continue; // ��a���b��������
    double d = e[i].dist;
    dijkstra.AddEdge(a, b, d);
    dijkstra.AddEdge(b, a, d);
  }

  dijkstra.dijkstra(s);
  return dijkstra.d[t];
}

int main() {
  int T;
  scanf("%d", &T);
  for(int kase = 1; kase <= T; kase++) {
    scanf("%lf%lf%lf%lf%d", &src.x, &src.y, &dest.x, &dest.y, &n);
    for(int i = 0; i < n; i++)
      scanf("%lf%lf%lf", &C[i].x, &C[i].y, &r[i]);
    printf("Case %d: %.9lf\n", kase, solve());
  }
  return 0;
}
