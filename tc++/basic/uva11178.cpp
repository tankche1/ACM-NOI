# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator + (const Vector &a,const Vector &b) {return Vector(a.x+b.x,a.y+b.y);}
Vector operator - (const Vector &a,const Vector &b) {return Vector(a.x-b.x,a.y-b.y);}
Vector operator * (const Vector &a,const double &b) {return Vector(a.x*b,a.y*b);}
double Dot(const Vector &a,const Vector &b) {return a.x*b.x+a.y*b.y;}
double length(const Vector &a) {return sqrt(Dot(a,a));}
double Angle(const Vector &A,const Vector &B) {return acos(Dot(A,B)/length(A)/length(B));}
double Cross(const Vector &a,const Vector &b){return a.x*b.y-a.y*b.x;}
Vector Rotate(Vector A,double rad){
	return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));
}

Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
	Vector u=P-Q;
	return P+v*(Cross(w,u)/Cross(v,w));
}

Point getD(Point A,Point B,Point C){
	Vector v1=C-B;
	v1=Rotate(v1,Angle(A-B,C-B)/3.0);
	
	Vector v2=B-C;
	v2=Rotate(v2,-Angle(B-C,A-C)/3.0);
	
	return GetLineIntersection(B,v1,C,v2);
}

/*Point getD(Point A, Point B, Point C) {
  Vector v1 = C-B;
  double a1 = Angle(A-B, v1);
  v1 = Rotate(v1, a1/3);

  Vector v2 = B-C;
  double a2 = Angle(A-C, v2);
  v2 = Rotate(v2, -a2/3);

  return GetLineIntersection(B, v1, C, v2);
}*/

Point read(){
	Point A;
	scanf("%lf%lf",&A.x,&A.y);
	return A;
}

int main(){
	int T;
	Point A,B,C,D,E,F;
	scanf("%d",&T);
	while(T--){
		A=read();
		B=read();
		C=read();
		D=getD(A,B,C);
		F=getD(C,A,B);
		E=getD(B,C,A);
		printf("%.6f %.6f %.6f %.6f %.6f %.6f\n",D.x,D.y,E.x,E.y,F.x,F.y);
	}
	return 0;
}
