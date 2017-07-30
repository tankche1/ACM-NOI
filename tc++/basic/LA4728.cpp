# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=400010;

struct Point{
	double x,y;
	Point(double x=0,double y=0) :x(x),y(y) {}
};

typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
double Dot(const Vector &A,const Vector &B) {return A.x*B.x+A.y*B.y;}
double Cross(const Vector &A,const Vector &B) {return A.x*B.y-A.y*B.x;}
double Dist2(Point A,Point B) { return(A.x-B.x)*(A.x-B.x)+(A.y-B.y)*(A.y-B.y);}

bool operator < (const Vector &A,const Vector &B) {return A.x<B.x||(A.x==B.x&&A.y<B.y);}

bool operator == (const Vector &A,const Vector &B) {return A.x==B.x&&A.y==B.y;}

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
	if(m>1) m--;
	return m;
}

double diameter2(Point *p,int n){
	double ans=0;
		//printf("n:%d\n",n);
	//for(int i=0;i<n;i++) printf("%d %d\n",(int)p[i].x,(int)p[i].y);
	if(n==1) return 0;
	if(n==2) return Dist2(p[1],p[0]);
	p[n++]=p[0];
	for(int u=0,v=1;u<n-1;u++){
		for(;;){
			double diff=(Cross(p[u+1]-p[u],p[v+1]-p[v]));
			if(diff<=0){
				//printf("u:%d v:%d\n",u,v);
				ans=max(ans,Dist2(p[v],p[u]));
				if(diff==0) ans=max(ans,Dist2(p[v+1],p[u]));
				break;
			}
			v=(v+1)%(n-1);
		}
	}
	return ans;
}

int T,n;
Point p[maxn],ch[maxn];
int x,y,w;
int main(){
	scanf("%d",&T);
	while(T--){
		scanf("%d",&n);
		for(int i=0;i<n;i++){
			scanf("%d%d%d",&x,&y,&w);
			int num=4*i;
			p[num]=Point(x,y);
			p[num+1]=Point(x+w,y);
			p[num+2]=Point(x,y+w);
			p[num+3]=Point(x+w,y+w);
		}
		int m=ConvexHull(p,n*4,ch);
		printf("%d\n",(int)(diameter2(ch,m)));
	}
	return 0;
}
