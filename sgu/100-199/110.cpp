# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=55;
const int INF=~0U>>1;
const double eps=1e-10;
struct Point{
	double x,y,z;
	Point() {}
	Point(double x,double y,double z):x(x),y(y),z(z) {}
	void print(){
		printf("%.2lf %.2lf %.2lf ",x,y,z);
	}
};
Point operator + (Point a,Point b) {return Point(a.x+b.x,a.y+b.y,a.z+b.z);}
Point operator -  (Point a,Point b) {return Point(a.x-b.x,a.y-b.y,a.z-b.z);}
Point operator * (Point a,double b) {return Point(a.x*b,a.y*b,a.z*b);}
double Dot_mul(Point a,Point b){return a.x*b.x+b.y*a.y+a.z*b.z;}
double Dist(Point a) {return sqrt(a.x*a.x+a.y*a.y+a.z*a.z);}
Point normal(Point v){
	double len=Dist(v);
	return Point(v.x/len,v.y/len,v.z/len);
}
int dcmp(double x){
	if(fabs(x)<eps) return 0;
		return x<0?-1:1;
}
double GetDistFromLineToCircle(Point s,Point v,Point C,double R){
	Point e=s-C;
	double a=Dot_mul(v,v);
	double b=2*Dot_mul(v,e);
	double c=Dot_mul(e,e)-R*R;
	double delta=b*b-4*a*c;
	if(delta>=0){
		double s1=(-b+sqrt(delta))/(2*a);
		double s2=(-b-sqrt(delta))/(2*a);
		if(s1>s2) swap(s1,s2);
		if(dcmp(s1)>=0) return s1;
		if(dcmp(s2)>=0) return s2;
	}
	return INF;
}
double R[maxn];
Point Circle[maxn];
Point s,e;
int n;
int out[maxn];
void solve(){
	out[0]=0;
	int pre=-1;
	for(;;){
		int idx=-1;double mink=INF,d;
			//s.print();e.print();puts("");
		e=normal(e);
		for(int i=1;i<=n;i++)
			if(i!=pre&&dcmp(mink-(d=GetDistFromLineToCircle(s,e,Circle[i],R[i])))>0) idx=i,mink=d;
			//	printf("mink:%.3lf\n",mink);
		if(idx!=-1){
			Point p=s+(e*mink);
			Point v=normal(Circle[idx]-p);
			double dis=Dot_mul(e,v)/Dist(v);
			v=v*dis;
			s=p;e=e-v*2;
			out[++out[0]]=idx;pre=idx;
			if(out[0]>10) break;
		}
		else break;
	}
	if(out[0]>0)
		printf("%d",out[1]);
	for(int i=2;i<=10&&i<=out[0];i++)
		printf(" %d",out[i]);
	if(out[0]>10) printf(" etc.");
	puts("");
}
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lf%lf%lf%lf",&Circle[i].x,&Circle[i].y,&Circle[i].z,&R[i]);
	scanf("%lf%lf%lf%lf%lf%lf",&s.x,&s.y,&s.z,&e.x,&e.y,&e.z);
	e=e-s;
	solve();
	return 0;
}
