# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=110;
const int INF=(~0U>>1)-100;

int sgn(double a){if(a<0)return -1;if(a>0)return 1;return 0;}

struct point{int x,y;int index;point(int a=0,int b=0){x=a;y=b;}};
point p[maxn];
int ansy[101100],ansa[101100],ansb[101100],cnt=0;

int main(){
	//freopen("G.out","w",stdout);
	int tcase;
	int num,n,pos;
	int miny=INF,maxy=-INF;double minx,maxx;
	scanf("%d",&tcase);
	while(tcase--){
		cnt=0; miny=INF,maxy=-INF;
		scanf("%d%d",&num,&n);
		for(int i=1;i<=n;i++){
			scanf("%d %d",&p[i].x,&p[i].y);
			if(p[i].y<miny) {miny=p[i].y,pos=i;}
		}
		maxy=(int)p[1].y;
		p[n+1].x=p[1].x;p[n+1].y=p[1].y;
		int L,R;
		for(int y=maxy-1;y>miny;y--){
			minx=INF;maxx=-INF;
			for(int i=1;i<pos;i++){
				if(p[i].y==y) {maxx=p[i].x-0.1;break;}
				if(p[i].y>y&&p[i+1].y<y){
					maxx=((double)(p[i].x)+((double)(p[i+1].x-p[i].x)/((double)(p[i+1].y-p[i].y)*1.0))*(y-p[i].y));
					break;
				}
			}
			for(R=(int)(maxx-3);R<maxx;R++);R--;
			for(int i=pos;i<n+1;i++){
				if(p[i].y==y) {minx=p[i].x+0.1;break;}
				if(p[i].y<y&&p[i+1].y>y){
					minx=(p[i].x)+((double)(p[i+1].x-p[i].x)/((double)(p[i+1].y-p[i].y)*1.0))*(y-p[i].y);
					break;
				}
			}
			//printf("y:%d minx:%.3lf maxx:%.3lf L:%d R:%d\n",y,minx,maxx,L,R);
			for(L=(int)(minx+3);L>minx;L--);L++;
		//	printf("y:%d minx:%.3lf maxx:%.3lf L:%d R:%d\n",y,minx,maxx,L,R);
			if(L<=R){
				cnt++;ansy[cnt]=y;ansa[cnt]=L;ansb[cnt]=R;
			}
		}
	//	printf("maxy:%d miny:%d\n",maxy,miny);
		printf("%d %d\n",num,cnt);
		for(int i=1;i<=cnt;i++)
			printf("%d %d %d\n",ansy[i],ansa[i],ansb[i]);
	}
	return 0;
}
