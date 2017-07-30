#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1000010;
const int INF=~0U>>1;
int x[maxn],y[maxn],w[maxn];
int n;
int minx=INF,maxx=-INF,miny=INF,maxy=-INF;
int main(){
	scanf("%d",&n);
	LL ans=INF;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d",&x[i],&y[i],&w[i]);
		if(x[i]>y[i]) {minx=min(minx,y[i]),maxx=max(maxx,y[i]),miny=min(miny,x[i]),maxy=max(maxy,x[i]);}
		else if(x[i]<y[i]) {minx=min(minx,x[i]),maxx=max(maxx,x[i]),miny=min(miny,y[i]),maxy=max(maxy,y[i]);}
		else minx=min(minx,y[i]),maxx=max(maxx,y[i]),miny=min(miny,x[i]),maxy=max(maxy,x[i]);
	}
	//printf("minx:%d miny:%d maxx:%d maxy:%d\n",minx,miny,maxx,maxy);
	LL length=(maxx-minx)*2;length+=(maxy-miny)*2;
	int t1,t2;
	for(int i=0;i<2;i++){
		if(i) swap(minx,miny);
		for(int j=0;j<2;j++){
			if(j) swap(maxx,maxy);
			LL num=0;
			if(maxx>=minx&&maxy>=miny){
				bool ok=true;
				for(int i=1;i<=n;i++){
					if(x[i]>=minx&&x[i]<=maxx&&y[i]>=miny&&y[i]<=maxy) continue;
					if(y[i]>=minx&&y[i]<=maxx&&x[i]>=miny&&x[i]<=maxy) num+=w[i];
					else {ok=false;break;}
				}
				if(ok&&num<ans) ans=num,t1=i,t2=j;
			}
			if(j) swap(maxx,maxy);
		}
		if(i) swap(minx,miny);
	}
	printf("%lld %lld\n",length,ans);
	if(t1) swap(minx,miny);
	if(t2) swap(maxx,maxy);
	for(int i=1;i<=n;i++){
		if(x[i]>=minx&&x[i]<=maxx&&y[i]>=miny&&y[i]<=maxy) printf("0");
		else if(y[i]>=minx&&y[i]<=maxx&&x[i]>=miny&&x[i]<=maxy) printf("1");
	}puts("");
	return 0;
}
