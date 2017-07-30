# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
LL a,b,c,d,x,y;
LL x1,x2,y1,y2;

inline void gcd(LL a,LL b,LL &x,LL &y,LL &d){
	if(a==0){
		x=0,y=b>0?1:-1,d=abs(b);return;
	}
	gcd(b%a,a,x,y,d);
	swap(x,y);
	x-=b/a*y;
}

/*inline LL up(double a){
	if(LL(a)==a) return a;return LL(a)+1;
}

inline LL down(double a){
	if(LL(a)==a) return a;return LL(a)+1;
}*/
int main(){
	scanf("%I64d%I64d%I64d",&a,&b,&c);
	scanf("%I64d%I64d%I64d%I64d",&x1,&x2,&y1,&y2);
	int xx,yy;
	if(a<0)
		xx=x1,yy=x2,x1=-yy,x2=-xx,a=-a;
	if(b<0) 
		xx=y1,yy=y2,y1=-yy,y2=-xx,b=-b;
	if(a==0&&b==0)
		printf("%I64d\n",c==0?(x2-x1+1)*(y2-y1+1):0);
	else if(a==0)
		printf("%I64d\n",((-c)%b==0)?(((-c)/b>=y1&&(-c)/b<=y2)?(x2-x1+1):0):0);
	else if(b==0)
		printf("%I64d\n",((-c)%a==0)?(((-c)/a>=x1&&(-c)/a<=x2)?(y2-y1+1):0):0);
	else{
	gcd(a,b,x,y,d);//printf("a:%d b:%d x:%d y:%d d:%d\n",a,b,x,y,d);
	if(c%d!=0) printf("0\n");
	else{
		LL _maxx,_maxy,_minx,_miny;
		x*=(-c)/d;y*=(-c)/d;
		/*double minx=((x1-x)*d)/(b);
		double maxx=((x2-x)*d)/(b);
		double miny=((y-y2)*d)/(a);
		double maxy=((y-y1)*d)/(a);*/
		if(((x1-x)*d)%b==0) _minx=((x1-x)*d)/(b);
		else _minx=((x1-x)*d)*(b)<0?((x1-x)*d)/(b):((x1-x)*d)/(b)+1;
		if(((y-y2)*d)%(a)==0) _miny=((y-y2)*d)/(a);
		else _miny=((y-y2)*d)*(a)<0?((y-y2)*d)/(a):((y-y2)*d)/(a)+1;
		if(((x2-x)*d)%(b)==0) _maxx=((x2-x)*d)/(b);
		else _maxx=((x2-x)*d)*(b)<0?((x2-x)*d)/(b)-1:((x2-x)*d)/(b);
		if(((y-y1)*d)%(a)==0) _maxy=((y-y1)*d)/(a);
		else _maxy=((y-y1)*d)*(a)<0?((y-y1)*d)/(a)-1:((y-y1)*d)/(a);
		/*int minx,maxx,miny,maxy;
		if(_minx>(int)_minx) minx=int(_minx)+1;else minx=int(_minx);
		if(_miny>(int)_miny) _miny=int(_miny)+1;else miny=int(_miny);
		maxx=(int)_maxx;maxy=(int)_maxy;
		if(minx>maxx||miny>maxy) puts("0");
		else{*/
			LL _min=max(_minx,_miny),_max=min(_maxx,_maxy);
			printf("%I64d\n",(_max-_min+1>=0)?(_max-_min+1):0);
	}
}
	return 0;
}
