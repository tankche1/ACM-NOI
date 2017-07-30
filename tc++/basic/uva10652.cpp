# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const double PI=acos(-1.0);
double torad(double rad){
	return rad/180.0*PI;
}

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
double Cross(const Vector &A,const Vector &B) {return A.x*B.y-A.y*B.x;}

bool operator < (const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool operator == (const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

//Vector Rotate(Vector v,double ang){return Vector(v.x*cos(ang)-v.y*sin(ang),v.x*sin(ang)+v.y*cos(ang));}
Vector Rotate(const Vector& A, double rad) {
  return Vector(A.x*cos(rad)-A.y*sin(rad), A.x*sin(rad)+A.y*cos(rad));
}

vector<Point> ConvexHull(vector<Point> p){
	sort(p.begin(),p.end());
	p.erase(unique(p.begin(),p.end()),p.end());
	int m=0,n=p.size();
	vector<Point> ch(n+1);
	for(int i=0;i<n;i++){
		while((m>1)&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--){
		while(m>k&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
			ch[m++]=p[i];
	}
	if(n>1) m--;
	ch.resize(m);
	return ch;
}

double PolygonArea(vector<Point> p){
	double area=0;
		int n=p.size();
	for(int i=1;i<n-1;i++){
		area+=Cross(p[i]-p[0],p[i+1]-p[0]);
	}
	return area/2;
}

int n;
vector<Point> P;
int main(){
	int T;
	double x,y,w,h,j;
	scanf("%d",&T);
	while(T--){
		P.clear();
		double area1=0,area2=0;
		scanf("%d",&n);
		for(int i=1;i<=n;i++){
			scanf("%lf%lf%lf%lf%lf",&x,&y,&w,&h,&j);
			Point A(x,y);
			double ang=-torad(j);
			P.push_back(A+Rotate(Vector(-w/2,h/2),ang));
			P.push_back(A+Rotate(Vector(w/2,h/2),ang));
			P.push_back(A+Rotate(Vector(w/2,-h/2),ang));
			P.push_back(A+Rotate(Vector(-w/2,-h/2),ang));
			area1+=w*h;
		}
		area2=PolygonArea(ConvexHull(P));
		printf("%.1lf %%\n",area1*100.0/area2);
	}
	return 0;
}
