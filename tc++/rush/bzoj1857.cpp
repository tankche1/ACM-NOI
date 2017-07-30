# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const double eps=1e-12;
struct Point{
	double x,y;
	Point() {}
	Point(double x,double y) :x(x),y(y) {}
};Point A[2],B[2],P[2];
Point operator + (const Point A,const Point B){
	return Point(A.x+B.x,A.y+B.y);
}
Point operator - (const Point A,const Point B){
	return Point(A.x-B.x,A.y-B.y);
}
Point operator / (const Point A,const double B){
	return Point(A.x/B,A.y/B);
}
double p,q,r;

double dist(Point A,Point B){
	return sqrt((B.x-A.x)*(B.x-A.x)+(B.y-A.y)*(B.y-A.y));
}

double get(){
	return dist(A[0],P[0])/p+dist(P[0],P[1])/r+dist(P[1],B[1])/q;
}

double Three(int k){
	Point L=A[k],R=B[k];
	double A1,A2;Point M1,M2,del;
	while(dist(L,R)>eps){
		del=(R-L)/3;
        M2=R-del;M1=M2-del;
		P[k]=M1;if(k) A1=Three(1-k);else A1=get();
		P[k]=M2;if(k) A2=Three(1-k);else A2=get();
		if(A1<A2) R=M2;
			else L=M1;
	}
	if(dist(A[k],B[k])<=eps){//it's a point
		P[k]=A[k];
		if(k) A1=Three(1-k);else A1=get();
	}
	return A1;
}

int main(){
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf",&A[0].x,&A[0].y,&B[0].x,&B[0].y,&A[1].x,&A[1].y,&B[1].x,&B[1].y);
	scanf("%lf%lf%lf",&p,&q,&r);
	printf("%.2lf\n",Three(1));
	return 0;
}
