//半平面交对于面积无限的答案会求出一个错误的凸包 删除最后一个点后围成的非封闭图形就是这个面积无限的图形
# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
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
double Length(const Vector& A) { return sqrt(Dot(A, A)); }
double Cross(const Vector& A, const Vector& B) { return A.x*B.y - A.y*B.x; }
Vector Normal(const Vector& A) { double L = Length(A); return Vector(-A.y/L, A.x/L); }

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

bool OnLeft(Line L,Point p){
	return Cross(L.v,p-L.P)>0;
}

Point GetLineIntersection(Line A,Line B){
	Vector u=A.P-B.P;
	double T=Cross(B.v,u)/Cross(A.v,B.v);
	return A.P+A.v*T;
}

int HalfplaneIntersection(Line *L,int n,Point *poly){
	sort(L,L+n);
	
	int first,last;
	Point p[n];
	Line q[n];
	q[first=last=0]=L[0];
	for(int i=1;i<n;i++){
		while(first<last&&!OnLeft(L[i],p[last-1])) last--;
		while(first<last&&!OnLeft(L[i],p[first])) first++;
		q[++last]=L[i];
		if(fabs(Cross(q[last].v,q[last-1].v))<eps){
			last--;
			if(OnLeft(q[last],L[i].P)) q[last]=L[i];
		}
		if(first<last) p[last-1]=GetLineIntersection(q[last-1],q[last]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1])) last--;
	if(last-first<=1) return 0;
	p[last]=GetLineIntersection(q[last],q[first]);
	
	int m=0;
	for(int i=first;i<=last;i++) poly[m++]=p[i];
	return m;
}

int n;
Point p[maxn];
Line L[maxn],line[maxn];
int main(){
	int x,y;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		for(int i=0;i<n;i++){
			scanf("%d%d",&x,&y);
			p[i]=Point((double)x,(double)y);
		}
		p[n]=p[0];
		for(int i=0;i<n;i++)
			L[i]=Line(p[i],p[i+1]-p[i]);
		double Left=0,Right=20000;
		while(Right-Left>1e-6){
			double M=(Left+Right)/2.0;
			for(int i=0;i<n;i++) line[i]=Line(L[i].P+Normal(L[i].v)*M,L[i].v);
			if(HalfplaneIntersection(line,n,p)) Left=M;
				else Right=M;
		}
		printf("%.6lf\n",Left);
	}
	return 0;
}
