# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;

struct Point3{
	double x,y,z;
	Point3(double x=0,double y=0,double z=0):x(x),y(y),z(z) {}
};
typedef Point3 Vector3;

Vector3 operator + (const Vector3 &A,const Vector3 &B) {return Vector3(A.x+B.x,A.y+B.y,A.z+B.z);}
Vector3 operator - (const Vector3 &A,const Vector3 &B) {return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);}
Vector3 operator * (const Vector3 &A,const double &B) {return Vector3(A.x*B,A.y*B,A.z*B);}
Vector3 operator / (const Vector3 &A,const double &B) {return Vector3(A.x/B,A.y/B,A.z/B);}

const double eps=1e-8;
int dcmp(double x){
	if(fabs(x)<eps) return 0;
		else return x<0?-1:1;
}

double Dot(const Vector3 &A,const Vector3 &B) {return A.x*B.x+A.y*B.y+A.z*B.z;}
double Length(const Vector3 &A) {return sqrt(Dot(A,A));}
double Angle(const Vector3 &A,const Vector3 &B) {return  acos(Dot(A,B)/Length(A)/Length(B));}
Vector3 Cross(const Vector3 &A,const Vector3 &B) {return Vector3(A.y*B.z-B.y*A.z,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x);}
double Area2(const Point3 &A,const Point3 &B,const Point3 &C) {return Length(Cross(B-A,C-A));}

Point3 read_point3() {
  Point3 p;
  scanf("%lf%lf%lf", &p.x, &p.y, &p.z);
  return p;
}

bool PointInTri(Point3 p,Point3 p1,Point3 p2,Point3 p3){
	return dcmp(Area2(p,p1,p2)+Area2(p,p2,p3)+Area2(p,p3,p1)-Area2(p1,p2,p3))==0;
}

bool TriSegIntersection(Point3 p0,Point3 p1,Point3 p2,Point3 A,Point3 B,Point3 &P){
	Vector3 n=Cross(p0-p1,p2-p1);
	 // Vector3 n = Cross(p1-p0, p2-p0);
	if(dcmp(Dot(n,B-A))==0) return false;
	double t=Dot(p0-A,n)/Dot(n,B-A);
	if(dcmp(t)<0||dcmp(t-1)>0) return false;
	P=A+(B-A)*t;
	return PointInTri(P,p0,p1,p2);
}

bool TriTriIntersection(Point3 *T1,Point3 *T2){
	Point3 P;
	for(int i=0;i<3;i++){
		if(TriSegIntersection(T1[0],T1[1],T1[2],T2[i],T2[(i+1)%3],P)) return true;
		if(TriSegIntersection(T2[0],T2[1],T2[2],T1[i],T1[(i+1)%3],P)) return true;
	}
	return false;
}

int main(){
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
