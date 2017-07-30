# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=maxn*3;
typedef long long LL;
const LL INF=(LL)1<<60;
int n,m;
int u[maxm],v[maxm],w[maxm],edge;
int bh[maxm];
int p[maxn];
int fa[maxn],weight[maxn];
bool used[maxm];
vector<int> G[maxn];
int deep[maxn];

struct State{
	int to;LL dist1,dist2;
	State(){}
	State(int to,LL dist1,LL dist2):to(to),dist1(dist1),dist2(dist2) {}
};
State dp[maxn][18];
const int Step=17;
int Two[18];

bool cmp(int a,int b){
	return w[a]<w[b];
}

void add_edge(int a,int b,int c){
	u[edge]=a;
	v[edge]=b;
	w[edge]=c;
	edge++;
}

int find(int x){
	if(x==p[x]) return x;
		return p[x]=find(p[x]);
}

LL kru=0;
void Kruskal(){
	memset(used,false,sizeof(used));
	for(int i=1;i<=m;i++)
		bh[i]=i;
	for(int i=1;i<=n;i++)
		p[i]=i;
	sort(bh+1,bh+m+1,cmp);
	for(int i=1;i<=m;i++){
		int e=bh[i];
		int px=find(u[e]),py=find(v[e]);
		if(px!=py){
			used[e]=true;
			G[u[e]].push_back(e);G[v[e]].push_back(e);
			p[px]=py;
			kru+=w[e];
		}
	}
}

void dfs(int x){
	for(int e=0;e<G[x].size();e++){
		int to=u[G[x][e]]==x?v[G[x][e]]:u[G[x][e]];
		if(to!=fa[x]){
			//printf("x:%d to:%d\n",x,to);
			deep[to]=deep[x]+1;
			fa[to]=x;weight[to]=w[G[x][e]];dfs(to);
		}
	}
}

void DP(){
	for(int i=1;i<=n;i++)
		dp[i][0]=State(fa[i],weight[i],0);
	for(int i=1;i<=Step;i++)
		for(int j=1;j<=n;j++){
			if(i) dp[j][i]=State(dp[dp[j][i-1].to][i-1].to,max(dp[j][i-1].dist1,dp[dp[j][i-1].to][i-1].dist1),max(dp[j][i-1].dist1==dp[dp[j][i-1].to][i-1].dist1?LL(0):min(dp[j][i-1].dist1,dp[dp[j][i-1].to][i-1].dist1),max(dp[j][i-1].dist2,dp[dp[j][i-1].to][i-1].dist2)));
		//	if(i<=2) printf("dp[%d][%d]:%d %lld %lld\n",j,i,dp[j][i].to,dp[j][i].dist1,dp[j][i].dist2);
		}
}

LL ans=INF;LL sh;
void LCA(int a,int b){
	LL f=0,s=0;
	//printf("a:%d b:%d\n",a,b);
	//bool first=true;
	if(deep[a]<deep[b]) swap(a,b);
	int t=deep[a]-deep[b];
	for(int j=0;j<=Step;j++)
		if(t&Two[j]) {
			f=max(dp[a][j].dist1,f);if(dp[a][j].dist1!=f) s=max(s,dp[a][j].dist1);s=max(s,dp[a][j].dist2);
			//	printf("a:%d\n",a);
			a=dp[a][j].to;
		}
		int j=Step;
	while(a!=b){
		while(j&&dp[a][j].to==dp[b][j].to) j--;
		f=max(dp[a][j].dist1,f);if(dp[a][j].dist1!=f) s=max(s,dp[a][j].dist1);s=max(s,dp[a][j].dist2);
		f=max(dp[b][j].dist1,f);if(dp[b][j].dist1!=f) s=max(s,dp[b][j].dist1);s=max(s,dp[b][j].dist2);
		a=dp[a][j].to;b=dp[b][j].to;
	}
	//printf("f:%lld s:%lld\n",f,s);
	if(sh-f<=kru) ans=min(ans,sh-s);
		else ans=min(ans,sh-f);
	//printf("a:%d b:%d res:%d\n",aa,bb,res);
}

int main(){
	Two[0]=1;for(int i=1;i<=Step;i++) Two[i]=Two[i-1]<<1;
	int a,b,c;
	scanf("%d%d",&n,&m);
	edge=1;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	Kruskal();
	fa[1]=1;weight[1]=0;deep[1]=0;
	dfs(1);
	DP();
	//printf("%lld\n",kru);
	for(int i=1;i<=m;i++)
		if(!used[i]){
			sh=kru+w[i];
			LCA(u[i],v[i]);;
		}
	printf("%lld\n",ans);
	//	printf("%lld\n",INF);
	return 0;
}
/*
4 6
2 3 2
1 2 3
1 3 3
1 4 3
2 4 3
3 4 3

*/
