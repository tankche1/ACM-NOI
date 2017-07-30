#include<bits/stdc++.h>
#define ll long long
using namespace std;
struct point {
	point(double tx,double ty) {x=tx;y=ty;}
	point(){}
	double x,y;
	void operator *=(double k) {
		x*=k;
		y*=k;
	}
	void operator /=(double k) {
		x/=k;
		y/=k;
	}
}s,mv,vl,vr,a[1005];

double theta,r;
bool exi[1005];
int n,m;
const double pi=3.14159265358979323846;
const double eps=1e-8;

point operator+(const point& A,const point& B){
	point tmp=point(A.x+B.x,A.y+B.y);
	return tmp;
}
point operator-(const point& A,const point& B) {
	point tmp=point(A.x-B.x,A.y-B.y);
	return tmp;
}

double mo(const point& A) {
	return sqrt(A.x*A.x + A.y*A.y);
}

double dis(const point& A,const point &B){
	return sqrt((A.x-B.x)*(A.x-B.x) + (A.y-B.y) * (A.y-B.y));
}

int dcmp(double tmp) {
	if(tmp>eps)return 1;
	if(tmp<-eps)return -1;
	return 0;
}

double cross(const point& v1,const point& v2) {
	return v1.x*v2.y-v2.x*v1.y;
}

bool inangle(const point& p1,const point& pl,const point& pr,const point& toc) {
	if(dis(p1,toc)<eps)return true;
	point vecl=pl-p1,vecr=pr-p1,vecc=toc-p1;
	if(dcmp(cross(vecr,vecl))<0)swap(vecl,vecr);
	if(dcmp(cross(vecl,vecc))<=0 && dcmp(cross(vecc,vecr))<=0)return true;
	return false;
}



void checksec() {
	point pl=vl+s,pr=vr+s;
	for(int i=1;i<=n;i++) {
		if(exi[i]==true && dis(s,a[i])<=r+eps && inangle(s,pl,pr,a[i]))
			exi[i]=false;
	}
}

void checkrec(const point& p1,const point& pl,const point& pr) {
	point p4=pr+pl-p1;
	for(int i=1;i<=n;i++)
		if(exi[i]==true && inangle(p1,pl,pr,a[i]) && inangle(p4,pr,pl,a[i]))
			exi[i]=false;
}
point rot(const point& A,double alpha) {
	point tmp;
	alpha=alpha*pi/180.0;
	tmp.x=cos(alpha) * A.x + sin(alpha) * A.y;
	tmp.y=-sin(alpha) * A.x + cos(alpha) * A.y;
	return tmp;
}

void checkwhilemoving(double t) {
	point mvt=mv,tmpvl=vl,tmpvr=vr;
	mvt*=t;mvt=mvt+s;

	point verti1=rot(mv,90),verti2=rot(mv,-90);
	verti1*=r;verti2*=r;tmpvl*=r;tmpvr*=r;

	verti1=verti1+s;verti2=verti2+s;
	tmpvl=tmpvl+s;tmpvr=tmpvr+s;

	checkrec(s,mvt,tmpvr);
	checkrec(s,mvt,tmpvl);
	if(inangle(s,tmpvl,tmpvr,verti1))
		checkrec(s,mvt,verti1);
	if(inangle(s,tmpvl,tmpvr,verti2))
		checkrec(s,mvt,verti2);

	s=mvt;
}

int main() {

	int tc;
	scanf("%d",&tc);
	for(int tt=1;tt<=tc;tt++) {
		memset(exi,1,sizeof(exi));
		point vi;
		cin>>n>>m>>theta>>r;
		cin>>s.x>>s.y>>vi.x>>vi.y>>mv.x>>mv.y;
		vi/=mo(vi);mv/=mo(mv);
		vr=rot(vi,theta/2.0);
		vl=rot(vi,-theta/2.0);
		int tx,ty;
		for(int i=1;i<=n;i++) {
			scanf("%d%d",&tx,&ty);
			a[i].x=tx;a[i].y=ty;
		}

		checksec();
		int t=0,tmpt,u,alpha;
		for(int i=1;i<=m;i++) {
			scanf("%d%d%d",&u,&tmpt,&alpha);
			if(u==1) {
				checkwhilemoving(tmpt-t);
				checksec();
				vl=rot(vl,alpha);
				vr=rot(vr,alpha);
				checksec();
			}
			else{
				checkwhilemoving(tmpt-t);
				checksec();
				mv=rot(mv,alpha);
				checksec();
			}
			t=tmpt;
		}
		printf("Case #%d: ",tt);
		for(int i=1;i<=n;i++)
			if(exi[i])printf("1");
			else printf("0");
		printf("\n");
	}
}
