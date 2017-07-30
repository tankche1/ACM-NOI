# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
struct POS{
	int x,y;
	POS(int x=0,int y=0):x(x),y(y) {}
};

inline int dis(POS a,POS b){
	return max(abs(a.x-b.x),abs(a.y-b.y));
}

int tank(int a){
	if(a==0) return a;
		if(a>0) return 1;return -1;
}

inline bool common(int x1,int x2,int x3,int x4,int kind){
	if(kind)
	return x3<=x2&&x4>=x1;
	else return (x3>=x1&&x3<=x2)||(x4>=x1&&x4<=x2);
}

POS w,b,wb;
int n;
int ans=INF;
int main(){
	scanf("%d",&n);
	scanf("%d%d%d%d%d%d",&b.x,&b.y,&w.x,&w.y,&wb.x,&wb.y);
	int len=dis(b,w);
	int step=len/2-1;
	if(abs(w.x-b.x)>abs(w.y-b.y)) swap(b.x,b.y),swap(w.x,w.y),swap(wb.x,wb.y);
	//int dif=abs(w.y-b.y)-abs(w.x-b.x);
	int _m=max(w.y,b.y);
	//printf("%d %d %d %d %d %d\n",b.x,b.y,w.x,w.y,wb.x,wb.y);
	bool ok=false;
	for(int y=min(w.y,b.y);y<=_m;y++){
		for(int ii=1;ii<=1;ii++){
		int dist=abs(y-w.y);
		if(dist==0||dist>step) continue;
		if(dist<abs(y-wb.y)) continue;
		int x1=wb.x-dist,x2=wb.x+dist;bool kind=abs(y-wb.y)==dist;
		int d=abs(y-b.y);
		int xw1=max(w.x-dist,b.x-d);int xw2=min(w.x+dist,b.x+d);
		if(xw1>xw2) swap(xw1,xw2);
		xw1=max(1,xw1);xw2=min(xw2,n);
		if(common(xw1,xw2,x1,x2,kind)) {//printf("wwy:%d x1:%d x2:%d %d %d\n",y,x1,x2,xw1,xw2);
			ok=true;ans=min(ans,dist);}
	}
		int dist=abs(y-b.y);
		if(dist==0||dist>step) continue;
		if(dist<abs(y-wb.y)) continue;
		int x1=wb.x-dist,x2=wb.x+dist;bool kind=abs(y-wb.y)==dist;
		int d=abs(y-w.y);
		int xw1=max(b.x-dist,w.x-d);int xw2=min(b.x+dist,b.x+d);
		//if(y==8) printf("%d %d\n",xw1,xw2);
		if(xw1>xw2) swap(xw1,xw2);
		xw1=max(1,xw1);xw2=min(xw2,n);
		if(common(xw1,xw2,x1,x2,kind)) {//printf("bby:%d x1:%d x2:%d %d %d\n",y,x1,x2,xw1,xw2);
			ok=true;ans=min(ans,dist);}
	}
	if(ok){puts("YES");printf("%d\n",ans);}
	else {puts("NO");printf("%d\n",len-1);}
	return 0;
}
