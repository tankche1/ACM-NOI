# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int Step=17;
const int INF=~0U>>1;
int n,m;
int first[maxn],next[maxn<<1],v[maxn<<1],d[maxn],dp[maxn][18],edge;
int size[maxn],fa[maxn],dep[maxn],dfn[maxn],dfs_clock=0,range[maxn],son[maxn],top[maxn];
int froot,nroot;
int weight[maxn];

struct SegmenTree{
	int _min[maxn<<2],same[maxn<<2];
	
	void pushup(int o){_min[o]=min(_min[o<<1],_min[o<<1|1]);}
	void pushdown(int o) {if(same[o]) same[o<<1]=same[o<<1|1]=_min[o<<1]=_min[o<<1|1]=same[o],same[o]=0;}
	
	void build(int o,int L,int R){
		same[o]=0;
		if(L==R){_min[o]=weight[L];return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
		pushup(o);
	}
	
	void update(int o,int L,int R,int qL,int qR,int val){
		if(qL<=L&&qR>=R){
			_min[o]=val;same[o]=val;return;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
		pushup(o);
	}
	
	int query(int o,int L,int R,int qL,int qR){
		if(qL>qR) return INF;
		if(qL<=L&&qR>=R)
			return _min[o];
		pushdown(o);
		int M=(L+R)>>1;
		int ans=INF;
		if(qL<=M) ans=min(ans,query(o<<1,L,M,qL,qR));
		if(qR>M) ans=min(ans,query(o<<1|1,M+1,R,qL,qR));
		return ans;
	}
}seg;

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs_size(int x){
	size[x]=1;son[x]=0;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa[x]) continue;
		fa[v[e]]=x;dep[v[e]]=dep[x]+1;dfs_size(v[e]);
		if(size[v[e]]>size[son[x]]) son[x]=v[e];
		size[x]+=size[v[e]];
	}
}

void dfs_build(int x){
	dfn[x]=++dfs_clock;
	if(son[x]) top[son[x]]=top[x],dfs_build(son[x]);
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=son[x]&&v[e]!=fa[x])
			top[v[e]]=v[e],dfs_build(v[e]);
	range[x]=dfs_clock;
}

void make_DP(){
	for(int i=1;i<=n;i++)
		dp[i][0]=fa[i];
	for(int j=1;j<=Step;j++)
		for(int i=1;i<=n;i++)
			dp[i][j]=dp[dp[i][j-1]][j-1];
}

int lca(int a,int b){
	if(dep[a]<dep[b]) swap(a,b);
	int t=dep[a]-dep[b];
	for(int j=Step;j>=0;j--)
		if(t&(1<<j))
			a=dp[a][j];
	int j=Step;
	while(a!=b){
		while(j>0&&dp[a][j]==dp[b][j]) j--;
		a=dp[a][j];b=dp[b][j];
	}
	return a;
}

void update(int a,int b,int val){
	int ta=top[a],tb=top[b];
	while(ta!=tb){
		if(dep[ta]<dep[tb]) swap(a,b),swap(ta,tb);
		seg.update(1,1,n,dfn[ta],dfn[a],val);
		a=fa[ta];ta=top[a];
	}
	if(dep[a]<dep[b]) swap(a,b);
	seg.update(1,1,n,dfn[b],dfn[a],val);
}

int get_k(int a,int t){
	for(int j=Step;j>=0;j--)
		if(t&(1<<j)) a=dp[a][j];
	return a;
}

void query(int pos){
	if(dep[lca(pos,nroot)]<dep[pos])
		printf("%d\n",seg.query(1,1,n,dfn[pos],range[pos]));
	else if(pos==nroot)
		printf("%d\n",seg.query(1,1,n,1,n));
	else{
		int y=get_k(nroot,dep[nroot]-dep[pos]-1);
		printf("%d\n",min(seg.query(1,1,n,1,dfn[y]-1),seg.query(1,1,n,range[y]+1,n)));
	}
}

int main(){
	int a,b,v,op,pos;
	scanf("%d%d",&n,&m);
	edge=0;memset(first,-1,sizeof(first));
	for(int i=1;i<n;i++)
		scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);
	for(int i=1;i<=n;i++)
		scanf("%d",&d[i]);
	scanf("%d",&froot);nroot=froot;
	
	fa[froot]=froot;dep[froot]=1;size[0]=0;top[froot]=froot;
	dfs_size(froot);
	dfs_build(froot);
	for(int i=1;i<=n;i++) weight[dfn[i]]=d[i];
	
	seg.build(1,1,n);
	make_DP();
	
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&nroot);
		}
		else if(op==2){
			scanf("%d%d%d",&a,&b,&v);
			update(a,b,v);
		}
		else{
			scanf("%d",&pos);
			query(pos);
		}
	}
	return 0;
}
/*
5 10
1 2 3 4 5
1 2 2 3 3 4 4 5
1 2 3 4 5
1
2 1 3 6
1 3
3 2
*/
