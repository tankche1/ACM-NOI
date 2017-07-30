# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const double eps=1e-8;
	
int dcmp(double x){
	if(fabs(x)<eps) return 0;
		return x<0?-1:1;
}

struct Point{
	double x,y;
	Point(double x=0,double y=0) :x(x),y(y) {}
};
typedef Point Vector;

Point operator + (const Point &A,const Point &B) {return Vector(A.x+B.x,A.y+B.y);}
Point operator - (const Point &A,const Point &B) {return Vector(A.x-B.x,A.y-B.y);}
Point operator * (const Point &A,const double &B) {return Vector(A.x*B,A.y*B);}
Point operator / (const Point &A,const double &B) {return Vector(A.x/B,A.y/B);}

double Dot (const Point &A,const Point &B)  {return A.x*B.x+A.y*B.y;}
double Length(const Vector &A) {return sqrt(Dot(A,A));}
double Cross(const Point &A,const Point &B) {return A.x*B.y-A.y*B.x;}

bool operator == (const Point &A,const Point &B){
	return (dcmp(A.x-B.x)==0&&dcmp(A.y-B.y)==0);
}

Point read(){
	Point p;
	scanf("%lf%lf",&p.x,&p.y);
	return p;
}

Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}

bool OnSegment(Point p,Point A,Point B){
	return dcmp(Cross(p-A,B-A))==0&&dcmp(Dot(p-A,p-B))<0;
}

typedef vector<Point> Polygon;

Polygon CutPolygon(Polygon poly,Point A,Point B,double &tot){
	Polygon ans;
	Polygon dist;
	int n=poly.size();
	for(int i=0;i<n;i++){
		if(dcmp(Cross(B-A,poly[i]-A))>=0) ans.push_back(poly[i]);
		if(dcmp(Cross(B-A,poly[(i+1)%n]-poly[i]))!=0){
			Point p=GetLineIntersection(poly[i],poly[(i+1)%n]-poly[i],A,B-A);
				if(OnSegment(p,poly[i],poly[(i+1)%n])) {ans.push_back(p);dist.push_back(p);}
				else if(p==poly[(i+1)%n]) dist.push_back(p);
			}
	}
	//printf("A:%.3lf %.3lf B:%.3lf %.3lf\n",A.x,A.y,B.x,B.y);
	tot+=Length(dist[1]-dist[0]);
//	printf("size:%d\n",dist.size());
	//printf("A:%.3lf %.3lf B:%.3lf %.3lf\n",dist[1].x,dist[1].y,dist[0].x,dist[0].y);
//	for(int i=0;i<ans.size();i++) printf("%.3lf %.3lf\n",ans[i].x,ans[i].y);
	return ans;
}

Polygon square,poly;
Point a[10];
int ord[10];

int n,m,p;
int main(){
	scanf("%d%d%d",&n,&m,&p);
	for(int i=0;i<p;i++){
		a[i]=read();
	}
	reverse(a,a+p);
	square.push_back(Point(0,0));
	square.push_back(Point(n,0));
	square.push_back(Point(n,m));
	square.push_back(Point(0,m));
	for(int i=0;i<p;i++) ord[i]=i;
	double ans=INF;
	while(next_permutation(ord,ord+p)){
		poly=square;
		double tot=0;
		for(int i=0;i<p;i++){
			poly=CutPolygon(poly,a[ord[i]],a[(ord[i]+1)%p],tot);
		}
		ans=min(ans,tot);
	}
	printf("%.3lf\n",ans);
	return 0;
}
