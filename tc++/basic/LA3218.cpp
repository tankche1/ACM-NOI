# include<stdio.h>
# include<string.h>
# include<vector>
# include<math.h>
# include<algorithm>
using namespace std;
const double eps=1e-8;
const int maxn=10010;
const int maxp=110;
const int maxm=10010;

double dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point {
  double x, y;
  Point(double x=0, double y=0):x(x),y(y) { }
};

typedef Point Vector;

Vector operator + (Vector A, Vector B) {
  return Vector(A.x+B.x, A.y+B.y);
}

Vector operator - (Point A, Point B) {
  return Vector(A.x-B.x, A.y-B.y);
}

Vector operator * (Vector A, double p) {
  return Vector(A.x*p, A.y*p);
}

bool operator < (const Point& a, const Point& b) {
  return dcmp(a.x - b.x) < 0 || (dcmp(a.x - b.x) == 0 && dcmp(a.y - b.y) < 0);
}

bool operator == (const Point& a, const Point &b) {
  return dcmp(a.x-b.x) == 0 && dcmp(a.y-b.y) == 0;
}

double Dot(Vector A, Vector B) { return A.x*B.x + A.y*B.y; }
double Cross(Vector A, Vector B) { return A.x*B.y - A.y*B.x; }
double Length(Vector A) { return sqrt(Dot(A, A)); }

typedef vector<Point> Polygon;

Point GetLineIntersection(const Point &P,const Vector &v,const Point &Q,const Vector &w){
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}

bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
	double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
	return dcmp(c1)*dcmp(c2)<0&&dcmp(c3)*dcmp(c4)<0;
}

bool OnSegment(Point p,Point a1,Point a2){
	return dcmp(Cross(a2-a1,p-a1))==0&&dcmp(Dot(p-a1,p-a2))<0;
	//return dcmp(Cross(a1-p, a2-p)) == 0 && dcmp(Dot(a1-p, a2-p)) < 0;
}

double PolygonArea(Polygon poly){
	int n=poly.size();
	double area=0;
	for(int i=1;i<n-1;i++){
		area+=Cross(poly[i]-poly[0],poly[(i+1)]-poly[0]);
	}
	return area/2;
}

struct Edge {
  int from, to; // 起点，终点，左边的面编号
  double ang;
	Edge(int from,int to,double ang) :from(from),to(to),ang(ang) {}
};

struct PSLG{
	int n,m,face_cnt;
	double x[maxm],y[maxm];
	vector<Edge> edges;
	vector<int> G[maxm];
	int vis[maxm*2],left[maxm*2],prev[maxm*2];
	
	vector<Polygon> faces;
	double area[maxm];
		
	void init(int n){
		this->n=n;
		for(int i=0;i<n;i++) G[i].clear();
		face_cnt=m=0;
		edges.clear();
		faces.clear();
	}
	
	double getAngle(int from,int to){
		return atan2(y[to]-y[from],x[to]-x[from]);
	}
	
	void add_edge(int from,int to){
		double ang=getAngle(from,to);
			edges.push_back(Edge(from,to,ang));
		ang=getAngle(to,from);
		edges.push_back(Edge(to,from,ang));
		int m=edges.size();
		G[from].push_back(m-2);
		G[to].push_back(m-1);
	}
	
	void Build(){
		for(int u=0;u<n;u++){
			int d = G[u].size();
			for(int i = 0; i < d; i++)
        		for(int j = i+1; j < d; j++) // 这里偷个懒，假设从每个点出发的线段不会太多
          			if(edges[G[u][i]].ang > edges[G[u][j]].ang) swap(G[u][i], G[u][j]);
			for(int i=0;i<d;i++)
				prev[G[u][(i+1)%d]]=G[u][i];
		}
		memset(vis,0,sizeof(vis));
		face_cnt=0;
		for(int u=0;u<n;u++)
			for(int i=0;i<G[u].size();i++){
				int e=G[u][i];
				if(!vis[e]){
					Polygon poly;
					face_cnt++;
					for(;;){
						vis[e]=true;left[e]=face_cnt;
						int from=edges[e].from;
						poly.push_back(Point(x[from],y[from]));
						e=prev[e^1];
						if(e==G[u][i]) break;
					}
					faces.push_back(poly);
				}
			}
		for(int i=0;i<faces.size();i++)
			area[i]=PolygonArea(faces[i]);
	}
};
PSLG g;

int n,c;
Point P[maxp],V[maxp*maxp/2];
double x,y;
	
int ID(Point p){
	return lower_bound(V,V+c,p)-V;
}

Polygon simplify(Polygon poly){
	Polygon ans;
	int n=poly.size();
	for(int i=0;i<n;i++){
		if(dcmp(Cross(poly[i]-poly[(i+1)%n],poly[(i+2)%n]-poly[(i+1)%n]))!=0) ans.push_back(poly[(i+1)%n]);
	}
	return ans;
}

void build_graph(){
	vector<double> Dist[maxn];
	for(int i=0;i<n;i++)
		V[i]=P[i];
	c=n;
	for(int i=0;i<n;i++){
		for(int j=i+1;j<n;j++){
			if(SegmentProperIntersection(P[i],P[(i+1)%n],P[j],P[(j+1)%n])){
				V[c++]=GetLineIntersection(P[i],P[(i+1)%n]-P[i],P[j],P[(j+1)%n]-P[j]);
				Dist[i].push_back(Length(V[c-1]-P[i]));
				Dist[j].push_back(Length(V[c-1]-P[j]));
			}
		}
	}
	sort(V,V+c);
	c=unique(V,V+c)-V;
	g.init(c);
	for(int i=0;i<c;i++){
		g.x[i]=V[i].x;
		g.y[i]=V[i].y;
	}
	for(int i=0;i<n;i++){
		Dist[i].push_back(0);
		Dist[i].push_back(Length(P[(i+1)%n]-P[i]));
		sort(Dist[i].begin(),Dist[i].end());
		double len=Length(P[(i+1)%n]-P[i]);
		Vector v=P[(i+1)%n]-P[i];
		for(int j=0;j<Dist[i].size()-1;j++){
			Point a=P[i]+v*(Dist[i][j]/len);
			Point b=P[i]+v*(Dist[i][j+1]/len);
			if(a==b) continue;
			g.add_edge(ID(a),ID(b));
		}
	}
	g.Build();
	Polygon poly;
	for(int i=0;i<g.faces.size();i++)
		if(g.area[i]<0){
			poly=g.faces[i];
			reverse(poly.begin(),poly.end());
			poly = simplify(poly);
			break;
		}
		int m=poly.size();
		printf("%d\n",m);
		int start=0;
		for(int i=1;i<m;i++){
			if(poly[i]<poly[start]) start=i;
		}
		for(int i = start; i < m; i++)
			printf("%.4lf %.4lf\n", poly[i].x, poly[i].y);
		for(int i = 0; i < start; i++)
			printf("%.4lf %.4lf\n", poly[i].x, poly[i].y);
}

int main(){
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
		scanf("%lf%lf",&x,&y);
		P[i]=Point(x,y);
		}
		build_graph();
	}
	return 0;
}
