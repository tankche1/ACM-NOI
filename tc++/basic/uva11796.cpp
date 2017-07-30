# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxA=55;
const int INF=~0U>>1;
double eps=1e-8;

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};
typedef Point Vector;
int dcmp(double x){
	if(fabs(x)<eps) return 0;
	return x<0?-1:1;
}

Vector operator + (const Vector &A,const Vector &B){ return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) { return Vector(A.x-B.x,A.y-B.y); }
Vector operator * (const Vector &A,double B) {return Vector(A.x*B,A.y*B);}
Vector operator / (const Vector &A,double B) {return Vector(A.x/B,A.y/B);}
bool operator == (const Point &A,const Point &B) {return dcmp(A.x-B.x)==0&&(dcmp(A.y-B.y)==0);}
double Dot(Point A,Point B) {return A.x*B.x+A.y*B.y;}
double length(Vector A) { return sqrt(Dot(A,A));}
double Cross(Vector A,Vector B) {return A.x*B.y-A.y*B.x;}
double DistanceToSegment(Point P,Point A,Point B){
	if(A==B) return length(P-A);
	Vector v1=B-A,v2=P-A,v3=P-B;
	if(dcmp(Dot(v1,v2))<0) return length(v2);
		else if(dcmp(Dot(v1,v3))>0) return length(v3);
			else return fabs(Cross(v1,v2))/length(v1);
}

Point read(){
	double x,y;
		scanf("%lf%lf",&x,&y);
	return Point(x,y);
}

int T,A,B;
double Min,Max;
Point P[maxA],Q[maxA];

void update(Point P,Point A,Point B){
	Max=max(Max,max(length(P-A),length(P-B)));
	Min=min(Min,DistanceToSegment(P,A,B));
}

int main(){
	double lenA,lenB;
	scanf("%d",&T);
	int kase=0;
	while(T--){
		Min=INF;
		Max=0;
		scanf("%d%d",&A,&B);
		lenA=0;lenB=0;
		for(int i=1;i<=A;i++){
			P[i]=read();
			if(i>1) lenA+=length(P[i]-P[i-1]);
		}
		for(int i=1;i<=B;i++){
			Q[i]=read();
			if(i>1) lenB+=length(Q[i]-Q[i-1]);
		}
		Point Pa=P[1],Pb=Q[1];
		int Sa=1,Sb=1;
		while(Sa<A&&Sb<B){
			double La=length(P[Sa+1]-Pa);
			double Lb=length(Q[Sb+1]-Pb);
			double t=min(La/lenA,Lb/lenB);
			Vector Va=(P[Sa+1]-Pa)/La*t*lenA;
			Vector Vb=(Q[Sb+1]-Pb)/Lb*t*lenB;
			update(Pa,Pb,Pb+Vb-Va);
			Pa=Pa+Va;
			Pb=Pb+Vb;
			if(Pa==P[Sa+1]) Sa++;
			if(Pb==Q[Sb+1]) Sb++;
		}
		printf("Case %d: %.0lf\n", ++kase, (Max-Min));
	}
	return 0;
}
