#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=200010;
const int INF=~0U>>1;
int n,m;
int A[maxn],weight[maxn];
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int depth[maxn],bh[maxn],maxdepth,dfs_clock,rangeL[maxn],rangeR[maxn],fa[maxn],sonL[maxn],sonR[maxn];
void add_edge(int x,int y){
	next[edge]=first[x];
	v[edge]=y;
	first[x]=edge++;
}

struct SegmenTree{
	int add[maxn<<2],sum[maxn<<2];
	
	void build(int o,int L,int R){
		add[o]=0;
		if(L==R) {sum[o]=weight[L];return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);build(o<<1|1,M+1,R);
		sum[o]=sum[o<<1]+sum[o<<1|1];
	}
	
	void pushdown(int o,int L,int R){
		if(add[o]){
			add[o<<1]+=add[o];add[o<<1|1]+=add[o];int M=(L+R)>>1;
			sum[o<<1]+=add[o]*(M-L+1);sum[o<<1|1]+=add[o]*(R-M);
			add[o]=0;
		}
	}
	
	void update(int o,int L,int R,int qL,int qR,int val){
		//printf("o:%d L:%d R:%d qL:%d qR:%d val:%d\n",o,L,R,qL,qR,val);
		if(qL<=L&&qR>=R){
			add[o]+=val;sum[o]+=(R-L+1)*val;return;
		}
		pushdown(o,L,R);
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val);
		sum[o]=sum[o<<1]+sum[o<<1|1];
	}
	
	int query(int o,int L,int R,int t){
		if(L==R) return sum[o];
		pushdown(o,L,R);
		int M=(L+R)>>1;
		if(t<=M) return query(o<<1,L,M,t);
			else return query(o<<1|1,M+1,R,t);
	}
	
}seg;

void dfs(int x,bool use){
	maxdepth=max(maxdepth,depth[x]);
	if(use) bh[x]=++dfs_clock,rangeL[x]=dfs_clock;
	if(!use) sonL[x]=dfs_clock+1;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x])
			fa[v[e]]=x,depth[v[e]]=depth[x]+1,dfs(v[e],!use);
	if(use) rangeR[x]=dfs_clock;
	if(!use) sonR[x]=dfs_clock;
}

int main(){
	//freopen("input.txt","r",stdin);
	int op,x,y,val;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
	}
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		scanf("%d%d",&x,&y),add_edge(x,y),add_edge(y,x);
	n++;add_edge(1,n),add_edge(n,1);depth[n]=1;dfs_clock=0;maxdepth=0;fa[n]=0;
	dfs(n,1);
	dfs(1,1);A[n]=0;
		
	for(int i=1;i<=n;i++)
		weight[bh[i]]=A[i];
	//for(int i=1;i<=n;i++) printf("i:%d bh:%d depth:%d rangeL:%d rangeR:%d\n",i,bh[i],depth[i],rangeL[i],rangeR[i]);
	seg.build(1,1,n);
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		//printf("i:%d\n",i);
		if(op==1){
			scanf("%d%d",&x,&val);
			seg.update(1,1,n,rangeL[x],rangeR[x],val);
			if(sonL[x]<=sonR[x]) seg.update(1,1,n,sonL[x],sonR[x],-val);
		}
		else{
			scanf("%d",&x);
			printf("%d\n",seg.query(1,1,n,bh[x]));
		}
	}
	return 0;
}
