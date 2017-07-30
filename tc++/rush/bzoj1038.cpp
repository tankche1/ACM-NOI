#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int maxn=310;
const double INF=1LL<<60;
const double eps=1e-13;
int n;
double x[maxn],y[maxn];

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
	Point p;
	Vector v;
	double ang;
	Line() {}
	Line(Point p,Vector v):p(p),v(v) {ang=atan2(v.y,v.x);}
	bool operator < (const Line &L) const{
		return ang<L.ang;
	}
};

bool OnLeft(Line L,Point P){
	return Cross(L.v,P-L.p)>0;
}

Point GetIntersection(Line A,Line B){
	Vector u=A.p-B.p;
	double t=Cross(B.v,u)/Cross(A.v,B.v);
	return A.p+A.v*t;
}

int HalfplaneIntersection(Line *L,int n,Point *poly){
	sort(L,L+n);
	
	int first,last;
	Point *p=new Point[n];
	Line *q=new Line[n];
	q[first=last=0]=L[0];
	for(int i=1;i<n;i++){
		while(first<last&&!OnLeft(L[i],p[last-1])) last--;
		while(first<last&&!OnLeft(L[i],p[first])) first++;
		q[++last]=L[i];
		if(fabs(Cross(q[last].v,q[last-1].v))<eps){
			last--;if(OnLeft(q[last],L[i].p)) q[last]=L[i];
		}
		if(first<last) p[last-1]=GetIntersection(q[last],q[last-1]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1])) last--;
		
	if(last-first<=1) return 0;
	p[last]=GetIntersection(q[last],q[first]);
	
	int m=0;
	for(int i=first;i<=last;i++) poly[m++]=p[i];
	return m;
}

Line L[maxn];int cnt=0;

Point poly[maxn];

bool cmp(Point A,Point B){
	return A.x==B.x?A.y<B.y:A.x<B.x;
}

int dcmp(double x){
	if(fabs(x)<eps) return 0;
	return x>0?1:-1;
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf",&x[i]);
	for(int i=1;i<=n;i++)
		scanf("%lf",&y[i]);
	for(int i=2;i<=n;i++){
		L[cnt++]=Line(Point(x[i-1],y[i-1]),Vector(x[i]-x[i-1],y[i]-y[i-1]));
	}
	L[cnt++]=Line(Point(x[1],y[1]),Vector(0,-1));
	L[cnt++]=Line(Point(x[n],y[n]),Vector(0,1));
	L[cnt++]=Line(Point(x[n],INF),Vector(-1,0));
/*	for(int i=0;i<cnt;i++){
		printf("P(%.3lf,%.3lf) v(%.3lf,%.3lf)\n",L[i].p.x,L[i].p.y,L[i].v.x,L[i].v.y);
	}*/
	int m=HalfplaneIntersection(L,cnt,poly);//printf("m:%d\n",m);
	double ans=INF;
	double t;
	for(int i=0;i<m;i++){
		//printf("(%.3lf ,%.3lf)\n",poly[i].x,poly[i].y);
		for(int j=1;j<n;j++){
			int next=j+1;
			if(dcmp(poly[i].x-x[j])*dcmp(poly[i].x-x[next])<=0){
				t=poly[i].y-(y[next]-y[j])/((x[next]-x[j])*1.0)*(poly[i].x-x[j])-y[j];
				ans=min(ans,t);//printf("t:%.3lf x:%.3lf j:%d\n",t,poly[i].x,j);
			}
		}
	}
	for(int i=1;i<=n;i++){
		for(int j=0;j<m;j++){
			//printf("(%.3lf ,%.3lf)\n",poly[j].x,poly[j].y);
			int next=(j+1)%m;
			if(dcmp(x[i]-poly[j].x)*dcmp(x[i]-poly[next].x)<=0){
				t=poly[j].y+(poly[next].y-poly[j].y)/((poly[next].x-poly[j].x)*1.0)*(x[i]-poly[j].x)-y[i];
				ans=min(ans,t);
			}
		}
	}
	printf("%.3lf\n",fabs(ans));
	return 0;
}
