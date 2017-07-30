# include<stdio.h>
# include<string.h>
# include<math.h>
# include<string>
# include<vector>
# include<iostream>
# include<algorithm>
using namespace std;
const double PI = acos(-1);
double eps=1e-10;
int dcmp(double x){
	if(fabs(x)<eps) return 0;
	return x>0?1:-1;
}


struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	void print() {printf("%.6lf %.6lf\n",x,y);}
};

bool operator < (const Point &A,const Point &B) {return A.x==B.x?A.y<B.y:A.x<B.x;}
bool operator == (const Point &A,const Point &B) {return dcmp(A.x-B.x)==0&&dcmp(A.y-B.y);}

typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
Vector operator * (const Vector &A,double B) {return Vector(A.x*B,A.y*B);}
Vector operator / (const Vector &A,double B) {return Vector(A.x/B,A.y/B);}
double Dot(Point A,Point B) {return A.x*B.x+A.y*B.y;}
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double Length(Vector A) {return sqrt(Dot(A,A));}
double Angel(Vector A,Vector B) {return acos(Dot(A,B)/Length(A)/Length(B));}
double angel(Vector A) {return atan2(A.y,A.x);}

Vector Rotate(Vector A,double rad){return Vector(A.x*cos(rad)-A.y*sin(rad),A.x*sin(rad)+A.y*cos(rad));}

Vector Normal(Vector A){
	//return Rotate(A,PI/2);
	  double L = Length(A);
  return Vector(-A.y/L, A.x/L);
}

Point MiddleSegment(Point A,Point B){return Point((A.x+B.x)/2,(A.y+B.y)/2);}
Point GetLineIntersection(Point P,Vector v,Point Q,Vector w){
	Vector u=P-Q;
	double t=Cross(w,u)/Cross(v,w);
	return P+v*t;
}

double DistancetoLine(Point P,Point A,Point B){
	//return fabs(Cross(A-P,B-P))/Length(B-A);
	Vector v1 = B - A, v2 = P - A;
  return fabs(Cross(v1, v2)) / Length(v1); // 如果不取绝对值，得到的是有向距离
}

struct Circle{
	Point c;
	double r;
	Circle(Point c,double r):c(c),r(r) {}
	Point point(double rad){
		return Point(c.x+r*cos(rad),c.y+r*sin(rad));
	}
};

struct Line{
	Point p;
	Vector v;
	Line(Point p,Vector v):p(p),v(v) {}
	Point point(double t){
		return p+v*t;
	}
	Line move(double d){
		return Line(p+Normal(v)*d,v);
	}
};

/*double lineAngleDegree(Vector v){
	double ang=angel(v)*180.0/PI;
	if(ang< 0) ang += 360.0;//坑爹的精度
	while(ang-180 >= 0) ang -= 180.0;
	return ang;
}*/

double lineAngleDegree(Vector v) {
  double ang = angel(v)*180.0/PI;
  while(dcmp(ang) < 0) ang += 360.0;
  while(dcmp(ang-180) >= 0) ang -= 180.0;
  return ang;
}

int getTangents(Point p,Circle C,Vector* v){
	Vector u=C.c-p;
	double dist=Length(u);
	if(dist<C.r) return 0;
	else if(dcmp(dist-C.r)==0) {
		v[0]=Rotate(u,PI/2);
		return 1;
	}
	double ang=asin(C.r/dist);
	v[0]=Rotate(u,-ang);
	v[1]=Rotate(u,+ang);
	return 2;
}

Point GetLineProjection(Point P,Point A,Vector v){
	return A+v*(Dot(v,P-A)/Dot(v,v));
}

