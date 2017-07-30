// LA3218/UVa1340 Find the Border
// Rujia Liu
// ע�⣺�������ֱ��ʹ�á���������������������������ֻ��Ϊ����ʾPSLG��ʵ��
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
#include<cstring>
#include<cassert>
using namespace std;

const double eps = 1e-8;
double dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) {
  return Vector(A.x+B.x, A.y+B.y);
}

Vector operator - (Point A, Point B) {
  return Vector(A.x-B.x, A.y-B.y);
}

Vector operator * (Vector A, double p) {
  return Vector(A.x*p, A.y*p);
}

// �����������С�ڡ�������Ǵ�ģ���Ϊ������������a, b, c, a��b�ܽӽ�����a<b��b<a������������b��c�ܽӽ�����a��c���ӽ�
// ����ʹ�����֡�С�ڡ��������ǰ�������ų��������
bool operator < (const Point& a, const Point& b) {
  return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

typedef vector<Point> Polygon;

Point GetLineIntersection(const Point& P, const Vector& v, const Point& Q, const Vector& w) { 
  Vector u = P-Q;
  double t = Cross(w, u) / Cross(v, w);
  return P+v*t;
}

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
  c3 = Cross(b2-b1,a1-b1), c4=Cross(b2-b1,a2-b1);
  return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

bool OnSegment(Point p, Point a1, Point a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

// ����ε��������
double PolygonArea(Polygon poly) {
  double area = 0;
  int n = poly.size();
  for(int i = 1; i < n-1; i++)
    area += Cross(poly[i]-poly[0], poly[(i+1)%n]-poly[0]);
  return area/2;
}

struct Edge {
  int from, to; // ��㣬�յ㣬��ߵ�����
  double ang;
};

const int maxn = 10000 + 10; // ������

// ƽ��ֱ��ͼ��PSGL��ʵ��
struct PSLG {
  int n, m, face_cnt;
  double x[maxn], y[maxn];
  vector<Edge> edges;
  vector<int> G[maxn];
  int vis[maxn*2];  // ÿ�����Ƿ��Ѿ����ʹ�
  int left[maxn*2]; // ����ı��
  int prev[maxn*2]; // ��ͬ������һ���ߣ���˳ʱ����ת��������һ���ߣ��ı��

  vector<Polygon> faces;
  double area[maxn]; // ÿ��polygon�����

  void init(int n) {
    this->n = n;
    for(int i = 0; i < n; i++) G[i].clear();
    edges.clear();
    faces.clear();
  }

  // �����߶�from->to�ļ���
  double getAngle(int from, int to) {
    return atan2(y[to]-y[from], x[to]-x[from]);
  }

  void AddEdge(int from, int to) {
    edges.push_back((Edge){from, to, getAngle(from, to)});
    edges.push_back((Edge){to, from, getAngle(to, from)});
    m = edges.size();
    G[from].push_back(m-2);
    G[to].push_back(m-1);
  }

  // �ҳ�faces���������
  void Build() {
    for(int u = 0; u < n; u++) {
      // ����u�����ĸ����߰���������
      int d = G[u].size();
      for(int i = 0; i < d; i++)
        for(int j = i+1; j < d; j++) // ����͵�����������ÿ����������߶β���̫��
          if(edges[G[u][i]].ang > edges[G[u][j]].ang) swap(G[u][i], G[u][j]);
      for(int i = 0; i < d; i++)
        prev[G[u][(i+1)%d]] = G[u][i];
    }

    memset(vis, 0, sizeof(vis));
    face_cnt = 0;
    for(int u = 0; u < n; u++)
      for(int i = 0; i < G[u].size(); i++) {
        int e = G[u][i];
        if(!vis[e]) { // ��ʱ����Ȧ
          face_cnt++;
          Polygon poly;
          for(;;) {
            vis[e] = 1; left[e] = face_cnt;
            int from = edges[e].from;
            poly.push_back(Point(x[from], y[from]));
            e = prev[e^1];
            if(e == G[u][i]) break;
            assert(vis[e] == 0);
          }
          faces.push_back(poly);
        }
      }

    for(int i = 0; i < faces.size(); i++) {
      area[i] = PolygonArea(faces[i]);
    }
  }
};

PSLG g;

const int maxp = 100 + 5;
int n, c;
Point P[maxp];

Point V[maxp*(maxp-1)/2+maxp];

// ��V�������ҵ���p
int ID(Point p) {
  return lower_bound(V, V+c, p) - V;
}

// �ٶ�polyû�����ڵ��غϵ������ֻ��Ҫɾ�����㹲�ߵ����
Polygon simplify(const Polygon& poly) {
  Polygon ans;
  int n = poly.size();
  for(int i = 0; i < n; i++) {
    Point a = poly[i];
    Point b = poly[(i+1)%n];
    Point c = poly[(i+2)%n];
    if(dcmp(Cross(a-b, c-b)) != 0) ans.push_back(b);
  }
  return ans;
}

void build_graph() {
  c = n;
  for(int i = 0; i < n; i++)
    V[i] = P[i];

  vector<double> dist[maxp]; // dist[i][j]�ǵ�i���߶��ϵĵ�j��������㣨P[i]���ľ���
  for(int i = 0; i < n; i++)
    for(int j = i+1; j < n; j++)
      if(SegmentProperIntersection(P[i], P[(i+1)%n], P[j], P[(j+1)%n])) {
        Point p = GetLineIntersection(P[i], P[(i+1)%n]-P[i], P[j], P[(j+1)%n]-P[j]);
        V[c++] = p;
        dist[i].push_back(Length(p - P[i]));
        dist[j].push_back(Length(p - P[j]));
      }

  // Ϊ�˱�֤���ܽӽ��ĵ㡱������ͬһ��������ʹ����sort+unique�ķ���
  // ����ʹ��ǰ���ᵽ�ġ��������Ǵ��󡱵�С��������������ܱ�֤���ܽӽ��ĵ㡱���������������
  // ��һ�������Ĵ���ʽ�ǰ���������ܶ౶������100000������Ȼ���������������㣨������Ϻ��ٻ�ԭ����������ľ�����ʧ����³���Ժ��ٶȡ�
  sort(V, V+c);
  c = unique(V, V+c) - V;

  g.init(c); // c��ƽ��ͼ�ĵ���
  for(int i = 0; i < c; i++) {
    g.x[i] = V[i].x;
    g.y[i] = V[i].y;
  }
  for(int i = 0; i < n; i++) {
    Vector v = P[(i+1)%n] - P[i];
    double len = Length(v);
    dist[i].push_back(0);
    dist[i].push_back(len);
    sort(dist[i].begin(), dist[i].end());
    int sz = dist[i].size();
    for(int j = 1; j < sz; j++) {
      Point a = P[i] + v * (dist[i][j-1] / len);
      Point b = P[i] + v * (dist[i][j] / len);
      if(a == b) continue;
      g.AddEdge(ID(a), ID(b));
    }
  }

  g.Build();

  Polygon poly;
  for(int i = 0; i < g.faces.size(); i++)
    if(g.area[i] < 0) { // ������ͨͼ��Ωһһ�����С���������������
      poly = g.faces[i];
      reverse(poly.begin(), poly.end()); // �����ڲ�������˵�����������εĸ���������˳ʱ���
      poly = simplify(poly); // �����������Ͽ��ܻ������ڹ��ߵ�
      break;
    }

  int m = poly.size();
  printf("%d\n", m);

  // ��ѡ������С�ĵ���Ϊ��������
  int start = 0;
  for(int i = 0; i < m; i++)
    if(poly[i] < poly[start]) start = i;
  for(int i = start; i < m; i++)
    printf("%.4lf %.4lf\n", poly[i].x, poly[i].y);
  for(int i = 0; i < start; i++)
    printf("%.4lf %.4lf\n", poly[i].x, poly[i].y);
}

int main() {
  while(scanf("%d", &n) == 1 && n) {
    for(int i = 0; i < n; i++) {
      int x, y;
      scanf("%d%d", &x, &y);
      P[i] = Point(x, y);
    }
    build_graph();
  }
  return 0;
}
