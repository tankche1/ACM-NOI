# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# define ID(x,y) (x*n+y)
# include<algorithm>
using namespace std;
typedef unsigned long long LL;
const int maxn=33;
int m,n;
bool vis[maxn*maxn];
char s[maxn][maxn];
int dist[maxn*maxn];
LL plan[maxn*maxn];
int dx[8]={-1,-2,-2,-1,1,2,2,1},dy[8]={-2,-1,1,2,-2,-1,1,2};

struct Reach{
	vector<int> G;
	void find_path(int start){
		memset(vis,false,sizeof(vis));
		queue<int> q;
		q.push(start);vis[start]=true;G.push_back(start);
		while(!q.empty()){
			int pos=q.front();q.pop();
			int x=pos/n,y=pos%n;
			for(int i=0;i<8;i++){
				int newx=x+dx[i],newy=y+dy[i];
				if(newx>=0&&newx<m&&newy>=0&&newy<n){
					if(s[newx][newy]=='#'||s[newx][newy]=='*'||s[newx][newy]=='t'||s[newx][newy]=='s') continue;
					if(!vis[ID(newx,newy)]){
						vis[ID(newx,newy)]=1;
						q.push(newx*n+newy);G.push_back(newx*n+newy);
					}
				}
			}
		}
		/*printf("start:%d \n",start);
		for(int i=0;i<G.size();i++)
			printf("to: %d\n",G[i]);
		int a;scanf("%d",&a);*/
	}
};
Reach reach[maxn*maxn];

int start,end;

int BFS(int start){
	memset(dist,-1,sizeof(dist));
	memset(plan,0,sizeof(plan));
	queue<int> q;
	q.push(start);
	dist[start]=0;
	plan[start]=1;
	while(!q.empty()){
		memset(vis,false,sizeof(vis));
		int pos1=q.front();q.pop();
		if(dist[end]!=-1&&dist[pos1]!=dist[end]-1) break;
		for(int i=0;i<reach[pos1].G.size();i++){
			int pos2=reach[pos1].G[i];
			int x=pos2/n,y=pos2%n;
			for(int j=0;j<8;j++){
				int newx=x+dx[j],newy=y+dy[j];
				if(newx>=0&&newx<m&&newy>=0&&newy<n){
					if(s[newx][newy]=='*'||s[newx][newy]=='t'&&!vis[ID(newx,newy)]){
						vis[ID(newx,newy)]=1;
						if(dist[ID(newx,newy)]==-1||dist[ID(newx,newy)]==dist[pos1]+1)
						plan[ID(newx,newy)]+=plan[pos1];
						if(dist[ID(newx,newy)]==-1){
							dist[ID(newx,newy)]=dist[pos1]+1;
							q.push(ID(newx,newy));
						}
					}
				}
			}
		}
	}
	return dist[end]==-1?-1:dist[end]-1;
}

int main(){
	scanf("%d%d",&m,&n);
	for(int i=0;i<m;i++)
		scanf("%s",s[i]);
	for(int i=0;i<m;i++)
		for(int j=0;j<n;j++){
			reach[ID(i,j)].find_path(ID(i,j));
			if(s[i][j]=='s') start=ID(i,j);
			if(s[i][j]=='t') end=ID(i,j);
	}
	int ans=BFS(start);
	printf("%d\n",ans);
	if(ans!=-1) printf("%llu\n",plan[end]);
	return 0;
}
/*
5 5
s....
..*..
.*...
.t...
.....
*/