int getLineCircleIntersection(Line L, Circle C, double& t1, double& t2, vector<Point>& sol){
  double a = L.v.x, b = L.p.x - C.c.x, c = L.v.y, d = L.p.y - C.c.y;
  double e = a*a + c*c, f = 2*(a*b + c*d), g = b*b + d*d - C.r*C.r;
  double delta = f*f - 4*e*g; // 判别式
  if(dcmp(delta) < 0) return 0; // 相离
  if(dcmp(delta) == 0) { // 相切
    t1 = t2 = -f / (2 * e); sol.push_back(L.point(t1));
    return 1;
  }
  // 相交
  t1 = (-f - sqrt(delta)) / (2 * e); sol.push_back(L.point(t1));
  t2 = (-f + sqrt(delta)) / (2 * e); sol.push_back(L.point(t2));
  return 2;
	/*Point p=GetLineProjection(C.c,L.p,L.v);
	double dist=Length(C.c-p);
	Vector v=L.v/Length(L.v);
	if(dcmp(dist-C.r)>0) {return 0;}
	else if(dcmp(dist-C.r)==0) {
		t1=(p.x-L.p.x)/v.x;sol.push_back(p);
		return 1;
	}
	double LL=sqrt(C.r*C.r-dist*dist);
	Point A=p-v*LL;
	t1=(A.x-L.p.x)/L.v.x;sol.push_back(A);
	A=p+v*LL;
	t2=(A.x-L.p.x)/L.v.x;sol.push_back(A);
	return 2;*/
}

int getCircleIntersection(Circle C1,Circle C2,vector<Point>& sol){
	double d=Length(C1.c-C2.c);
	if(dcmp(d)==0){
		if(dcmp(C1.r-C2.r)==0) return -1;
		return 0;
	}
	if(dcmp(C1.r+C2.r-d)<0) return 0;
	if(dcmp(dcmp(C1.r-C2.r)-d)>0) return 0;
	double a=angel(C2.c-C1.c);
	double da=acos((C1.r*C1.r+d*d-C2.r*C2.r)/(2*C1.r*d));
	Point p1=C1.point(a-da),p2=C1.point(a+da);
		
	sol.push_back(p1);
	if(p1==p2) return 1;
	sol.push_back(p2);
	return 2;
}

Circle CircumscribedCircle(double x1,double y1,double x2,double y2,double x3,double y3){
	/*Point A(x1,y1),B(x2,y2),C(x3,y3);
	Point m1=MiddleSegment(A,B);
	Point m2=MiddleSegment(B,C);
	Point P=GetLineIntersection(m1,Rotate(B-m1,PI/2),m2,Rotate(C-m2,PI/2));
	return Circle(P,Length(A-P));*/
	Point p1(x1,y1),p2(x2,y2),p3(x3,y3);
double Bx = p2.x-p1.x, By = p2.y-p1.y;
  double Cx = p3.x-p1.x, Cy = p3.y-p1.y;
  double D = 2*(Bx*Cy-By*Cx);
  double cx = (Cy*(Bx*Bx+By*By) - By*(Cx*Cx+Cy*Cy))/D + p1.x;
  double cy = (Bx*(Cx*Cx+Cy*Cy) - Cx*(Bx*Bx+By*By))/D + p1.y;
  Point p = Point(cx, cy);
  return Circle(p, Length(p1-p));
}

Circle InscribedCircle(double x1,double y1,double x2,double y2,double x3,double y3){
	/*Point A(x1,y1),B(x2,y2),C(x3,y3);
	Vector va=Rotate(B-A,Angel(B-A,C-A)/2);
	Vector vb=Rotate(C-B,Angel(C-B,A-B)/2);
	Point c=GetLineIntersection(A,va,B,vb);
	return Circle(c,DistancetoLine(c,A,B));*/
	Point p1(x1,y1),p2(x2,y2),p3(x3,y3);
	  double a = Length(p2-p3);
  double b = Length(p3-p1);
  double c = Length(p1-p2);
  Point p = (p1*a+p2*b+p3*c)/(a+b+c);
  return Circle(p, DistancetoLine(p, p1, p2));
}

vector<Point> CircleThroughPointTangentToLineGivenRadius(Point p,Line L,double r){
	Line A=L.move(-r),B=L.move(r);
	Circle C(p,r);
	vector<Point> ans;
	double t1,t2;
	getLineCircleIntersection(A,C,t1,t2,ans);
	getLineCircleIntersection(B,C,t1,t2,ans);
	return ans;
}

