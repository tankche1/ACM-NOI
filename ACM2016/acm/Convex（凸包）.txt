# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int sgn(double a) {if(a<0) return -1;if(a>0) return 1;return 0;}

struct point{
	double x,y;
	int index;
	point(double x=0,double y=0):x(x),y(y) {}
};

double operator ^(const point &a,const point &b){return a.x*b.y-a.y*b.x;}
point operator - (const point& a,const point& b) {return point(a.x-b.x,a.y-b.y);}
point operator + (const point& a,const point& b) {return point(a.x+b.x,a.y+b.y);}
bool operator < (const point& a,const point& b){if(a.y==b.y) return a.x<b.x;return a.y>b.y;}

int turn(const point &a,const point &b,const point &c){//1:left -1:right
	return sgn((b-a)^(c-b));
}


int convex_hull(point *p,int n,int *stk){//p是点集 n是点数 stk是凸包上的点 函数返回凸包上的点数
	sort(p+1,p+n+1);
	stk[1]=1;stk[2]=2;
	int top=2;
	for(int i=3;i<=n;i++){
		while(top>=2&&turn(p[stk[top-1]],p[stk[top]],p[i])>=0) top--;
		stk[++top]=i;
	}
	int tmp=top;
	for(int i=n-1;i>=1;i--){
		while(top>tmp&&turn(p[stk[top-1]],p[stk[top]],p[i])>=0) top--;
		stk[++top]=i;
	}
	top--;
	return top;
}

point p[maxn];
int n,stk[maxn],num;
int main()
{
	//freopen("G.out","w",stdout);
	int Tcase,top;
	scanf("%d",&Tcase);
	while(Tcase--){
		scanf("%d %d",&num,&n);
		for(int i=1;i<=n;i++){
			scanf("%lf%lf",&p[i].x,&p[i].y);p[i].index=i;
		}
		top=convex_hull(p,n,stk);
		printf("%d",num);
		printf(" %d\n",top);
		for(int i=1;i<=top;i++){
			printf("%d %d\n",(int)p[stk[i]].x,(int)p[stk[i]].y);
		}
	}
	return 0;
}