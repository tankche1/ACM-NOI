# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=510;

const double eps = 1e-10;
int dcmp(double x) {
  if(fabs(x) < eps) return 0; else return x < 0 ? -1 : 1;
}

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};

typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
double Dot(const Vector &A,const Vector &B) {return A.x*B.x+A.y*B.y;}
double Cross(const Vector &A,const Vector &B) {return A.x*B.y-A.y*B.x;}

bool operator < (const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool operator == (const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

bool SegmentProperIntersection(Point a1,Point a2,Point b1,Point b2){
	double c1=Cross(a2-a1,b1-a1),c2=Cross(a2-a1,b2-a1);
	double c3=Cross(b2-b1,a1-b1),c4=Cross(b2-b1,a2-b1);
	return (dcmp(c1)*dcmp(c2)<0)&&(dcmp(c3)*dcmp(c4)<0);
}

bool isPointOnSegment(Point p,Point a1,Point a2){
	return dcmp(Cross(a1-p,a2-p))==0&&dcmp(Dot(a1-p,a2-p))<0;
}

bool isPointInPolygon(Point p,Point *poly,int n){
	int wn=0;
	for(int i=0;i<n-1;i++){
		if(p==poly[i]||p==poly[i+1]||isPointOnSegment(p,poly[i],poly[i+1])) return -1;
		int k=dcmp(Cross(poly[i+1]-poly[i],p-poly[i]));
		int d1=dcmp(poly[i].y-p.y);
		int d2=dcmp(poly[i+1].y-p.y);
		if(k>0&&d1<=0&&d2>0) wn++;
		if(k<0&&d2<=0&&d1>0) wn--;
	}
	if(wn!=0) return 1;
	return 0;
}

int ConvexHull(Point *p,int n,Point *ch){
	sort(p,p+n);
	n=unique(p,p+n)-p;
	int m=0;
	for(int i=0;i<n;i++){
		while(m>1&&(Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0)) m--;
		ch[m++]=p[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--){
		while(m>k&&(Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0)) m--;
		ch[m++]=p[i];
	}
	return m;
}

int n,m;
Point Red[maxn],Blue[maxn];
Point red[maxn],blue[maxn];
int main(){
	double x,y;
	while(scanf("%d%d",&n,&m)!=EOF){
		if(!n) break;
		for(int i=0;i<n;i++){
			scanf("%lf%lf",&x,&y);
			Red[i]=Point(x,y);
		}
		for(int i=0;i<m;i++){
			scanf("%lf%lf",&x,&y);
			Blue[i]=Point(x,y);
		}
		int nn=ConvexHull(Red,n,red);
		int mm=ConvexHull(Blue,m,blue);
		bool ans=true;
		/*for(int i=0;i<nn;i++){
			printf("%.7lf %.7lf\n",red[i].x,red[i].y);
		}*/
		/*for(int i=0;i<mm;i++)
			printf("%.7lf %.7lf\n",blue[i].x,blue[i].y);*/
		for(int i=0;i<nn-1;i++){
			for(int j=0;j<mm-1;j++){
				if(SegmentProperIntersection(red[i],red[i+1],blue[j],blue[j+1])){
					ans=false;break;
				}
			}
		}
		if(isPointInPolygon(red[0],blue,mm)!=0) ans=false;
		if(isPointInPolygon(blue[0],red,nn)!=0) ans=false;
		if(nn==1&&mm==1&&red[0]==blue[0]) ans=false;
		if(ans) puts("Yes");
		else puts("No");
	}
	return 0;
}
