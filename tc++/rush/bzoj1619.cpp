# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
# define Legel(a,b) a>=1&&a<=n&&b>=1&&b<=m
using namespace std;
const int maxn=705;
int h[maxn][maxn];
int n,m;
bool vis[maxn][maxn];
int ans=0;
typedef pair<int,int> pi;
queue<pi> Q;
bool go;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};
int dxx[8]={-1,-1,-1,0,0,1,1,1},dyy[8]={-1,0,1,-1,1,-1,0,1};

void floodfill(int x,int y){
	while(!Q.empty()) Q.pop();vis[x][y]=true;
	Q.push(pi(x,y));
	while(!Q.empty()){
		int x=Q.front().first,y=Q.front().second;Q.pop();
		/*for(int k=0;k<4;k++){
			int xx=x+dx[k],yy=y+dy[k];
			if(Legel(xx,yy)){
				if(h[xx][yy]==h[x][y]&&!vis[xx][yy]){
					vis[xx][yy]=true;
					Q.push(pi(xx,yy));
				}
			}
		}*/
		for(int k=0;k<8;k++){
			int xx=x+dxx[k],yy=y+dyy[k];
			if(Legel(xx,yy)){
				if(h[xx][yy]>h[x][y]){
					go=false;
				}
				else if(h[xx][yy]==h[x][y]&&!vis[xx][yy]){
					vis[xx][yy]=true;
					Q.push(pi(xx,yy));
				}
			}
		}
		
	}
	return;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			scanf("%d",&h[i][j]);
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(vis[i][j]) continue;
			go=true;
			floodfill(i,j);
			ans+=go;
			//if(go) printf("%d %d\n",i,j);
		}
		printf("%d\n",ans);
	return 0;
}
