// LA4728/UVa1453 Square
// Rujia Liu
#include<cstdio>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

struct Point {
  int x, y;
  Point(int x=0, int y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator - (const Point& A, const Point& B) {
  return Vector(A.x-B.x, A.y-B.y);
}

int Cross(const Vector& A, const Vector& B) {
  return A.x*B.y - A.y*B.x;
}

int Dot(const Vector& A, const Vector& B) {
  return A.x*B.x + A.y*B.y;
}

int Dist2(const Point& A, const Point& B) {
  return (A.x-B.x)*(A.x-B.x) + (A.y-B.y)*(A.y-B.y);
}

bool operator < (const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool operator == (const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

// �㼯͹��
// �����ϣ����͹���ı���������㣬������ <= �ĳ� <
// ע�⣺����㼯�ᱻ�޸�
vector<Point> ConvexHull(vector<Point>& p) {
  // Ԥ����ɾ���ظ���
  sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());

  int n = p.size();
  int m = 0;
  vector<Point> ch(n+1);
  for(int i = 0; i < n; i++) {
    while(m > 1 && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  int k = m;
  for(int i = n-2; i >= 0; i--) {
    while(m > k && Cross(ch[m-1]-ch[m-2], p[i]-ch[m-2]) <= 0) m--;
    ch[m++] = p[i];
  }
  if(n > 1) m--;
  ch.resize(m);
  return ch;
}

// ���ص㼯ֱ����ƽ��
int diameter2(vector<Point>& points) {
  vector<Point> p = ConvexHull(points);
  int n = p.size();
  if(n == 1) return 0;
  if(n == 2) return Dist2(p[0], p[1]);
  p.push_back(p[0]); // ���ȡģ
  int ans = 0;
  for(int u = 0, v = 1; u < n; u++) {
    // һ��ֱ����ס��p[u]-p[u+1]
    for(;;) {
      // ��Area(p[u], p[u+1], p[v+1]) <= Area(p[u], p[u+1], p[v])ʱֹͣ��ת
      // ��Cross(p[u+1]-p[u], p[v+1]-p[u]) - Cross(p[u+1]-p[u], p[v]-p[u]) <= 0
      // ����Cross(A,B) - Cross(A,C) = Cross(A,B-C)
      // �����Cross(p[u+1]-p[u], p[v+1]-p[v]) <= 0
      int diff = Cross(p[u+1]-p[u], p[v+1]-p[v]);
      if(diff <= 0) {
        ans = max(ans, Dist2(p[u], p[v])); // u��v�Ƕ����
        if(diff == 0) ans = max(ans, Dist2(p[u], p[v+1])); // diff == 0ʱu��v+1Ҳ�Ƕ����
        break;
      }
      v = (v + 1) % n;
    }
  }
  return ans;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    int n;
    scanf("%d", &n);
    vector<Point> points;
    for(int i = 0; i < n; i++) {
      int x, y, w;
      scanf("%d%d%d", &x, &y, &w);
      points.push_back(Point(x, y));
      points.push_back(Point(x+w, y));
      points.push_back(Point(x, y+w));
      points.push_back(Point(x+w, y+w));
    }
    printf("%d\n", diameter2(points));
  }
  return 0;
}
