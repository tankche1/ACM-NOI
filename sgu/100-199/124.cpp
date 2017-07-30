# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10030;
struct point{
	int x1,y1,x2,y2;
}p[maxn];
int xx,yy,n;
int main(){
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&p[i].x1,&p[i].y1,&p[i].x2,&p[i].y2);
		if(p[i].x1==p[i].x2){
			if(p[i].y1>p[i].y2) swap(p[i].y1,p[i].y2);
		}
		else if(p[i].x1>p[i].x2) swap(p[i].x1,p[i].x2);
	}
	scanf("%d%d",&xx,&yy);
	
	for(int i=1;i<=n;i++){
		if(p[i].x1==p[i].x2){
			if(xx==p[i].x1&&yy<=p[i].y2&&yy>=p[i].y1){
			puts("BORDER");return 0;
			}
		}
		else{
			if(yy==p[i].y1&&xx<=p[i].x2&&xx>=p[i].x1){
				puts("BORDER");return 0;
			}
		}
	}
	
	double mx,my;mx=xx+0.5;my=yy;
	int bian=0;
	for(int i=1;i<=n;i++){
		if(p[i].y1==p[i].y2&&p[i].y1>my&&p[i].x1<=mx&&p[i].x2>=mx)
			bian++;
	}
	if(bian&1) puts("INSIDE");
	else puts("OUTSIDE");
	return 0;
}
