# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const double eps = 1e-8;
double dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

typedef vector<Point> Polygon;

Vector operator + (Vector A, Vector B) {
  return Vector(A.x+B.x, A.y+B.y);
}

Vector operator - (Point A, Point B) {
  return Vector(A.x-B.x, A.y-B.y);
}

Vector operator * (Vector A, double p) {
  return Vector(A.x*p, A.y*p);
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Length2(Vector A) { return Dot(A, A); }

Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}

bool OnSegment(Point p,Point a1,Point a2){
	return dcmp(Cross(p-a1,a2-a1))==0&&dcmp(Dot(p-a1,p-a2))<0;
	//return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

typedef vector<Point> Polygon;

Polygon CutPolygon(Polygon poly,Point A,Point B){
	Polygon ans;
	int n=poly.size();
	for(int i=0;i<n;i++){
		if(dcmp(Cross(B-A,poly[i]-A))>=0) ans.push_back(poly[i]);
		if(dcmp(Cross(B-A,poly[(i+1)%n]-poly[i]))!=0){
			Point p=GetLineIntersection(A,B-A,poly[i],poly[(i+1)%n]-poly[i]);
			if(OnSegment(p,poly[i],poly[(i+1)%n])) ans.push_back(p);
		}
	}
	return ans;
}

vector<Polygon> pieces,new_pieces;

void Cut(Point A,Point B){
	new_pieces.clear();
	for(int i=0;i<pieces.size();i++){
		Polygon left=CutPolygon(pieces[i],A,B);
		Polygon right=CutPolygon(pieces[i],B,A);
		if(left.size()>=3) new_pieces.push_back(left);
		if(right.size()>=3) new_pieces.push_back(right);
	}
	pieces=new_pieces;
}

bool IsPointInPolygon(Point p,Polygon poly){
	int n=poly.size();
	int wn=0;
	for(int i=0;i<n;i++){
		if(OnSegment(p,poly[i],poly[(i+1)%n])) return -1;
		double k=dcmp(Cross(poly[(i+1)%n]-poly[i],p-poly[i]));
		double d1=dcmp(poly[i].y-p.y);
		double d2=dcmp(poly[(i+1)%n].y-p.y);
		if(k>0&&d1<=0&&d2>0) wn++;
		if(k<0&&d1>0&&d2<=0) wn--;
	}
	return wn!=0;
}

bool IsPointInCircle(Point p,Point O,double R){
	return dcmp(Length2(p-O)-R*R)<0;
}

int CircleLineIntersection(Point O,double R,Point a1,Point a2,double &t1,double &t2){
	double A=(a2.x-a1.x)*(a2.x-a1.x)+(a2.y-a1.y)*(a2.y-a1.y);
	double B=2*((a2.x-a1.x)*(a1.x-O.x)+(a2.y-a1.y)*(a1.y-O.y));
	double C=(a1.x-O.x)*(a1.x-O.x)+(a1.y-O.y)*(a1.y-O.y)-R*R;
	double delta=B*B-4*A*C;
	if(dcmp(delta)<0) return 0;
	if(dcmp(delta)==0){
		t1=t2=-B/2/A;
		return 1;
	}
	t1=(-B+sqrt(delta))/(2*A);
	t2=(-B-sqrt(delta))/(2*A);
	return 2;
}

bool CirclePolygonIntersection(Polygon poly,double x,double y,double R){
	Point p=Point(x,y);
	if(IsPointInPolygon(p,poly)!=0) return true;
	if(IsPointInCircle(poly[0],p,R)) return true;
	int n=poly.size();
	double t1,t2;
	for(int i=0;i<n;i++){
		int c=CircleLineIntersection(p,R,poly[i],poly[(i+1)%n],t1,t2);
		if(c==2){
			if(dcmp(t1)>0&&dcmp(t1-1)<0) return true;
			if(dcmp(t2)>0&&dcmp(t2-1)<0) return true;
			//if(IsPointInCircle((poly[i]+poly[(i+1)%n])*0.5,p,R)) return true;
		}if(IsPointInCircle((poly[i]+poly[(i+1)%n])*0.5,p,R)) return true;
	}
	return false;
}

vector<double> area;
void query(double x,double y,double R){
	vector<double> ans;
	for(int i=0;i<pieces.size();i++){
		if(CirclePolygonIntersection(pieces[i],x,y,R)) ans.push_back(area[i]);
	}
	sort(ans.begin(),ans.end());
	printf("%d",ans.size());
	for(int i=0;i<ans.size();i++){
		printf(" ");
		printf("%.2lf",ans[i]);
	}
	printf("\n");
}

double PolygonArea(Polygon poly){
	int n=poly.size();
	double area=0;
	for(int i=1;i<n-1;i++){
		area+=Cross(poly[i]-poly[0],poly[(i+1)]-poly[0]);
	}
	return area/2;
}

int n,m,L,W;

int main(){
	double x1,y1,x2,y2;
	double x,y,R;
	while(scanf("%d%d%d%d",&n,&m,&L,&W)!=EOF){
		if(!n) break;
		pieces.clear();
		Polygon poly;
		poly.push_back(Point(0,0));
		poly.push_back(Point(L,0));
		poly.push_back(Point(L,W));
		poly.push_back(Point(0,W));
		pieces.push_back(poly);
		for(int i=0;i<n;i++){
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			Cut(Point(x1,y1),Point(x2,y2));
		}
		area.clear();
		for(int i=0;i<pieces.size();i++)
			area.push_back(fabs(PolygonArea(pieces[i])));
		for(int i=0;i<m;i++){
			scanf("%lf%lf%lf",&x,&y,&R);
			query(x,y,R);
		}
		printf("\n");
	}
	return 0;
}
