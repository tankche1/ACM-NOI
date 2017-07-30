// UVa11275 3D Triangles����������жϵ�����������
// Rujia Liu
#include<cstdio>
#include<cmath>
using namespace std;

struct Point3 {
  double x, y, z;
  Point3(double x=0, double y=0, double z=0):x(x),y(y),z(z) { }
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3& A, const Vector3& B) { return Vector3(A.x+B.x, A.y+B.y, A.z+B.z); }
Vector3 operator - (const Point3& A, const Point3& B) { return Vector3(A.x-B.x, A.y-B.y, A.z-B.z); }
Vector3 operator * (const Vector3& A, double p) { return Vector3(A.x*p, A.y*p, A.z*p); }
Vector3 operator / (const Vector3& A, double p) { return Vector3(A.x/p, A.y/p, A.z/p); }

const double eps = 1e-8;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

double Dot(const Vector3& A, const Vector3& B) { return A.x*B.x + A.y*B.y + A.z*B.z; }
double Length(const Vector3& A) { return sqrt(Dot(A, A)); }
double Angle(const Vector3& A, const Vector3& B) { return acos(Dot(A, B) / Length(A) / Length(B)); }
Vector3 Cross(const Vector3& A, const Vector3& B) { return Vector3(A.y*B.z - A.z*B.y, A.z*B.x - A.x*B.z, A.x*B.y - A.y*B.x); }
double Area2(const Point3& A, const Point3& B, const Point3& C) { return Length(Cross(B-A, C-A)); }

Point3 read_point3() {
  Point3 p;
  scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
  return p;
}

// ����������P0, P1, P2��
bool PointInTri(const Point3& P, const Point3& P0, const Point3& P1, const Point3& P2) {
  double area1 = Area2(P, P0, P1);
  double area2 = Area2(P, P1, P2);
  double area3 = Area2(P, P2, P0);
  return dcmp(area1 + area2 + area3 - Area2(P0, P1, P2)) == 0;
}

// ������P0P1P2�Ƿ���߶�AB�ཻ
bool TriSegIntersection(const Point3& P0, const Point3& P1, const Point3& P2, const Point3& A, const Point3& B, Point3& P) {
  Vector3 n = Cross(P1-P0, P2-P0);
  if(dcmp(Dot(n, B-A)) == 0) return false; // �߶�A-B��ƽ��P0P1P2ƽ�л���
  else { // ƽ��A��ֱ��P1-P2��Ωһ����
    double t = Dot(n, P0-A) / Dot(n, B-A);
    if(dcmp(t) < 0 || dcmp(t-1) > 0) return false; // �����߶�AB��
    P = A + (B-A)*t; // ����
    return PointInTri(P, P0, P1, P2);
  }
}

bool TriTriIntersection(Point3* T1, Point3* T2) {
  Point3 P;
  for(int i = 0; i < 3; i++) {
    if(TriSegIntersection(T1[0], T1[1], T1[2], T2[i], T2[(i+1)%3], P)) return true;  
    if(TriSegIntersection(T2[0], T2[1], T2[2], T1[i], T1[(i+1)%3], P)) return true;  
  }
  return false;
}

int main() {
  int T;
  scanf("%d", &T);
  while(T--) {
    Point3 T1[3], T2[3];
    for(int i = 0; i < 3; i++) T1[i] = read_point3();
    for(int i = 0; i < 3; i++) T2[i] = read_point3();
    printf("%d\n", TriTriIntersection(T1, T2) ? 1 : 0);
  }
  return 0;
}
