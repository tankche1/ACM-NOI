# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=110;

const double eps = 1e-12;
double dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (const Point& A, const Point& B) {
  return Vector(A.x+B.x, A.y+B.y);
}

Vector operator - (const Point& A, const Point& B) {
  return Vector(A.x-B.x, A.y-B.y);
}

Vector operator * (const Point& A, double v) {
  return Vector(A.x*v, A.y*v);
}

Vector operator / (const Point& A, double v) {
  return Vector(A.x/v, A.y/v);
}

double Cross(const Vector& A, const Vector& B) {
  return A.x*B.y - A.y*B.x;
}

double Dot(const Vector& A, const Vector& B) {
  return A.x*B.x + A.y*B.y;
}

double Length(const Vector& A) {
  return sqrt(Dot(A,A));
}

bool operator < (const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool operator == (const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool OnSegment(Point p,Point a1,Point a2){
	return dcmp(Cross(a2-a1,p-a1))==0&&dcmp(Dot(p-a1,p-a2))<0;
}

bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
	double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
	return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}

int n;
Point p1[maxn],p2[maxn];
bool G[maxn*2][maxn*2];
bool vis[maxn*2];
int m;

bool dfs(int x){
	vis[x]=true;
	if(x==1) return true;
	for(int i=0;i<m;i++)
		if(G[x][i]&&!vis[i]) if(dfs(i)) return true;
	return false;
}

bool OnAnySegment(Point p){
	for(int i=0;i<n;i++)
		if(OnSegment(p,p1[i],p2[i])) return true;
	return false;
}

bool IntersectWithAnySegment(Point a1,Point a2){
	for(int i=0;i<n;i++){
		if(SegmentProperIntersection(a1,a2,p1[i],p2[i])) return true;
	}
	return false;
}

bool find_path(){
	vector<Point> P;
	P.push_back(Point(0,0));
	P.push_back(Point(10000,10000));
	for(int i=0;i<n;i++){
		if(!OnAnySegment(p1[i])) P.push_back(p1[i]);
		if(!OnAnySegment(p2[i])) P.push_back(p2[i]);
	}
	m=P.size();
	memset(G,false,sizeof(G));
	for(int i=0;i<m;i++){
		for(int j=i+1;j<m;j++){
			if(!IntersectWithAnySegment(P[i],P[j]))
				G[i][j]=G[j][i]=1;
		}
	}
	memset(vis,false,sizeof(vis));
	return dfs(0);
}

int main(){
	double x1,y1,x2,y2;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		for(int i=0;i<n;i++){
			scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
			p1[i]=Point(x1,y1);p2[i]=Point(x2,y2);
			Vector v=p2[i]-p1[i];
			v=v/(Length(v));
			p1[i]=p1[i]-(v*(1e-6));
			p2[i]=p2[i]+(v*(1e-6));
		}
		if(find_path()) puts("no");
			else puts("yes");
	}
	return 0;
}
