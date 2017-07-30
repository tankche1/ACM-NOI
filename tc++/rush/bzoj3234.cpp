#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=210;
int sum[maxn][maxn][maxn],n;
bool vis[maxn][maxn][maxn];
int ans,mx,my,mz;
struct Box{
	int x,y,z;
	Box(){}
	Box(int x,int y,int z):x(x),y(y),z(z) {}
};
queue<Box> q;

int dx[6]={0,0,1,-1,0,0},dy[6]={1,-1,0,0,0,0},dz[6]={0,0,0,0,1,-1};
void BFS(){
	ans=0;q.push(Box(mx,my,mz));
	while(!q.empty()){
		int x=q.front().x,y=q.front().y,z=q.front().z;q.pop();
		for(int d=0;d<6;d++){
			int nx=x+dx[d],ny=y+dy[d],nz=z+dz[d];
			if(nx>=0&&nx<=mx&&ny>=0&&ny<=my&&nz>=0&&nz<=mz){
				if(vis[nx][ny][nz]) continue;
				if(sum[nx][ny][nz])
					ans++;
				else q.push(Box(nx,ny,nz)),vis[nx][ny][nz]=1;
			}
		}
	}
}

int main(){
	int x1,y1,z1,x2,y2,z2;
	scanf("%d",&n);
	mx=0,my=0,mz=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d%d%d",&x1,&y1,&z1,&x2,&y2,&z2);
		x1++;y1++;z1++;x2++;y2++;z2++;
		mx=max(mx,x2);my=max(my,y2);mz=max(mx,z2);
		sum[x1][y1][z1]++;sum[x2][y1][z1]--;sum[x1][y2][z1]--;sum[x1][y1][z2]--;
		sum[x1][y2][z2]++;sum[x2][y2][z1]++;sum[x2][y1][z2]++;
		sum[x2][y2][z2]--;
	}
	for(int i=1;i<=mx;i++)
		for(int j=1;j<=my;j++)
			for(int k=1;k<=mz;k++){
				sum[i][j][k]+=sum[i-1][j][k]+sum[i][j-1][k]+sum[i][j][k-1];
				sum[i][j][k]-=sum[i-1][j-1][k]+sum[i-1][j][k-1]+sum[i][j-1][k-1];
				sum[i][j][k]+=sum[i-1][j-1][k-1];
			}
	BFS();printf("%d\n",ans);
	return 0;
}
