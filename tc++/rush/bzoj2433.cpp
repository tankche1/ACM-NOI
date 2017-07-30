# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxr=2010;
const double eps=1e-8;
int n;
double speed;

struct Point{
	double x,y;
	Point(double x=0,double y=0):x(x),y(y) {}
	void read(){
		scanf("%lf%lf",&x,&y);
	}
	double alphato(Point p){
		return atan2(p.y-y,p.x-x);
	}
	double dist(Point p){
		return sqrt((p.x-x)*(p.x-x)+(p.y-y)*(p.y-y));
	}
};
Point st,ed;

struct Rect{
	Point low,high;
	void read(){
		low.read();high.read();
	}
}rects[maxr];

bool havePoint(Rect A,Point b){
	return A.low.x<=b.x&&A.high.x>=b.x;
}

int dcmp(double x){
	if(fabs(x)<eps) return 0;
	return x<0?-1:1;
}

bool isMiddle(double m,double l,double r){
	if(dcmp(m-l)==0||dcmp(r-m)==0||(m>=l&&m<=r)) return true;
	return false;
}

double dist[maxr][2];
Point ps[maxr][2];
int atstart,atend;
double ans;

void updatePoint(Point p,int first,double d){
	double l=-(1e100),r=1e100;
	for(int i=first;i<=n;i++){
		if(i==atend){
			if(isMiddle(p.alphato(ed),l,r)){
				ans=min(ans,d+p.dist(ed));//printf("d:%.3lf dist:%.3lf ans:%.3lf\n",d,p.dist(ed),ans);
			}
			break;
		}
		for(int k=0;k<2;k++){
			if(isMiddle(p.alphato(ps[i][k]),l,r))
				dist[i][k]=min(dist[i][k],d+p.dist(ps[i][k]));
		}
		l=max(l,p.alphato(ps[i][0]));
		r=min(r,p.alphato(ps[i][1]));
		if(dcmp(r-l)<0) break;
	}
}

void solve(){
	ans=1e100;//printf("%.3lf\n",ans);
	for(int i=1;i<=n;i++){
		if(havePoint(rects[i],st)) atstart=i;
		if(havePoint(rects[i],ed)) atend=i;
	}
	fill(dist[1],dist[n+1],1e100);
	for(int i=1;i<n;i++){
		ps[i][0]=Point(rects[i].high.x,max(rects[i].low.y,rects[i+1].low.y));
		ps[i][1]=Point(rects[i].high.x,min(rects[i].high.y,rects[i+1].high.y));
	}
	updatePoint(st,atstart,0);
	for(int i=atstart;i<atend;i++)
		updatePoint(ps[i][0],i+1,dist[i][0]),updatePoint(ps[i][1],i+1,dist[i][1]);
	//printf("%.3lf\n",ans);
	printf("%.10lf\n",ans/speed);
}

int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		rects[i].read();
	}
	st.read();ed.read();
	if(st.x>ed.x) swap(st.x,ed.x);
	scanf("%lf",&speed);
	solve();
	return 0;
}
/*2
1 1 2 2
2 0 3 4
1 1
3 0
1.0
*/
