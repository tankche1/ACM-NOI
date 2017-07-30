# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=2010;
int n;

struct point{
	int x,y;
};
point P[maxn];
int x[maxn],x_cnt,y[maxn],y_cnt;
int dp[maxn][12];
int Step=11;
int Two[12],log[maxn];

void Square_Table(){
	memset(dp,0,sizeof(dp));
	int i=0;Two[0]=1;
	for(int i=1;i<=Step;i++){
		Two[i]=Two[i-1]<<1;
		for(int j=Two[i-1];j<Two[i];j++) log[j]=i-1;
	}
	for(int i=1;i<=n;i++)
		dp[P[i].y][0]=max(dp[P[i].y][0],P[i].x);//,printf("dp[%d][%d]:%d\n",P[i].y,0,dp[P[i].y][0]);
	for(int i=1;i<=Step;i++){
		for(int j=1;j<=y_cnt;j++){
			dp[j][i]=max(dp[j][i-1],dp[min(y_cnt,j+Two[i-1])][i-1]);
			//printf("dp[%d][%d]:%d %d \n",j,i,dp[j][i],min(y_cnt,j+Two[i-1]));
		}
	}
}

int getmax(int l,int r){
	return max(dp[l][log[r-l+1]],dp[r-log[r-l+1]+1][log[r-l+1]]);
}

int main(){
	freopen("arrow.in","r",stdin);
	freopen("arrow.out","w",stdout);
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		x_cnt=y_cnt=1;
		for(int i=1;i<=n;i++){
			scanf("%d%d",&P[i].x,&P[i].y);
			x[x_cnt++]=P[i].x,y[y_cnt++]=P[i].y;
		}
		sort(x+1,x+x_cnt);sort(y+1,y+y_cnt);
		x_cnt=unique(x+1,x+x_cnt)-(x+1);//printf("x_cnt:%d\n",x_cnt);
		y_cnt=unique(y+1,y+y_cnt)-(y+1);
		//for(int i=1;i<=x_cnt;i++) printf("x[%d]:%d\n",i,x[i]);
		
		for(int i=1;i<=n;i++)
			P[i].x=lower_bound(x+1,x+x_cnt+1,P[i].x)-(x),P[i].y=lower_bound(y+1,y+y_cnt+1,P[i].y)-(y);//printf("P[%d].x:%d y:%d\n",i,P[i].x,P[i].y);
		Square_Table();
		
		int ans=0;
		//for(int i=1;i<=x_cnt;i++) printf("x[%d]:%d\n",i,x[i]);
		for(int i=1;i<=n;i++){
			for(int j=1;j<=n;j++){
				if(P[i].x==P[j].x&&P[i].y<P[j].y){
				//	printf("%d %d x:%d\n",i,j,P[i].x);
					int len=getmax(P[i].y,P[j].y);//printf("%d\n",len);
					//printf("x[len]:%d x:%d y:%d y:%d\n",x[len],x[P[i].x],y[P[j].y],y[P[i].y]);
					if(x[len]-x[P[i].x]>y[P[j].y]-y[P[i].y])
						ans=max(ans,x[len]-x[P[i].x]+y[P[j].y]-y[P[i].y]);
				}
			}
		}
		printf("%d\n",ans);
	}
	return 0;
}
/*
1
5
2 2
2 5
6 4
2 4
2 10
*/

