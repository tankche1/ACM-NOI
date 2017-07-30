// LA3532/UVa1367 Nuclear Plants
// Rujia Liu
#include<cstdio>
#include<cmath>
#include<cstring>
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

const double eps = 5 * 1e-13;
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

double angle(Vector v) {
  return atan2(v.y, v.x);
}

bool OnSegment(const Point& p, const Point& a1, const Point& a2) {
  return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

// ���������Բ1�ļ��Ǳ�����rad��
void getCircleCircleIntersection(Point c1, double r1, Point c2, double r2, vector<double>& rad) {
  double d = Length(c1 - c2);
  if(dcmp(d) == 0) return; // �������ں������غϣ������ཻ
  if(dcmp(r1 + r2 - d) < 0) return;
  if(dcmp(fabs(r1-r2) - d) > 0) return;

  double a = angle(c2 - c1);
  double da = acos((r1*r1 + d*d - r2*r2) / (2*r1*d));
  rad.push_back(NormalizeAngle(a-da));
  rad.push_back(NormalizeAngle(a+da));
}

Point GetLineProjection(Point P, Point A, Point B) {
  Vector v = B-A;
  return A+v*(Dot(v, P-A) / Dot(v, v));
}

// ֱ��AB��Բ��ΪC���뾶Ϊr��Բ�Ľ��㡣�����Բ�ļ��Ǳ�����rad��
void getLineCircleIntersection(Point A, Point B, Point C, double r, vector<double>& rad){
  Point p = GetLineProjection(C, A, B);
  double a = angle(p - C);
  double d = Length(p - C);
  if(dcmp(d - r) > 0) return;
  if(dcmp(d) == 0) { // ��Բ��
    rad.push_back(NormalizeAngle(angle(A - B)));
    rad.push_back(NormalizeAngle(angle(B - A)));
  }
  double da = acos(d / r);
}

/////////// ��Ŀ���
const int maxn = 200 + 5;
int n, N, M; // n��Բ��������N��M�ǳ��س���
Point P[maxn];
double R[maxn];

// ȡԲno����Ϊrad�ĵ�
Point getPoint(int no, double rad) {
  return Point(P[no].x + cos(rad)*R[no], P[no].y + sin(rad)*R[no]);
}

// ��no��Բ����Ϊrad�ĵ��Ƿ�ɼ�����ͬ��Բֻ�б����С�Ŀɼ�����Ȼ���ڱ�����˵����Ҫ��
bool visible(int no, double rad) {
  Point p = getPoint(no, rad);
  if(p.x < 0 || p.y < 0 || p.x > N || p.y > M) return false;
  for(int i = 0; i < n; i++) {
    if(P[no] == P[i] && dcmp(R[no] - R[i]) == 0 && i < no) return false;
    if(dcmp(Length(p - P[i]) - R[i]) < 0) return false;
  }
  return true;
}

// ���ر߽��ϵĵ�p�Ƿ�ɼ�
bool visible(Point p) {
  for(int i = 0; i < n; i++) {
    if(dcmp(Length(p - P[i]) - R[i]) <= 0) return false;
  }
  return true;
}

// ��Բ�Ĳ���(0,0)-(N,M)�ڵ����
// ʹ��һ������ͼ�ε�����㷨�������У�������ͼ�Ρ�ָ���ǲ����ֲ˵��������ı߽���Բ����ֱ�߶ι��ɡ�
// �㷨����������ͼ�α߽��ϵ�ÿһ�Σ����������ߣ�a~>b���ۼ�Cross(a, b)������ֱ�߶�a->b�ұ߲��ֵ��������߲����㸺��
// �߽���㣺
// 1. ÿ��Բ������Բ�ͳ��ر߽�ֳ���������Բ�����е㲻������Բ�������ڳ����ڵ�Բ��������ͼ�α߽���
// 2. ���ص������߽类Բ�ֳ����������߶Ρ��е���ĳ��Բ�ڲ����߶�������ͼ�α߽���
double getArea() {
  Point b[4];
  b[0] = Point(0, 0);
  b[1] = Point(N, 0);
  b[2] = Point(N, M);
  b[3] = Point(0, M);
  double area = 0;

  // Բ������
  for(int i = 0; i < n; i++) {
    vector<double> rad;
    rad.push_back(0);
    rad.push_back(PI*2);

    // Բ�ͱ߽�Ľ���
    for(int j = 0; j < 4; j++)
      getLineCircleIntersection(b[j], b[(j+1)%4], P[i], R[i], rad);

    // Բ��Բ�Ľ���
    for(int j = 0; j < n; j++)
      getCircleCircleIntersection(P[i], R[i], P[j], R[j], rad);
    
    sort(rad.begin(), rad.end());
    for(int j = 0; j < rad.size()-1; j++) if(rad[j+1] - rad[j] > eps) {
      double mid = (rad[j] + rad[j+1]) / 2.0; // Բ���е������ԲiԲ�ĵļ���
      if(visible(i, mid)) { // ���е�ɼ�����˻���ͼ�α߽���
        area += Cross(getPoint(i, rad[j]), getPoint(i, rad[j+1])) / 2.0;
        double a = rad[j+1] - rad[j];
        area += R[i] * R[i] * (a - sin(a)) / 2.0;
      }
    }
  }

  // ֱ�߶β���
  for(int i = 0; i < 4; i++) {
    Vector v = b[(i+1)%4] - b[i];
    double len = Length(v);

    vector<double> dist;
    dist.push_back(0);
    dist.push_back(len);
    for(int j = 0; j < n; j++) {
      vector<double> rad;
      getLineCircleIntersection(b[i], b[(i+1)%4], P[j], R[j], rad);
      for(int k = 0; k < rad.size(); k++) {
        Point p = getPoint(j, rad[k]);
        dist.push_back(Length(p - b[i]));
      }
    }

    sort(dist.begin(), dist.end()); // ���밴�յ����ľ�����������ǰ��յ���ֵ������򣬷�������������ܻᷴ
    vector<Point> points;
    for(int j = 0; j < dist.size(); j++)
      points.push_back(b[i] + v * (dist[j] / len));

    for(int j = 0; j < dist.size()-1; j++) {
      Point midp = (points[j] + points[j+1]) / 2.0;
      if(!visible(midp)) area += Cross(points[j], points[j+1]) / 2.0; // �߶��е㲻�ɼ�������߶���ͼ�α߽���
    }
  }

  return N*M - area;
}

int main() {
  int ks, kl;
  while(scanf("%d%d%d%d", &N, &M, &ks, &kl) == 4 && N && M) {
    for(int i = 0; i < ks; i++) { scanf("%lf%lf", &P[i].x, &P[i].y); R[i] = 0.58; }
    sort(P, P+ks);
    ks = unique(P, P+ks) - P;
    for(int i = 0; i < kl; i++) { scanf("%lf%lf", &P[ks+i].x, &P[ks+i].y); R[ks+i] = 1.31; }
    sort(P+ks, P+ks+kl);
    n = unique(P+ks, P+ks+kl) - P;
    printf("%.2lf\n", getArea());
  }
  return 0;
}
