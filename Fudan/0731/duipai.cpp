#include <set>
#include <map>
#include <queue>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <algorithm>
using namespace std;
#define LL long long
int N,last,rr;
double A,B,C,ans;
int r[2],l[2],height[200010];
double k[2],b[2];
class lin{
	  public:double k,b;int t;
	  bool operator <(const lin &X)const{return t<X.t;}
}t;
class linrec{public:lin a[200010];}line[2];
class rec{public:int x,z;}P[100010];
int setline(int step){
	int zmax=0;
	scanf("%d",&N);
	for (int i=1;i<=N;i++)scanf("%d%d",&P[i].x,&P[i].z),height[++last]=P[i].z,zmax=max(zmax,P[i].z);
	r[step]=0;
	for (int i=1;i<N;i++)
	if (P[i+1].z!=P[i].z){
		int x;
		t.k=double(-P[i+1].x+P[i].x)/(P[i+1].z-P[i].z);
		t.b=-P[i].x-P[i].z*t.k;
		if (P[i+1].z<P[i].z)t.k=-t.k,t.b=-t.b;
		t.t=min(P[i+1].z,P[i].z);
		x=++r[step];
		line[step].a[x]=t;
		t.k=-t.k;
		t.b=-t.b;
		t.t=max(P[i+1].z,P[i].z);
		x=++r[step];
		line[step].a[x]=t;
	}
	sort(line[step].a+1,line[step].a+r[step]+1);
	return zmax;
}
double calc(int z){
	return A*z*z*z+B*z*z+C*z;
}
int main(){
	//freopen("lonely.in","r",stdin);
	//freopen("lonely.out","w",stdout);
	last=0;
	if (setline(0)!=setline(1)){
		printf("Invalid plan\n");
		return 0;
	}
	sort(height+1,height+last+1);
	rr=1;
	for (int i=2;i<=last;i++)
		if (height[i]!=height[rr])height[++rr]=height[i];
	l[0]=l[1]=1;
	for (int i=1;i<rr;i++){
		for (int step=0;step<2;step++)
			while(l[step]<=r[step]&&line[step].a[l[step]].t==height[i]){
				k[step]+=line[step].a[l[step]].k;
				b[step]+=line[step].a[l[step]].b;
				l[step]++;
			}
		A=k[0]*k[1]/3;
		B=(k[1]*b[0]+k[0]*b[1])/2;
		C=b[0]*b[1];
		ans=ans+calc(height[i+1])-calc(height[i]);
		printf("%.2lf\n",ans);
	}
	printf("%lf\n",ans);
}
