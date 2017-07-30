#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=1010;
int h[maxn][maxn];
int w[maxn][maxn];
int m,n;


inline int pos(int x,int y) {return (x-1)*n+y;}

struct Lian{
	int first[maxn],next[maxn*maxn];
	void init(){
		memset(first,-1,sizeof(first));
	}
	void insert(int a,int b){
		next[b]=first[a];
		first[a]=b;
	}
}h1,h2;

int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

int main(){
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			w[i][j]=INF;
	h1.init();h2.init();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			scanf("%d",&h[i][j]);
			//printf("i:%d j:%d m:%d n:%d \n",i,j,m,n);
			if(h[i][j]>0){
				h1.insert(h[i][j],pos(i,j));
			}
			else h[i][j]=-h[i][j];
		}
	}
	/*for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++){
			if(h[i][j]<10) printf("0");
				printf("%d ",h[i][j]);
	}puts("");
}*/
	int ans=0;
	for(int i=1;i<=1000;i++){
		while(1){
			if(h2.first[i]!=-1){
				int x=(h2.first[i]-1)/n+1,y=(h2.first[i]-1)%n+1;
				h2.first[i]=h2.next[pos(x,y)];
				//printf("h2 x:%d y:%d w:%d\n",x,y,w[x][y]);
				for(int d=0;d<4;d++){
					int nx=x+dx[d],ny=y+dy[d];
					if(nx>=1&&nx<=m&&ny>=1&&ny<=n&&w[nx][ny]==INF){
						
							w[nx][ny]=max(h[nx][ny],w[x][y]);//if(x==5&&y==9)printf("nx:%d ny:%d w:%d\n",nx,ny,w[nx][ny]);
							h2.insert(w[nx][ny],pos(nx,ny));
					}
				}
			}
			else if(h1.first[i]!=-1){
				int x=(h1.first[i]-1)/n+1,y=(h1.first[i]-1)%n+1;
				h1.first[i]=h1.next[pos(x,y)];
				if(w[x][y]!=INF) continue;
				ans++;//printf("x:%d y:%d\n",x,y);
				w[x][y]=h[x][y];
				for(int d=0;d<4;d++){
					int nx=x+dx[d],ny=y+dy[d];
					if(nx>=1&&nx<=m&&ny>=1&&ny<=n&&w[nx][ny]==INF){
						
							w[nx][ny]=max(h[nx][ny],w[x][y]);//printf("nx:%d ny:%d w:%d\n",nx,ny,w[nx][ny]);
							h2.insert(w[nx][ny],pos(nx,ny));
					}
				}
			}
			else break;
		}
	}
	printf("%d\n",ans);
	return 0;
}
