#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
const int INF=~0U>>2;
double xx[22],yy[22],rad[22];
double l,r;
const double pi=acos(-1);
int n;
double dp[1<<20];
int main(){
	scanf("%d%lf%lf",&n,&l,&r);
	int maxs=1<<n;
	for(int i=1;i<=n;i++){
		scanf("%lf%lf%lf",&xx[i],&yy[i],&rad[i]);rad[i]=rad[i]/180.0*pi;//printf("%.3lf %.3lf %.3lf\n",xx[i],yy[i],rad[i]);
		if(yy[i]<0) yy[i]=-yy[i];
	}
	double ans=-INF;
	dp[0]=l;
	for(int i=1;i<maxs;i++) dp[i]=-999999.0;
	for(int i=0;i<maxs;i++){
		for(int j=1;j<=n;j++){
			if((i&(1<<(j-1)))==0){
				int next=i|(1<<(j-1));
				double now=dp[i];
				double x=now-xx[j],y=-yy[j];
				double newx=x*cos(rad[j])-y*sin(rad[j]),newy=x*sin(rad[j])+y*cos(rad[j]);
					//printf("a:%.6lf b:%.6lf\n",newx,newy);
				//printf("x:%.3lf y:%.3lf newx:%.3lf newy:%.3lf xx:%.3lf yy:%.3lf \n",x,y,newx,newy,xx,yy);
				if(newy>=0){//puts("fuck");
					dp[next]=r;continue;
				}
				newx=newx*(y/newy)+xx[j];
				//newx=y*newx/newy+xx[j];
				//printf("newx:%.6lf\n",newx);
				//printf("next:%d\n",next);
				dp[next]=max(dp[next],newx);
			}
		}
		//if(dp[i]>ans) ans=dp[i],printf("dp[%d]:%.9lf\n",i,dp[i]);
		ans=max(ans,dp[i]);
	}
	//printf("%.9lf\n",ans);
	//printf("%.9lf\n",min(dp[maxs-1],r)-l);
	printf("%.9lf\n",min(ans,r)-l);
	return 0;
}
