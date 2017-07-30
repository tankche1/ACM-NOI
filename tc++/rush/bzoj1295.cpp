# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
# define pos(a,b) (a-1)*m+b
const int maxn=32;
const int INF=~0U>>1;
int n,m,t;
int g[maxn][maxn];
int first[maxn*maxn],next[maxn*maxn*8],v[maxn*maxn*8],dist[maxn*maxn*8],edge;
int nn;
bool inq[maxn*maxn];
int start;

struct SPFA{
	int d[maxn*maxn];
	
	void spfa(int s){
		queue<int> q;q.push(s);
		for(int i=1;i<=nn;i++) d[i]=INF;
			memset(inq,false,sizeof(inq));
		d[s]=start;
		while(!q.empty()){
			int x=q.front();q.pop();
			inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]>d[x]+dist[e]){
					d[v[e]]=d[x]+dist[e];
					if(!inq[v[e]])
						q.push(v[e]),inq[v[e]]=true;
				}
			}
		}
	}
};
SPFA spfa[maxn*maxn];

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	first[a]=edge;
	v[edge]=b;
	dist[edge++]=c;
}

int main(){
	char ch;
	scanf("%d%d%d",&n,&m,&t);nn=m*n;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			while((ch=getchar())&&ch!='0'&&ch!='1');
				g[i][j]=ch-'0';
			}
			edge=0;memset(first,-1,sizeof(first));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(i!=n) add_edge(pos(i,j),pos(i+1,j),g[i+1][j]);
			if(i!=1) add_edge(pos(i,j),pos(i-1,j),g[i-1][j]);
			if(j!=m) add_edge(pos(i,j),pos(i,j+1),g[i][j+1]);
			if(j!=1) add_edge(pos(i,j),pos(i,j-1),g[i][j-1]);
	}
	//printf("%d %d\n",edge,maxn*maxn*8);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
		start=g[i][j];spfa[pos(i,j)].spfa(pos(i,j));
		}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			for(int ii=1;ii<=n;ii++)
				for(int jj=1;jj<=m;jj++){
					if(spfa[pos(i,j)].d[pos(ii,jj)]<=t){
						int dist=((ii-i)*(ii-i)+(jj-j)*(jj-j));
						if(dist>ans) {ans=dist;//printf("%d %d %d %d dist:%d\n",i,j,ii,jj,spfa[pos(i,j)].d[pos(ii,jj)]);
						}
					}
				}
		}
		double anss=sqrt(ans);
		printf("%.6lf\n",anss);
	return 0;
}
/*
5 5 6
11111
11111
11111
11111
11111

*/
