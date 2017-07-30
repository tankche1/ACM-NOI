#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef pair<int,int> pi;
const double eps=1e-8;
const int maxn=110;
const int INF=maxn*maxn*100;
double L;
int R,C;
char s[maxn][maxn];
int stx,sty,endx,endy;
pi q[maxn*maxn];
int head,tail;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
double cost[4];
double dist[maxn][maxn];

double BFS(double v){
	cost[0]=cost[1]=v;cost[2]=cost[3]=1;
	for(int i=1;i<=R;i++)
		for(int j=1;j<=C;j++)
			dist[i][j]=INF;
	dist[stx][sty]=0;
	head=0;tail=-1;
	q[++tail]=pi(stx,sty);
	while(head<=tail){
		int x=q[head].first,y=q[head].second;head++;
		for(int k=0;k<4;k++){
			int nx=x+dx[k],ny=y+dy[k];
			if(nx>=1&&nx<=R&&ny>=1&&ny<=C){
				if(s[nx][ny]=='#') continue;
				if(dist[nx][ny]>dist[x][y]+cost[k]){
					dist[nx][ny]=dist[x][y]+cost[k];
					q[++tail]=pi(nx,ny);
				}
			}
		}
	}
	//printf("v:%.3lf dist:%.3lf\n",v,dist[endx][endy]);
	return dist[endx][endy];
}

int main(){
	int tcase;scanf("%d\n",&tcase);
	while(tcase--){
		scanf("%lf%d%d\n",&L,&R,&C);
		for(int i=1;i<=R;i++)
			gets(s[i]+1);//,printf("i:%d ",i),puts(s[i]+1);
		for(int i=1;i<=R;i++)
			for(int j=1;j<=C;j++)
				if(s[i][j]=='S') stx=i,sty=j;
				else if(s[i][j]=='E') endx=i,endy=j;
		double l,r,m;
		l=0,r=10;
		while(r-l>eps){
			m=(r+l)/2.0;
			if(BFS(m)>=L) r=m;
			else l=m;
		}
		printf("%.5lf\n",r);
	}
	return 0;
}
/*
2
2.5 4 5
#####
#S  #
#  E#
#####
21 13 12
############
#S##     #E#
# ##  #  # #
#   # #  # #
### # #  # #
#   # #  # #
#  ## #  # #
##  # #  # #
### # #  # #
##  # #  # #
#  ## #    #
#     #    #
############
*/
