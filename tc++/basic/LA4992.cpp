# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
double eps=1e-8;
const int maxn=50010;

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};

typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
Vector operator * (const Vector &A,const double &B) {return Vector(A.x*B,A.y*B);}
double Dot(const Vector &A,const Vector &B) {return A.x*B.x+A.y*B.y;}
double Cross(const Vector &A,const Vector &B) {return A.x*B.y-A.y*B.x;}

struct Line{
	Point P;
	Vector v;
	double ang;
	Line(){}
	Line(Point P,Vector v):P(P),v(v) {ang=atan2(v.y,v.x);}
	bool operator < (const Line &rhs)const{
		return ang<rhs.ang;
	}
};

bool OnLeft(Line L,Point p){
	return Cross(L.v,p-L.P)>eps;
}

Point GetLineIntersection(Line A,Line B){
	Vector u=A.P-B.P;
	double t=Cross(B.v,u)/Cross(A.v,B.v);
	return A.P+A.v*t;
}

int HalfplaneIntersection(Line *L,int n,Point *poly){
	sort(L,L+n);
	Point p[n];
	Line q[n];
	int first,last;
	q[first=last=0]=L[0];
	for(int i=1;i<n;i++){
		while(first<last&&!OnLeft(L[i],p[last-1])) last--;
		while(first<last&&!OnLeft(L[i],p[first])) first++;
		q[++last]=L[i];
		if(fabs(Cross(q[last].v,q[last-1].v))<eps){
			last--;
			if(OnLeft(q[last],L[i].P))
				q[last]=L[i];
		}
		if(first<last) p[last-1]=GetLineIntersection(q[last-1],q[last]);
	}
	while(first<last&&!OnLeft(q[first],p[last-1])) last--;
	if(last-first<=1) return 0;
	p[last]=GetLineIntersection(q[last],q[first]);
	int m=0;
	for(int i=first;i<=last;i++) poly[m++]=p[i];
	return m;
}

int n;
Point p[maxn],ch[maxn];
Line line[maxn],L[maxn];
int main(){
	double x,y;
	while(scanf("%d",&n)!=EOF){
		for(int i=0;i<n;i++){
			scanf("%lf%lf",&x,&y);
			p[i]=Point(x,y);
		}
		reverse(p,p+n);
		//for(int i=0;i<n;i++)
		//	printf("%lf %lf\n",p[i].x,p[i].y);
		p[n]=p[0];
		for(int i=0;i<n;i++) line[i]=Line(p[i],p[i+1]-p[i]);
		int LL=1,RR=n,M;
		while(LL<=RR){
			M=(LL+RR)>>1;
			//printf("LL:%d RR:%d M:%d\n",LL,RR,M);
			int m=n;
			for(int i=0;i<n;i++) L[i]=line[i];
			for(int i=0;i+M-1<n;i++){
				int to=i+M,from=i==0?n-1:i-1;
				L[m++]=Line(p[from],p[to]-p[from]);
				//printf("from:%d to:%d\n",from,to);
			}
			if(((n-M)<=2)||(!HalfplaneIntersection(L,m,ch))) RR=M-1;
				else LL=M+1;
		}
		printf("%d\n",RR+1);
	}
	return 0;
}