vector<Point> CircleTangentToTwoLinesWithRadius(Line A,Line B,double r){
	Line A1=A.move(-r),A2=A.move(r);
	Line B1=B.move(-r),B2=B.move(r);
	vector<Point> ans;
	ans.push_back(GetLineIntersection(A1.p,A1.v,B1.p,B1.v));
	ans.push_back(GetLineIntersection(A1.p,A1.v,B2.p,B2.v));
	ans.push_back(GetLineIntersection(A2.p,A2.v,B1.p,B1.v));
	ans.push_back(GetLineIntersection(A2.p,A2.v,B2.p,B2.v));
	return ans;
}

void format(Circle C){
	printf("(%.6lf,%.6lf,%.6lf)\n",C.c.x,C.c.y,C.r);
}

void format(vector<Point> ans) {
  int n = ans.size();
  sort(ans.begin(), ans.end());
  printf("[");
  if(n) {
    printf("(%.6lf,%.6lf)", ans[0].x, ans[0].y);
    for(int i = 1; i < n; i++) printf(",(%.6lf,%.6lf)", ans[i].x, ans[i].y);
  }
  printf("]\n");
}

void format(vector<double>& ans) {
  int n = ans.size();
  sort(ans.begin(), ans.end());
  printf("[");
  if(n) {
    printf("%.6lf", ans[0]);
    for(int i = 1; i < n; i++) printf(",%.6lf", ans[i]);
  }
  printf("]\n");
}

Line getLine(double x1,double y1,double x2,double y2){
	Point c(x1,y1);
	Vector v=Point(x2,y2)-c;
	return Line(c,v);
}

vector<Point> FUCKYOU(Circle C1,Circle C2,double r){
	Vector v = C2.c - C1.c;
	vector<Point> ans;
  double dist = Length(v);
  int d = dcmp(dist - C1.r -C2.r - r*2);
  if(d > 0) return ans;
	C1.r+=r;C2.r+=r;

	getCircleIntersection(C1,C2,ans);
	return ans;
}

int main(){
	char op[30];
	double x1,y1,x2,y2,x3,y3,xc,yc,r,xp,yp,x4,y4,r1,r2;
	while(cin >> op){
		if(strcmp(op,"CircumscribedCircle")==0){
			scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3);
			format(CircumscribedCircle(x1,y1,x2,y2,x3,y3));
		}
		else if(strcmp(op,"InscribedCircle")==0){
			scanf("%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3);
			format(InscribedCircle(x1,y1,x2,y2,x3,y3));
		}
		else if(strcmp(op,"TangentLineThroughPoint")==0){
			scanf("%lf%lf%lf%lf%lf",&xc,&yc,&r,&xp,&yp);
			Vector v[2];
			vector<double> ans;
			int cnt=getTangents(Point(xp,yp),Circle(Point(xc,yc),r),v);
			for(int i=0;i<cnt;i++) ans.push_back(lineAngleDegree(v[i]));
			format(ans);
		}
		else if(strcmp(op,"CircleThroughAPointAndTangentToALineWithRadius")==0) {
			scanf("%lf%lf%lf%lf%lf%lf%lf",&xp,&yp,&x1,&y1,&x2,&y2,&r);
			format(CircleThroughPointTangentToLineGivenRadius(Point(xp, yp), getLine(x1, y1, x2, y2), r));
		}
		else if(strcmp(op,"CircleTangentToTwoLinesWithRadius")==0){
			scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&x2,&y2,&x3,&y3,&x4,&y4,&r);
			format(CircleTangentToTwoLinesWithRadius(getLine(x1,y1,x2,y2),getLine(x3,y3,x4,y4),r));
		}
		else if(strcmp(op,"CircleTangentToTwoDisjointCirclesWithRadius")==0){
			scanf("%lf%lf%lf%lf%lf%lf%lf",&x1,&y1,&r1,&x2,&y2,&r2,&r);
			format(FUCKYOU(Circle(Point(x1,y1),r1),Circle(Point(x2,y2),r2),r));
		}
	}
	return 0;
}
