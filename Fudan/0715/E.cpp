# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
# define sqr(a) a*a
using namespace std;
typedef long long LL;
int n;
struct point{
	int x,y;
	point(int x=0,int y=0):x(x),y(y) {}
};
point p[1010];
int main(){
	int Tcase,t=0;
	double ans=1000000000;
	scanf("%d",&Tcase);
	while(Tcase--){
		printf("Case %d: ",++t);
		ans=1000000000;
		scanf("%d",&n);
		double len;
		for(int i=1;i<=n;i++)
			scanf("%d %d",&p[i].x,&p[i].y);
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				if(((double)sqrt((double)sqr((double)(p[j].x-p[i].x))+(double)sqr((double)(p[j].y-p[i].y))))>=ans) continue;
				for(int k=j+1;k<=n;k++){
					if((p[k].y-p[j].y)*(p[k].x-p[i].x)==(p[k].y-p[i].y)*(p[k].x-p[j].x)) continue;
					//puts("hei");
					len=0;
					len+=(double)sqrt((double)sqr((double)(p[k].x-p[i].x))+(double)sqr((double)(p[k].y-p[i].y)));
					len+=(double)sqrt((double)sqr((double)(p[k].x-p[j].x))+(double)sqr((double)(p[k].y-p[j].y)));
					len+=(double)sqrt((double)sqr((double)(p[j].x-p[i].x))+(double)sqr((double)(p[j].y-p[i].y)));
					ans=min(ans,len);
				}
			}
		if(ans==1000000000) puts("No Solution");
		else printf("%.3lf\n",ans);
	}
	return 0;
}
