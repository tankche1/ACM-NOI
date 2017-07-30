// LA2397/UVa1060 Collecting Luggage
// Rujia Liu
#include<cstdio>
#include<cstdlib>
#include<cmath>
#include<cstring>
#include<vector>
#include<queue>
#include<algorithm>
using namespace std;

const double eps = 1e-10;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }

bool operator < (const Point& a, const Point& b) {
  return a.x < b.x || (a.x == b.x && a.y < b.y);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
  c3 = Cross(b2-b1,a1-b1), c4=Cross(b2-b1,a2-b1);
  return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

int isPointInPolygon(const Point& p, Point* poly, int n){
  int wn = 0;
  for(int i = 0; i < n; i++){
    const Point& p1 = poly[i];
    const Point& p2 = poly[(i+1)%n];
    if(p1 == p || p2 == p || OnSegment(p, p1, p2)) return -1; // �ڱ߽���
    int k = dcmp(Cross(p2-p1, p-p1));
    int d1 = dcmp(p1.y - p.y);
    int d2 = dcmp(p2.y - p.y);
    if(k > 0 && d1 <= 0 && d2 > 0) wn++;
    if(k < 0 && d2 <= 0 && d1 > 0) wn--;
  }
  if (wn != 0) return 1; // �ڲ�
  return 0; // �ⲿ
}

const int maxn = 100 + 10;
const int INF = 1000000000;

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

int n;
Point startp, belt[maxn]; // Ϊ�˷��㣬belt[n]����㣬belt[n+1]���յ�
double vl, vp, perimeter, len[maxn];
Dijkstra solver;

// ��a-b�Ƿ񱻵�ס
bool isBlocked(int a, int b) {
  for(int i = 0; i < n+2; i++)
    if(i != a && i != b && OnSegment(belt[i], belt[a], belt[b])) return true; // �м䲻����������
  for(int i = 0; i < n; i++)
    if(SegmentProperIntersection(belt[i], belt[(i+1)%n], belt[a], belt[b])) return true; // ���ܺͶ���εı߹淶�ཻ
  Point midp = (belt[a] + belt[b]) * 0.5;
  if(isPointInPolygon(midp, belt, n) == 1) return true; // �����߶��ڶ������
  return false;
}

// �ж��Ƿ������ʱ��t�õ�����
bool check(double t) {
  solver.init(n+2); // 0~n-1�Ǵ��ʹ����㣬n����㣬n+1���յ�

  // ��������λ�ã���ŵ�belt[n+1]
  double dist = fmod(vl*t, perimeter);
  for(int i = 0; i < n; i++) {
    if(len[i] >= dist) {
      belt[n+1] = belt[i] + (belt[(i+1)%n] - belt[i]) * (dist / len[i]);
      break;
    }
    dist -= len[i];
  }

  // ��ͼ
  for(int i = 0; i < n+2; i++)
    for(int j = i+1; j < n+2; j++) {
      double d = Length(belt[i]-belt[j]);
      if(d > eps && isBlocked(i, j)) continue;
      solver.AddEdge(i, j, d);
      solver.AddEdge(j, i, d);
    }
  solver.dijkstra(n);
  return solver.d[n+1] <= vp*t;
}

int getSecond(double t) {
  return (int)floor(t * 60 + 0.5);
}

int main() {
  int kase = 0;
  while(scanf("%d", &n) == 1 && n > 0) {
    for(int i = 0; i < n; i++) scanf("%lf%lf", &belt[i].x, &belt[i].y);
    scanf("%lf%lf%lf%lf", &startp.x, &startp.y, &vl, &vp);
    perimeter = 0;
    double closest = 1e9;
    for(int i = 0; i < n; i++) {
      closest = min(closest, Length(startp - belt[i])); // �����˵��������ľ���
      len[i] = Length(belt[i] - belt[(i+1)%n]);
      perimeter += len[i]; // �ۼ��ܳ�
    }
    belt[n] = startp;
    double L = 0, R = (closest + perimeter / 2) / vp; // �Ͻ�Ϊ���ߵ�����������߰��ܳ�����Ҫ��ʱ��
    while(getSecond(L) != getSecond(R)) { // ����д��ա�L��R�ܽӽ��������������뵽���롱��һ��һ��
      double M = L + (R-L)/2;
      if(check(M)) R = M; else L = M;
    }
    int t = getSecond(L);
    printf("Case %d: Time = %d:%02d\n", ++kase, t / 60, t % 60);
  }
  return 0;
}
