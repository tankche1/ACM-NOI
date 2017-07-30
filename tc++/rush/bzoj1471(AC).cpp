# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=155;
typedef long long LL;
int s1,t1,s2,t2;
int n,m;
int tp[maxn];
int out[maxn];
bool used[maxn][maxn];
typedef pair<int,int> pi;
struct Graph{
int first[maxn],next[maxn*maxn/2],v[maxn*maxn/2],edge;
	
	void init(){
		memset(first,-1,sizeof(first));edge=0;
	}

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

};Graph G1,G2;
int g[maxn][maxn];

queue<int> Q;
void top_sorted(){
	for(int i=1;i<=n;i++)
		if(!out[i]) Q.push(i);
	int bh=n;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		tp[x]=bh--;
		for(int e=G2.first[x];e!=-1;e=G2.next[e])
			if(--out[G2.v[e]]==0) Q.push(G2.v[e]);
	}
	memset(g,0,sizeof(g));
	for(int i=1;i<=n;i++)
		for(int e=G1.first[i];e!=-1;e=G1.next[e]){
			g[tp[i]][tp[G1.v[e]]]=1;
			//printf("%d %d\n",tp[i],tp[G1.v[e]]);
		}
}

queue<pi> q;
long long G[maxn][maxn];
long long f[maxn];

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	G1.init();G2.init();
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);out[a]++;
		G1.add_edge(a,b);G2.add_edge(b,a);
	}
	scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
	top_sorted();
	memset(G,0,sizeof(G));for(int i=1;i<=n;i++) G[i][i]=1;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++)
			if(G[j][i]){
				for(int k=i+1;k<=n;k++){
				//	printf("g[%d %d]:%d\n",i,k,g[i][k]);
					if(g[i][k])
					G[j][k]+=G[j][i];//printf("j:%d k:%d\n",j,k);
				}
				//printf("G[%d][%d]:%lld\n",j,i,G[j][i]);
			}
	}
	for(int i=1;i<=n;i++){
		f[i]=G[tp[s1]][i]*G[tp[s2]][i];
		for(int j=1;j<=i-1;j++){
			f[i]-=f[j]*G[j][i]*G[j][i];
		}
		//printf("f[%d]:%lld\n",i,f[i]);
	}
	LL ans=G[tp[s1]][tp[t1]]*G[tp[s2]][tp[t2]];
	for(int i=1;i<=n;i++)
		ans-=f[i]*G[i][tp[t1]]*G[i][tp[t2]];
	printf("%lld\n",ans);
	return 0;
}
