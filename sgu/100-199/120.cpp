/*
sgu120 给正n边形两点 搞出n边形 方法是搞出中心然后向量旋转
*/
# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int N = 155;  
const double pi = acos(-1.0);  
  
int n, n1, n2;  
  
struct Point {  
    double x, y;  
    int id;  
    Point() {}  
    Point(double x, double y) {  
        this->x = x;  
        this->y = y;  
    }  
} p1, p2, ans[N];  
  
bool cmpid(Point a, Point b) {  
    return a.id < b.id;  
}  
  
typedef Point Vector;  
  
  
Vector operator + (Vector A, Vector B) {  
    return Vector(A.x + B.x, A.y + B.y);  
}  
  
Vector operator - (Vector A, Vector B) {  
    return Vector(A.x - B.x, A.y - B.y);  
}  
  
Vector operator * (Vector A, double p) {  
    return Vector(A.x * p, A.y * p);  
}  
  
Vector operator / (Vector A, double p) {  
    return Vector(A.x / p, A.y / p);  
}  
  
Vector Rotate(Vector A, double rad) {  
    return Vector(A.x * cos(rad) - A.y * sin(rad), A.x * sin(rad) + A.y * cos(rad));  
}  
  
double Dot(Vector A, Vector B) {return A.x * B.x + A.y * B.y;} //点积  
double Length(Vector A) {return sqrt(Dot(A, A));} //向量的模  

int main(){
	int ok;
	double d1,d2,d3;
	Vector v1,v2,v3;
	Point midpoint;
	double length1,length2;
	while(scanf("%d%d%d",&n,&n1,&n2)!=EOF){
		scanf("%lf%lf%lf%lf",&p1.x,&p1.y,&p2.x,&p2.y);
		if(n1>n2) swap(n1,n2),swap(p1,p2);
		d1=2*pi/n;d1=d1*(n2-n1);ok=-1;
		if(d1>=pi) d1=2*pi-d1,ok=1;
		//printf("d1:%.3lf d1:%d\n",d1,(int)(d1/pi*180));
		d2=(pi-d1)/2.0;
		v1=(p2-p1)*ok;
		v2=Rotate(v1,d2);
		length1=Length(p1-p2);
		if(d1>pi||d1<pi)
			length2=length1*sin(d2)/sin(d1);
		else length2=length1/2.0;
		v2=v2*(length2/length1);
		if(ok==-1) midpoint=p2+v2;
		else midpoint=p1+v2;
		v3=p1-midpoint;d3=2*pi/n;int now=n1;
		for(int i=0;i<n;i++){
			ans[i]=midpoint+v3;
			v3=Rotate(v3,d3);
			ans[i].id=now;
			if(--now==0) now=n;
		}
		sort(ans,ans+n,cmpid);
		for(int i=0;i<n;i++)
			printf("%.6lf %.6lf\n",ans[i].x,ans[i].y);
	}
	return 0;
}
