#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=30010;
const int maxm=100010;
const int maxq=40010;
const int Step=20;
int Two[22];
int n,m,q;
int p[maxn];
int find(int x){if(x==p[x]) return x;return p[x]=find(p[x]);}
struct Edge{
	int a,b;
	bool used;
	bool del;
	Edge() {used=0;del=0;}
	Edge(int a,int b):a(a),b(b) {used=0;del=0;}
	bool operator < (const Edge &rhs)const{
		if(a==rhs.a) return b<rhs.b;return a<rhs.a;
	}
};
Edge edges[maxm];
//bool cmp(Edge x,Edge y){}
int find_edge(Edge x) {return lower_bound(edges+1,edges+m+1,x)-edges;}
int first[maxn],next[maxn<<1],v[maxn<<1],fa[maxn],deep[maxn],dp[maxn][21],edge,start[maxn],end[maxn],dfs_clock;
int A[maxn],duty[maxq][3],ans[maxq];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

struct Segment{
	int add[maxn<<2];
	int sum[maxn<<2];
	Segment() {memset(add,0,sizeof(add));}
	
	void build(int o,int L,int R){
		if(L==R) {sum[o]=A[L];return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);build(o<<1|1,M+1,R);
		sum[o]=sum[o<<1]+sum[o<<1|1];
	}
	
	void pushdown(int o,int L,int R){
		if(add[o]){
			int M=(L+R)>>1;
			add[o<<1]+=add[o];add[o<<1|1]+=add[o];
			sum[o<<1]+=(M-L+1)*add[o];sum[o<<1|1]+=(R-M)*add[o];
			add[o]=0;
		}
	}
	
	void update(int o,int L,int R,int qL,int qR,int val){
		if(qL<=L&&qR>=R){
			sum[o]+=(R-L+1)*val;
			add[o]+=val;return;
		}
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
	}
	
	int query(int o,int L,int R,int q){
		if(L==R)
			return sum[o];
		pushdown(o,L,R);
		int M=(L+R)>>1;
		if(q<=M)
			return query(o<<1,L,M,q);
		else return query(o<<1|1,M+1,R,q);
	}
}seg;

void pre_dp(){
	Two[0]=1;
	for(int i=1;i<=20;i++) Two[i]=Two[i-1]<<1;
	for(int i=1;i<=n;i++) dp[i][0]=fa[i];
	for(int j=1;j<=Step;j++)
		for(int i=1;i<=n;i++)
			dp[i][j]=dp[dp[i][j-1]][j-1];
}

int lca(int a,int b){
	if(deep[a]<deep[b]) swap(a,b);
	int t=deep[a]-deep[b];
	for(int j=Step;j>=0;j--)
		if(t&Two[j]) a=dp[a][j];
	int j=Step;
	while(a!=b){
		while(j>0&&dp[a][j]==dp[b][j]) j--;
		a=dp[a][j];b=dp[b][j];
	}
	return a;
}

void dfs(int x){
	start[x]=++dfs_clock;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]) fa[v[e]]=x,deep[v[e]]=deep[x]+1,dfs(v[e]);
	end[x]=dfs_clock;
}

void plus_edge(int a,int b){
	int px=find(a),py=find(b);
	if(px==py) return;
	int ancestor=lca(a,b);int pa=find(ancestor);
	while(a!=ancestor){
		if(find(a)==pa) break;
		a=find(a);
		seg.update(1,1,n,start[a],end[a],-1);
		p[a]=pa;
		a=fa[a];
	}
	while(b!=ancestor){
		if(find(b)==pa) break;
		b=find(b);
		seg.update(1,1,n,start[b],end[b],-1);
		p[b]=pa;
		b=fa[b];
	}
	
}

int main(){
	q=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&edges[i].a,&edges[i].b);if(edges[i].a>edges[i].b) swap(edges[i].a,edges[i].b);
	}
	sort(edges+1,edges+m+1);
	while(scanf("%d",&duty[++q][0])){
		if(duty[q][0]==-1) break;
		scanf("%d%d",&duty[q][1],&duty[q][2]);
		if(duty[q][1]>duty[q][2]) swap(duty[q][1],duty[q][2]);
		if(duty[q][0]==0) edges[find_edge(Edge(duty[q][1],duty[q][2]))].del=true;
	}q--;
	for(int i=1;i<=n;i++)
		p[i]=i;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		if(edges[i].del) continue;
		int px=find(edges[i].a),py=find(edges[i].b);
		if(px!=py)
			p[px]=py,edges[i].used=1,add_edge(edges[i].a,edges[i].b);
	}
	dfs_clock=0;fa[1]=1;deep[1]=1;
	dfs(1);
	for(int i=1;i<=n;i++)
		A[start[i]]=deep[i];
	seg.build(1,1,n);
	pre_dp();
	for(int i=1;i<=n;i++) p[i]=i;
	for(int i=1;i<=m;i++){
		if(edges[i].del==0&&edges[i].used==0){
			plus_edge(edges[i].a,edges[i].b);
		}
	}
	for(int i=q;i>=1;i--){
		if(duty[i][0]==0){
			plus_edge(duty[i][1],duty[i][2]);
		}
		else{
			ans[i]=seg.query(1,1,n,start[duty[i][1]])+seg.query(1,1,n,start[duty[i][2]])-2*seg.query(1,1,n,start[lca(duty[i][1],duty[i][2])]);
		}
	}
	for(int i=1;i<=q;i++)
		if(duty[i][0]) printf("%d\n",ans[i]);
	return 0;
}
