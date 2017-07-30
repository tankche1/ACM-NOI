# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const double eps=1e-10;
const int maxn=110;
	
int dcmp(double x){
	if(fabs(x)<eps) return 0;
		return x<0?-1:1;
}

struct Point{
	double x,y;
	Point(double x=0,double y=0) :x(x),y(y) {}
};
typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
Vector operator *(const Vector &A,const double B) {return Vector(A.x*B,A.y*B);}

bool operator < (const Point A,const Point B){
	return dcmp(A.x-B.x)<0||(dcmp(A.x-B.x)==0&&A.y>B.y);
}

bool operator == (const Point A,const Point B){
	return dcmp(A.x-B.x)==0&&dcmp(A.y-B.y)==0;
}

double Dot(const Vector &A,const Vector &B){ return A.x*B.x+A.y*B.y;}
double Cross(const Vector &A,const Vector &B) {return A.x*B.y-A.y*B.x;}
double Length(Vector &A) {return sqrt(Dot(A,A));}

/*bool SegmentProperIntersection(Point P1,Point P2,Point P3,Point P4){
	return dcmp(Cross(P2-P1,P3-P1))*dcmp(Cross(P2-P1,P4-P1))<0&&dcmp(Cross(P4-P3,P1-P3))*dcmp(Cross(P4-P3,P2-P3))<0;
}*/
bool SegmentProperIntersection(const Point& a1, const Point& a2, const Point& b1, const Point& b2) {
  double c1 = Cross(a2-a1,b1-a1), c2 = Cross(a2-a1,b2-a1),
  c3 = Cross(b2-b1,a1-b1), c4=Cross(b2-b1,a2-b1);
  //printf("c:%.3lf %.3lf %.3lf %.3lf\n",c1,c2,c3,c4);
  return dcmp(c1)*dcmp(c2)<0 && dcmp(c3)*dcmp(c4)<0;
}

Point GetLineIntersection(const Point &P,const Vector &v,const Point &Q,const Vector &w){
	Vector u=P-Q;
	double t=Cross(u,w)/Cross(w,v);
	return P+v*t;
}

Point p[maxn],L[maxn][2][2];
double x[maxn*maxn];
int cnt=0;

int main(){
	int n,kase=0;double xx,h,b;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
			cnt=0;
		for(int i=0;i<n;i++){
			scanf("%lf%lf%lf",&xx,&h,&b);
			L[i][0][0]=Point((double)(xx-b/2.0),0);L[i][0][1]=Point((double)xx,h);
			L[i][1][0]=Point(xx,h);L[i][1][1]=Point((double)(xx+b/2.0),0);
			x[cnt++]=(double)(xx-b/2.0);
			x[cnt++]=xx;//	printf("%.3lf %.3lf %.3lf %.3lf \n",x[cnt-1].x,x[cnt-1].y,xx,h);
			x[cnt++]=(double)(xx+b/2.0);
			//	printf("%.3lf %.3lf %.3lf \n",(double)(xx-b/2.0),h,(double)(xx+b/2.0));
				
		}
	//	for(int i=0;i<cnt;i++)
	//					printf("%.3lf %.3lf\n",x[i].x,x[i].y);
		for(int i=0;i<n;i++)
			for(int j=i+1;j<n;j++)
				for(int a=0;a<2;a++)
					for(int b=0;b<2;b++){
						Point P1=L[i][a][0],P2=L[i][a][1],P3=L[j][b][0],P4=L[j][b][1];
						//printf("P1:%.3lf %.3lf P2 : %.3lf %.3lf\n",P1.x,P1.y,P2.x,P2.y);
						//printf("P3:%.3lf %.3lf P4 : %.3lf %.3lf\n",P3.x,P3.y,P4.x,P4.y);
						if(SegmentProperIntersection(P1,P2,P3,P4)){
						//	puts("FUCK");
							x[cnt++]=GetLineIntersection(P1,P2-P1,P3,P4-P3).x;
						}
					}
		sort(x,x+cnt);
		cnt=unique(x,x+cnt)-x;
					//for(int i=0;i<cnt;i++)
					//	printf("%.3lf\n",x[i]);
		double ans=0,lastp=0;
		for(int i=0;i<cnt;i++){
			double maxy=0;
			for(int j=0;j<n;j++)
				for(int a=0;a<2;a++){
					Point P1=L[j][a][0],P2=L[j][a][1];
					Point y(x[i],0),yy(0,1);
					Point pp=GetLineIntersection(P1,P2-P1,y,yy);
					if(dcmp(pp.x-P1.x)>=0&&dcmp(P2.x-pp.x)>=0)
					maxy=max(maxy,pp.y);
				}
			//	printf("%.3lf\n",maxy);
			if(dcmp(maxy)!=0||dcmp(lastp)!=0){
				ans+=sqrt((lastp-maxy)*(lastp-maxy)+(x[i]-x[i-1])*(x[i]-x[i-1]));
			}
			lastp=maxy;
		}
		printf("Case %d: %.0lf\n\n",++kase,ans);
	}
	return 0;
}
