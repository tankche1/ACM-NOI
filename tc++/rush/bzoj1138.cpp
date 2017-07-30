# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=410;
const int maxm=60010;
const int maxc=26;
vector<int> Face[maxn][maxc],Back[maxn][maxc];
int n,m;
struct state{
	int a,b,c;
	state(){}
	state(int a,int b,int c):a(a),b(b),c(c) {}
};
int Dist[maxn][maxn][maxc+1];

void BFS(){
	queue<state> Q;
	memset(Dist,-1,sizeof(Dist));
	for(int i=1;i<=n;i++)
		Dist[i][i][maxc]=0,Q.push(state(i,i,maxc));
	for(int i=1;i<=n;i++){
		for(int j=0;j<maxc;j++){
			for(int e=0;e<Face[i][j].size();e++)
				Dist[i][Face[i][j][e]][maxc]=1,Q.push(state(i,Face[i][j][e],maxc));
		}
	}
	while(!Q.empty()){
		state now=Q.front();Q.pop();
		//printf("a:%d b:%d c:%d dist:%d\n",now.a,now.b,now.c,Dist[now.a][now.b][now.c]);
		if(now.c==maxc){
			for(int j=0;j<maxc;j++)
				for(int e=0;e<Back[now.a][j].size();e++)
				if(Dist[Back[now.a][j][e]][now.b][j]==-1)
					Dist[Back[now.a][j][e]][now.b][j]=Dist[now.a][now.b][now.c]+1,Q.push(state(Back[now.a][j][e],now.b,j));
		}
		else{
			int j=now.c;
			for(int e=0;e<Face[now.b][j].size();e++)
				if(Dist[now.a][Face[now.b][j][e]][maxc]==-1)
					Dist[now.a][Face[now.b][j][e]][maxc]=Dist[now.a][now.b][now.c]+1,Q.push(state(now.a,Face[now.b][j][e],maxc));
		}
	}
}

int main(){
	int a,b;char t;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);while((t=getchar())&&(t>'z'||t<'a'));
		Face[a][t-'a'].push_back(b);
		Back[b][t-'a'].push_back(a);
	}
	BFS();
	int q;scanf("%d",&q);
	int x,last=0;
	for(int i=1;i<=q;i++){
		scanf("%d",&x);
		if(last){
			//printf("last:%d x:%d %d\n",last,x,Dist[last][x][maxc]);
			printf("%d\n",Dist[last][x][maxc]);
		}
		last=x;
	}
	return 0;
}
