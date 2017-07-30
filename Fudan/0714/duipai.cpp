#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

int sgn(double a){if(a<0)return -1;if(a>0)return 1;return 0;}

struct point{double x,y;int index;point(double a=0,double b=0){x=a;y=b;}};
double operator ^ (const point& a,const point& b)
{return a.x*b.y-a.y*b.x;}
point operator - (const point& a,const point& b)
{return point(a.x-b.x,a.y-b.y);}
point operator + (const point& a,const point& b)
{return point(a.x+b.x,a.y+b.y);}
bool operator < (const point& a,const point& b)
{if(a.y==b.y) return a.x<b.x;return a.y>b.y;}

int turn(const point& a,const point& b,const point& c)//1:left -1:right
{return sgn((b-a)^(c-b));}

int n;
point p[100001];
int stk[100010],top;
void convex_hull()
{
	std::sort(p+1,p+n+1);
	stk[1]=1;stk[2]=2;top=2;
	for(int i=3;i<=n;i++)
	{
		while(top>=2&&turn(p[stk[top-1]],p[stk[top]],p[i])>=0)top--;
		stk[++top]=i;
	}
	int tmp=top;
	for(int i=n-1;i>=1;i--)
	{
		while(top>tmp&&turn(p[stk[top-1]],p[stk[top]],p[i])>=0)top--;
		stk[++top]=i;
	}
	top--;
}

void clear(){top=0;}

int main()
{
	//freopen("G.out","w",stdout);
	int test,num;scanf("%d",&test);
	while(test--)
	{
		clear();
		scanf("%d%d",&num,&n);
		for(int i=1;i<=n;i++)
			{scanf("%lf%lf",&p[i].x,&p[i].y);p[i].index=i;}
		convex_hull();
		printf("%d %d\n",num,top);
		for(int i=1;i<=top;i++)
			printf("%d %d\n",(int)p[stk[i]].x,(int)p[stk[i]].y);
	}
}
