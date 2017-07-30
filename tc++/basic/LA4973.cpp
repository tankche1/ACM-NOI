# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;

struct Point3{
	int x,y,z;
	Point3() {}
	Point3(int x,int y,int z):x(x),y(y),z(z) {}
};

typedef Point3 Vector3;

Vector3 operator + (const Vector3 &A,const Vector3 &B){return Vector3(A.x+B.x,A.y+B.y,A.z+B.z);}
Vector3 operator - (const Vector3 &A,const Vector3 &B){return Vector3(A.x-B.x,A.y-B.y,A.z-B.z);}
Vector3 operator * (const Vector3 &A,const int &B){return Vector3(A.x*B,A.y*B,A.z*B);}
Vector3 operator / (const Vector3 &A,const int &B){return Vector3(A.x/B,A.y/B,A.z/B);}

bool operator == (const Vector3 &A,const Vector3 &B){
	return A.x==B.x&&A.y==B.y&&A.z==B.z;
}

Point3 read(){
	Point3 A;
	scanf("%d%d%d",&A.x,&A.y,&A.z);
	return A;
}

int Dot(const Vector3 &A,const Vector3 &B) {return A.x*B.x+A.y*B.y+A.z*B.z;}
int Length2(const Vector3& A) { return Dot(A, A);}
Vector3 Cross(const Vector3 &A,const Vector3 &B) {return Vector3(A.y*B.z-A.z*B.y,A.z*B.x-A.x*B.z,A.x*B.y-A.y*B.x);}

typedef long long LL;

LL gcd(LL a,LL b) {return b?gcd(b,a%b):a;}
LL lcm(LL a,LL b) {return a/gcd(a,b)*b;}

struct Rat{
	LL a,b;
	Rat(LL a=0):a(a),b(1) {}
	Rat(LL x,LL y):a(x),b(y) {
		if(b<0) a=-a,b=-b;
		LL d=gcd(a,b);
		if(d<0) d=-d;
		a/=d;b/=d;
	}
};

/*Rat operator + (const Rat &A,const Rat &B){
	return Rat(A.a*B.b+B.a*A.b,A.b*B.b);
}*/

Rat operator + (const Rat& A, const Rat& B) {
  LL x = lcm(A.b, B.b);
  return Rat(A.a*(x/A.b)+B.a*(x/B.b), x);
}

Rat operator - (const Rat &A,const Rat &B){
	return A+Rat(-B.a,B.b);
}

Rat operator * (const Rat &A,const Rat &B){
	return Rat(A.a*B.a,A.b*B.b);
}

void updatemin(Rat &A,Rat B){
	if(A.a*B.b>A.b*B.a) A.a=B.a,A.b=B.b;
}

Rat Rat_Distance2ToSegment(Point3 P,Point3 A,Point3 B){
	if(A==B) return Length2(P-A);
	if(Dot(B-A,P-A)<0) return Length2(P-A);
	if(Dot(A-B,P-B)<0) return Length2(P-B);
	return Rat(Length2(Cross(B-A,P-A)),Length2(B-A));
}

bool Rat_LineDistance3D(Point3 p1,Vector3 v1,Point3 p2,Vector3 v2,Rat &s){
	if(Length2(Cross(v1,v2))==0) return false;
	int A1=Dot(v2,v1),B1=-Dot(v1,v1),C1=Dot(p2-p1,v1);
	int A2=Dot(v2,v2),B2=-Dot(v1,v2),C2=Dot(p2-p1,v2);
	
	s=Rat(C2*A1-C1*A2,B1*A2-B2*A1);
	return true;
}

void Rat_GetPointOnLine(const Point3& A, const Point3& B, const Rat& t, Rat& x, Rat& y, Rat& z) {
  x = Rat(A.x) + Rat(B.x-A.x) * t;
  y = Rat(A.y) + Rat(B.y-A.y) * t;
  z = Rat(A.z) + Rat(B.z-A.z) * t;
}

Rat Rat_Distance2(const Rat& x1, const Rat& y1, const Rat& z1, const Rat& x2, const Rat& y2, const Rat& z2) {
  return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2)+(z1-z2)*(z1-z2);
}

int main(){
	int T;
	scanf("%d",&T);
	while(T--){
		Point3 a1,a2,b1,b2;
		a1=read();
		a2=read();
		b1=read();
		b2=read();
		Rat ans=Rat(1000000000,1);
		Rat s,v;
		bool ok=false;
		if(Rat_LineDistance3D(a1,a2-a1,b1,b2-b1,s)){
			if(s.a>0&&s.a<s.b){
				Rat_LineDistance3D(b1,b2-b1,a1,a2-a1,v);
				if(v.a>0&&v.a<v.b){
				ok=true;
				Rat x1,y1,z1,x2,y2,z2;
				Rat_GetPointOnLine(a1,a2,s,x1,y1,z1);
				Rat_GetPointOnLine(b1,b2,v,x2,y2,z2);
				ans=Rat_Distance2(x1,y1,z1,x2,y2,z2);
				}
			}
		}
	if(!ok) { // 平行直线/重合直线
      updatemin(ans, Rat_Distance2ToSegment(a1, b1, b2));
      updatemin(ans, Rat_Distance2ToSegment(a2, b1, b2));
      updatemin(ans, Rat_Distance2ToSegment(b1, a1, a2));
      updatemin(ans, Rat_Distance2ToSegment(b2,a1, a2));
    }
    printf("%lld %lld\n", ans.a, ans.b);
	}
	return 0;
}
