# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=110;
double eps=1e-8;

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Vector& A, const Vector& B) { return Vector(A.x+B.x, A.y+B.y); }
Vector operator - (const Point& A, const Point& B) { return Vector(A.x-B.x, A.y-B.y); }
Vector operator * (const Vector& A, double p) { return Vector(A.x*p, A.y*p); }
double Dot(const Vector& A, const Vector& B) { return A.x*B.x + A.y*B.y; }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
Vector Normal(const Vector& A) { double L = Length(A); return Vector(-A.y/L, A.x/L); }

struct Line{
	Point P;
	Vector v;
	double ang;
	Line() {}
	Line(Point P,Vector v) :P(P),v(v) {ang=atan2(v.y,v.x);}
	bool operator < (const Line &rhs)const{
		return ang<rhs.ang;
	}
};

bool OnLeft(Line L,Point p){
	return Cross(L.v,p-L.P)>eps;
}

Point GetLineIntersection(Line A,Line B){
	Vector u=A.P-B.P;
	double t=Cross(B.v,u)/Cross(A.v,B.v);
	return A.P+A.v*t;
}

int HalfplaneIntersection(Line *L,int n,Point *poly){
	sort(L,L+n);
	Point p[n];
	Line q[n];
	int first,last;
	q[first=last=0]=L[0];
	for(int i=1;i<n;i++){
		while(first<last&&!OnLeft(L[i],p[last-1])) last--;
		while(first<last&&!OnLeft(L[i],p[first])) first++;
		q[++last]=L[i];
		if(fabs(Cross(q[last].v,q[last-1].v))<eps){
			last--;
			if(OnLeft(q[last],L[i].P)) q[last]=L[i];
		}
		if(last>first)
			p[last-1]=GetLineIntersection(q[last-1],q[last]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1])) last--;
	if(last-first<=1) return 0;
	p[last]=GetLineIntersection(q[last],q[first]);
	
	int m=0;
	for(int i=first;i<=last;i++)
		poly[m++]=p[i];
	return m;
}

double k=10000;
double v[maxn],u[maxn],w[maxn];
int n;
Line L[maxn];
Point ch[maxn];

int main(){
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++)
			scanf("%lf%lf%lf",&v[i],&u[i],&w[i]);
		for(int i=0;i<n;i++){
			bool ok=true;
			int m=0;
			for(int j=0;j<n;j++){
				if(i==j) continue;
				if(v[j]>=v[i]&&u[j]>=u[i]&&w[j]>=w[i]) {ok=false;break;}
				if(v[i]>=v[j]&&u[i]>=u[j]&&w[i]>=w[j]) continue;
				double A=k/v[j]-k/w[j]-k/v[i]+k/w[i];
				double B=k/u[j]-k/w[j]-k/u[i]+k/w[i];
				double C=k/w[j]-k/w[i];
				Point p;
				if(fabs(A)>fabs(B)) p=Point(-C/A,0);
					else p=Point(0,-C/B);
				L[m++]=Line(p,Vector(B,-A));
			}
			if(ok){
				L[m++]=Line(Point(0,0),Vector(0,-1));
				L[m++]=Line(Point(0,0),Vector(1,0));
				L[m++]=Line(Point(0,1),Vector(-1,1));
				int mm=HalfplaneIntersection(L,m,ch);
				if(!mm) ok=0;
			}
			if(ok) printf("Yes\n"); else printf("No\n");
		}
	}
	return 0;
}
