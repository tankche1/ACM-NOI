#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=65;
const int INF=100000000;
int pre[maxn],tmp;
double C[maxn];
double K[maxn];
int n,m;
double kk;
double dp[maxn][maxn][maxn];
double F[maxn],ans;
double cal;
	
void init(){
	for(int i=0;i<=n;i++)
		for(int j=0;j<=m;j++)
			for(int k=0;k<=n;k++)
				dp[i][j][k]=-INF;
}

void treedp(int x,int dd){//最多是dd
	
	bool haves=false;
	for(int v=2;v<=n;v++) if(pre[v]==x) {treedp(v,dd+1);haves=1;}
	for(int d=min(1,dd);d<=dd;d++){
		if(!haves){
		dp[x][0][d]=C[x]*K[d];
		dp[x][1][d]=C[x]*K[1];
		continue;
	}
	for(int i=0;i<=m;i++) F[i]=-INF;F[0]=C[x]*K[d];
	for(int v=2;v<=n;v++) if(pre[v]==x){//不连1
		for(int j=m;j>=0;j--){
			double begin=F[j];
			for(int k=j;k>=1;k--){
				F[j]=max(F[j],F[j-k]+dp[v][k][d+1]);
			}
			F[j]=max(F[j],begin+dp[v][0][d+1]);
		}
	}
	for(int j=0;j<=m;j++)
		dp[x][j][d]=max(dp[x][j][d],F[j]);
	
	for(int i=0;i<=m;i++) F[i]=-INF;F[1]=C[x]*K[1];
	for(int v=2;v<=n;v++) if(pre[v]==x){//连1
		for(int j=m;j>=0;j--){
			double begin=F[j];
			for(int k=j;k>=1;k--){
				F[j]=max(F[j],F[j-k]+dp[v][k][2]);
			}
			F[j]=max(F[j],begin+dp[v][0][2]);
	}
}
	for(int j=0;j<=m;j++){
		dp[x][j][d]=max(dp[x][j][d],F[j]);
		//printf("dp[%d][%d][%d]:%.3lf\n",x,j,d,dp[x][j][d]);
	}
}
	return;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	double tt;
	scanf("%d%d%lf",&n,&m,&kk);
	for(int i=1;i<=n;i++)
		scanf("%d",&pre[i]);
	for(int i=1;i<=n;i++)
		scanf("%lf",&C[i]);
	K[0]=1.0;//printf("%.3lf\n",kk);
	for(int i=1;i<=n;i++) K[i]=K[i-1]*kk;
	//	printf("%.3lf\n",kk);
//	for(int i=0;i<=n;i++) printf("K[%d]:%.3lf\n",i,K[i]);
	ans=-INF;
	for(int x=pre[1],len=2;x!=1;x=pre[x],len++){
		tmp=pre[x];pre[x]=1;
		init();
		//printf("x:%d\n",x);
		for(int v=2;v<=n;v++)
			if(pre[v]==1)// printf("v:%d\n",v),
				treedp(v,1);
		for(int i=0;i<=m;i++) F[i]=-INF;F[0]=C[1];
		for(int v=2;v<=n;v++) if(pre[v]==1){
			for(int i=m;i>=0;i--){
				cal=F[i];
				for(int j=i;j>=1;j--){
					F[i]=max(F[i],F[i-j]+dp[v][j][1]);
				}
				F[i]=max(F[i],cal+dp[v][0][1]);
			}
		}
		tt=-INF;
		for(int i=0;i<=m-1+(tmp==1);i++){
			tt=max(tt,F[i]);
		}
		ans=max(ans,(tt)/((double)1.0-K[len]));
		pre[x]=tmp;
	}
	printf("%.2lf\n",ans);
	return 0;
}
