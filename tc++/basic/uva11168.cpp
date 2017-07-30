# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int INF=~0U>>1;

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
};

typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
double Cross(const Vector &A,const Vector &B) {return A.x*B.y-A.y*B.x;}

bool operator < (const Point& p1, const Point& p2) {
  return p1.x < p2.x || (p1.x == p2.x && p1.y < p2.y);
}

bool operator == (const Point& p1, const Point& p2) {
  return p1.x == p2.x && p1.y == p2.y;
}

int ConvexHull(Point *p,int n,Point *ch){
	sort(p,p+n);
	n=unique(p,p+n)-p;
	//for(int i=0;i<n;i++)
	//	printf("%.3lf %.3lf\n",p[i].x,p[i].y);
	int m=0;
	for(int i=0;i<n;i++){
		while(m>1&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
		ch[m++]=p[i];
	}
	int k=m;
	for(int i=n-2;i>=0;i--){
		while(m>k&&Cross(ch[m-1]-ch[m-2],p[i]-ch[m-2])<=0) m--;
			ch[m++]=p[i];
	}
	return m;
}

int T,n;
double A,B,k,b,x,y,C;
Point p[maxn],ch[maxn];
int main(){
	//freopen("fuck.txt","r",stdin);
	//freopen("fuckb.txt","w",stdout);
	scanf("%d",&T);
	for(int kase=1;kase<=T;kase++){
		double ans=INF;
		double sumx=0,sumy=0;
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%lf%lf",&x,&y);
			p[i]=Point(x,y);
			sumx+=x;sumy+=y;
		}
		int m=ConvexHull(p,n,ch);
		//for(int i=0;i<m;i++)
		//	printf("%.7lf %.7lf\n",ch[i].x,ch[i].y);
		if(m<=2) ans=0;
		else{
		for(int i=0;i<m-1;i++){
			/*k=(ch[i+1].y-ch[i].y)/(ch[i+1].x-ch[i].x);
			b=ch[i].y-k*ch[i].x;
			A=k;B=-1;C=b;*/
			A=ch[i+1].y-ch[i].y;
			B=-(ch[i+1].x-ch[i].x);
			C=-ch[i].x*A-B*ch[i].y;
			double dist=fabs(A*sumx+B*sumy+C*n)/sqrt(A*A+B*B);
			if(dist<ans) ans=dist;
		}
		}
		printf("Case #%d: %.3lf\n",kase,ans/n);
	}
	return 0;
}
