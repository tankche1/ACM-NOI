# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const double eps=1e-10;
const int maxn=310;
	
int dcmp(double x){
	if(fabs(x)<eps) return 0;
	return x>0?1:-1;
}

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector &A,double B) { return Vector(A.x*B,A.y*B);}
double Dot(const Vector &A,const Vector &B) {return A.x*B.x+A.y*B.y;}
double Cross(const Vector &A,const Vector &B) {return A.x*B.y-A.y*B.x;}

bool operator < (const Point A,const Point B){
	return dcmp(A.x-B.x)==0?dcmp(A.y-B.y)<0:dcmp(A.x-B.x)<0;
}

bool operator == (const Point A,const Point B){
	return dcmp(A.x-B.x)==0&&dcmp(A.y-B.y)==0;
}

bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
	double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
	return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}

Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}

bool OnSegment(Point P,Point a1,Point a2){
	return dcmp(Cross(a1-P,a2-P))==0&&dcmp(Dot(a1-P,a2-P))<0;
}

Point read(){
	int x,y;
		scanf("%d%d",&x,&y);
	return Point((double)x,(double)y);
}

int n;
Point P[maxn],V[maxn*maxn];
int main(){
	int tcase=0;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		for(int i=0;i<n;i++)
			P[i]=read();
		for(int i=0;i<=n-2;i++) 
			V[i]=P[i];
		int c=n-1;
		for(int i=0;i<n-1;i++)
			for(int j=i+1;j<n-1;j++){
				if(SegmentProperIntersection(P[i],P[i+1],P[j],P[j+1])) 
					V[c++]=GetLineIntersection(P[i],P[i+1]-P[i],P[j],P[j+1]-P[j]);
			}
			sort(V,V+c);
			c=unique(V,V+c)-V;
			int e=n-1;
			for(int i=0;i<c;i++)
				for(int j=0;j<n-1;j++){
					if(OnSegment(V[i],P[j],P[j+1])) e++;
				}
			printf("Case %d: There are %d pieces.\n",++tcase,2+e-c);
	}
	return 0;
}
