# include<stdio.h>
# include<string.h>
# include<math.h>
# include<vector>
# include<algorithm>
using namespace std;
const double eps=5*(1e-13);
int dcmp(double x){
	if(fabs(x)<eps) return 0;
		return x<0?-1:1;
}

const double PI=acos(-1);
const double TWO_PI=2*PI;

struct Point{
	double x,y;
	Point(double x=0,double y=0) :x(x),y(y) {}
};

typedef Point Vector;
Vector operator + (const Vector &A,const Vector &B) {return Vector(A.x+B.x,A.y+B.y);}
Vector operator - (const Vector &A,const Vector &B) {return Vector(A.x-B.x,A.y-B.y);}
Vector operator * (const Vector &A,const double &B) {return Vector(A.x*B,A.y*B);}
Vector operator / (const Vector &A,const double &B) {return Vector(A.x/B,A.y/B);}
double Dot(const Vector &A,const Vector &B) {return A.x*B.x+A.y*B.y;}
double Length(const Vector &A) {return sqrt(Dot(A,A));}
double angle(Vector v){return atan2(v.y,v.x);}

int getCircleCircleIntersection(Point C1,double r1,Point C2,double r2,vector<double> &ans){
	double dist=Length(C2-C1);
	if(dcmp(dist-r1-r2)>0) return 0;
	if(dcmp(fabs(r1-r2)-dist)>0) return 0;
	if(dcmp(dist)==0){
		if(dcmp(r1-r2)==0) return -1;
		return 0;
	}
	double da=angle(C2-C1);
	double ang=acos((r1*r1+dist*dist-r2*r2)/(2*dist*r1));
	ans.push_back(da+ang);
	ans.push_back(da-ang);
	return 2;
}


const int maxn=110;
bool vis[maxn];
double radius[maxn];
Point center[maxn];
int n;

int topmost(Point P){
	for(int i=n-1;i>=0;i--)
		if(Length(P-center[i])<radius[i]) return i;
	return -1;
}

int main(){
	double x,y,r;
	while(scanf("%d",&n)!=EOF){
		if(!n) break;
		for(int i=0;i<n;i++){
			scanf("%lf%lf%lf",&x,&y,&r);
			center[i]=Point(x,y);radius[i]=r;
		}
		memset(vis,false,sizeof(vis));
		vector<double> rad;
		for(int i=0;i<n;i++){
			rad.push_back(-PI);
			rad.push_back(PI);
			for(int j=0;j<n;j++){
				getCircleCircleIntersection(center[i],radius[i],center[j],radius[j],rad);
			}
			sort(rad.begin(),rad.end());
			for(int j=0;j<rad.size()-1;j++){
				double mid=(rad[j]+rad[j+1])/2.0;
				for(int size=-1;size<=1;size+=2){
					double r2=radius[i]+size*eps;
					int t=topmost(Point(center[i].x+cos(mid)*r2,center[i].y+sin(mid)*r2));
					if(t>=0) vis[t]=true;
				}
			}
		}
		int ans=0;
		for(int i=0;i<n;i++) if(vis[i]) ans++;
		printf("%d\n",ans);
	}
	return 0;
}
