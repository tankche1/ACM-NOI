#include<stdio.h>
#include<string.h>
# include<math.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
const double INF=1e+9;
int n;
const double eps=1e-16;

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;

Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }

double Dot(Vector A,Vector B) {return A.x*B.x+A.y*B.y;}
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double Length(Vector A) {return sqrt(Dot(A,A));}
Vector Normal(Vector A) {double L=Length(A);return Vector(A.x/L,A.y/L);}

struct Line{
	Point P;
	Vector v;
	double ang;
	Line() {}
	Line(Point P,Vector v):P(P),v(v) {ang=atan2(v.y,v.x);}
	bool operator < (const Line &L) const{
		return ang<L.ang;
	}
};

bool OnLeft(Line L,Point P){
	return Cross(L.v,P-L.P)>0;
}

Point GetIntersection(Line a,Line b){
	Vector u=a.P-b.P;
	double t=Cross(b.v,u)/Cross(a.v,b.v);
	return a.P+a.v*t;
}

Line L[maxn<<1];
Line Li[maxn<<1];
Point p[maxn<<1];
Line q[maxn<<1];

int HalfplaneIntersection(int n){
	for(int i=0;i<n;i++) Li[i]=L[i];
	sort(Li,Li+n);
	int first,last;
	q[first=last=0]=Li[0];
	for(int i=1;i<n;i++){
		while(first<last&&!OnLeft(Li[i],p[last-1])) last--;
		while(first<last&&!OnLeft(Li[i],p[first])) first++;
		q[++last]=Li[i];
		if(fabs(q[last].ang-q[last-1].ang)<eps){
			last--;
			if(OnLeft(q[last],Li[i].P)) q[last]=Li[i];
		}
		if(first<last) p[last-1]=GetIntersection(q[last-1],q[last]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1])) last--;
	if(last-first<=1) return 0;
	else return 1;
}

double x,a,b;
int main(){
	scanf("%d",&n);
	L[0]=Line(Point(0,0),Vector(0,1));L[1]=Line(Point(0,INF),Vector(-1,0));
	L[2]=Line(Point(-INF,INF),Vector(0,-1));L[3]=Line(Point(-INF,0),Vector(1,0));
	for(int i=1;i<=n;i++){
		scanf("%lf %lf %lf",&x,&a,&b); 
		L[4+2*i-2]=Line(Point(0,(double)a/(x*1.0)),Vector(1,-x));
		//L[4+2*i-2]=Line(Point((double)y[i][0]/(x[i]*x[i]*1.0),0),Point(0,(double)y[i][0]/(x[i]*1.0))-Point((double)y[i][0]/(x[i]*x[i]*1.0),0));
		//L[4+2*i-1]=Line(Point(0,(double)y[i][1]/(x[i]*1.0)),Point((double)y[i][1]/(x[i]*x[i]*1.0),0)-Point(0,(double)y[i][1]/(x[i]*1.0)));
		L[4+2*i-1]=Line(Point(0,(double)b/(x*1.0)),Vector(-1,x));
	}
	//for(int i=0;i<2*n+4;i++)
	//	printf("P(%.2lf %.2lf) v(%.2lf,%.2lf)\n",L[i].P.x,L[i].P.y,L[i].v.x,L[i].v.y);
	int l=1,r=n;
	while(l<=r){
		int M=(l+r)>>1;
		if(HalfplaneIntersection(4+2*M))
			l=M+1;
		else r=M-1;
	}
	printf("%d\n",l-1);
	return 0;
}
