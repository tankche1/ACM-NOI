# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=30005;
const int INF=1<<29;
int weight[maxn];

struct IntervalTree{
	int Max[maxn<<2],sum[maxn<<2];
	
	void pushup(int o){
		Max[o]=max(Max[o<<1],Max[(o<<1)|1]);
		sum[o]=sum[o<<1]+sum[(o<<1)|1];
	}
	
	void build(int o,int l,int r){
		if(l==r) sum[o]=Max[o]=weight[l];
		else{
			int M=(l+r)>>1;
			build(o<<1,l,M);build((o<<1)|1,M+1,r);
			pushup(o);
		}
	}
	
	void change(int o,int L,int R,int x,int W){
		if(L==R) Max[o]=sum[o]=W;
			else{
				int M=(L+R)>>1;
				if(x<=M) change(o<<1,L,M,x,W);
					else change((o<<1)|1,M+1,R,x,W);
				pushup(o);
			}
	}
	
	int query_max(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R)
			return Max[o];
		else{
			int ans=-INF,M=(L+R)>>1;
			if(qL<=M)
				ans=max(ans,query_max(o<<1,L,M,qL,qR));
			if(qR>M) ans=max(ans,query_max((o<<1)|1,M+1,R,qL,qR));
		return ans;
		}
	}
	
	int query_sum(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R) return sum[o];
		else{
			int ans=0,M=(L+R)>>1;
			if(qL<=M)
				ans+=query_sum(o<<1,L,M,qL,qR);
			if(qR>M) 
				ans+=query_sum((o<<1)|1,M+1,R,qL,qR);
			return ans;
		}
	}
};
IntervalTree seq;
int dfn[maxn],dfs_clock,top[maxn],size[maxn],fa[maxn],son[maxn],dep[maxn];
int n;

int qmax(int a,int b){
	int ta=top[a],tb=top[b];
	int ans=-INF;
	while(ta!=tb){
		//printf("a:%d ta:%d b:%d tb:%d\n",a,ta,b,tb);
		if(dep[ta]<dep[tb]){
			swap(ta,tb);swap(a,b);
		}
		ans=max(ans,seq.query_max(1,1,n,dfn[ta],dfn[a]));
		a=fa[ta];
		ta=top[a];
	}
	if(dep[a]>dep[b])
		swap(a,b);
	ans=max(ans,seq.query_max(1,1,n,dfn[a],dfn[b]));
	return ans;
}

int qsum(int a,int b){
	int ta=top[a],tb=top[b],ans=0;
	while(ta!=tb){
		if(dep[ta]<dep[tb]) swap(ta,tb),swap(a,b);
		ans+=seq.query_sum(1,1,n,dfn[ta],dfn[a]);//printf("a:%d ta:%d sum:%d\n",a,ta,seq.query_sum(1,1,n,dfn[ta],dfn[a]));
		a=fa[ta];
		ta=top[a];
	}
	if(dep[a]>dep[b]) swap(a,b);
		//printf("a:%d b:%d %d\n",a,b,seq.query_sum(1,1,n,dfn[a],dfn[b]));
		ans+=seq.query_sum(1,1,n,dfn[a],dfn[b]);
	return ans;
}

int first[maxn],next[maxn*2],v[maxn*2],edge;
void add_edge(int a,int b) {next[edge]=first[a];v[edge]=b;first[a]=edge++;}

void dfs_size(int x,int pa){
	//printf("x:%d\n",x);
	fa[x]=pa;
	size[x]=1;son[x]=0;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa[x]) continue;
		dep[v[e]]=dep[x]+1;
		dfs_size(v[e],x);
		size[x]+=size[v[e]];
		if(size[v[e]]>size[son[x]]) son[x]=v[e];
	}
}

void dfs(int x,int tx){
	//printf("x:%d\n",x);
	dfn[x]=++dfs_clock;
	top[x]=tx;
	//printf("top[%d]:%d\n",x,top[x]);
	if(son[x]!=0)
	dfs(son[x],tx);
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa[x]||v[e]==son[x]) continue;
		dfs(v[e],v[e]);
	}
}

int w[maxn];
int main(){
	int a,b;char op[20];
	scanf("%d",&n);
	memset(first,-1,sizeof(first));
	edge=0;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	dfs_clock=0;size[0]=0;
	dep[1]=1;
	dfs_size(1,0);
	dfs(1,1);
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	for(int i=1;i<=n;i++)
		weight[dfn[i]]=w[i];
	seq.build(1,1,n);
	int q;
	scanf("%d",&q);
	while(q--){
		scanf("%s%d%d",op,&a,&b);
		if(op[0]=='C'){
			seq.change(1,1,n,dfn[a],b);
		}
		else if(op[1]=='M'){
			printf("%d\n",qmax(a,b));
		}
		else printf("%d\n",qsum(a,b));
	}
	return 0;
}
