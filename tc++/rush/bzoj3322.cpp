# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
const LL INF=(LL)1<<60;
const int Step=17;
int dp[maxn][Step+2];
LL _min[maxn][Step+2];
int Two[Step+2];
struct Edge{
	int u,v,w;
};
Edge edges[maxn<<1];
bool cmp(Edge E1,Edge E2){
	return E1.w>E2.w;
}
int n,m,q;
int bh[maxn],b[maxn],deep[maxn];
LL w[maxn<<1],weight[maxn];
int p[maxn];
bool have[maxn];
int first[maxn],next[maxn<<1],v[maxn<<1],edge,fa[maxn];
int find(int x){if(x==p[x]) return x;return p[x]=find(p[x]);}

void add_edge(int a,int b,LL c){
	//printf("a:%d b:%d c:%lld\n",a,b,c);
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

void dfs(int x){
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]){
			fa[v[e]]=x;weight[v[e]]=w[e];deep[v[e]]=deep[x]+1;//printf("%lld\n",weight[v[e]]);
			dfs(v[e]);
		}
}

void get_DP(){
	for(int i=1;i<=n;i++)
		dp[i][0]=fa[i],_min[i][0]=weight[i];
	for(int j=1;j<=Step;j++)
		for(int i=1;i<=n;i++){
			dp[i][j]=dp[dp[i][j-1]][j-1];
			_min[i][j]=min(_min[i][j-1],_min[dp[i][j-1]][j-1]);
		}
}

LL Lca(int a,int b){
	//printf("a:%d b:%d ",a,b);
	if(deep[a]<deep[b]) swap(a,b);
		int t=deep[a]-deep[b];
	LL res=INF;
	for(int j=Step;j>=0;j--)
		if(t&Two[j]) res=min(res,_min[a][j]),a=dp[a][j];
			int j=Step;
	while(a!=b){
		while(j>0&&dp[a][j]==dp[b][j]) j--;
		res=min(res,min(_min[a][j],_min[b][j]));
		a=dp[a][j];b=dp[b][j];
	}
	//printf("res:%d\n",res);
	return res;
}

int main(){
	//printf("%lld\n",INF);
	Two[0]=1;
	for(int i=1;i<=Step;i++) Two[i]=Two[i-1]<<1;
	int x;
	scanf("%d%d%d",&n,&m,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&bh[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&edges[i].u,&edges[i].v,&edges[i].w);
	for(int i=1;i<=q;i++)
		scanf("%d",&x),have[x]=1;
	for(int i=1;i<=n;i++) p[i]=i;
	int last=-1;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=n;i++)
		if(have[i]){
			if(last==-1) last=i;
			else p[i]=p[last],add_edge(last,i,INF),add_edge(i,last,INF),last=i;
		}
		sort(edges+1,edges+m+1,cmp);
	for(int i=1;i<=m;i++){
		int px=find(edges[i].u),py=find(edges[i].v);
		if(px!=py){
			add_edge(edges[i].u,edges[i].v,edges[i].w);add_edge(edges[i].v,edges[i].u,edges[i].w);
			p[px]=py;
		}
	}
	LL now=0;//ans=0;
	fa[1]=1;weight[1]=0;deep[1]=0;
	dfs(1);
	get_DP();
	if(b[bh[1]]>0) now=b[bh[1]];
	else puts("0");
	for(int i=2;i<=n;i++){
		//printf("i:%d now:%lld\n",i,now);
		LL limit=Lca(bh[i-1],bh[i]);
		if(now>limit) now=limit;
			//printf("%lld %d\n",now,b[bh[i]]);
		if(b[bh[i]]<0) printf("%lld\n",min(now,(LL)-b[bh[i]]));
		now=max((LL)0,now+b[bh[i]]);
	}
	return 0;
}
