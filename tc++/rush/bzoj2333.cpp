# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=300010;
const int INF=maxn*1001;
int n,m;

struct Order{
	char op;
	int bh,x,v;
};
Order order[maxn];
int fa[maxn],end[maxn],son[maxn],pos[maxn];
int weight[maxn];
int tot;
int find(int x){
	if(x==fa[x]) return x;
	return fa[x]=find(fa[x]);
}

struct SegmentTree{
	int Max[maxn<<2],lazy[maxn<<2],ans;
	
	void maintain(int o){Max[o]=max(Max[o<<1],Max[o<<1|1]);}
	
	void pushdown(int o){
		if(lazy[o]!=0){
			Max[o<<1]+=lazy[o];Max[o<<1|1]+=lazy[o];
			lazy[o<<1]+=lazy[o];lazy[o<<1|1]+=lazy[o];
			lazy[o]=0;
		}
	}
	
	void build(int o,int L,int R){
		lazy[o]=0;
		if(L==R) {Max[o]=weight[L];return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
		maintain(o);
	}
	
	void add(int o,int L,int R,int qL,int qR,int v){
		if(qL<=L&&qR>=R){
			lazy[o]+=v;Max[o]+=v;return;
		}
		int M=(L+R)>>1;
		pushdown(o);
		if(qL<=M) add(o<<1,L,M,qL,qR,v);
		if(qR>M) add(o<<1|1,M+1,R,qL,qR,v);
		maintain(o);
	}
	
	void _query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R){
			ans=max(ans,Max[o]);return;
		}
		int M=(L+R)>>1;
		pushdown(o);
		if(qL<=M) _query(o<<1,L,M,qL,qR);
		if(qR>M) _query(o<<1|1,M+1,R,qL,qR);
		return;
	}
	
	void query_max(int qL,int qR){
		ans=-INF;
		_query(1,1,n,qL,qR);
		printf("%d\n",ans);
	}
};
SegmentTree seg;

int A[maxn];
int main(){
	char t;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		while((t=getchar())&&t!='U'&&t!='A'&&t!='F');
		order[i].op=t;
		if(t=='A'||t=='F') scanf("%d",&order[i].bh);
		if((t=='A'&&order[i].bh<=2)||t=='U') scanf("%d%d",&order[i].x,&order[i].v);
		else if(t=='A') scanf("%d",&order[i].v);
		else if(t=='F'&&order[i].bh<=2) scanf("%d",&order[i].x);
	}
	
	for(int i=1;i<=n;i++) fa[i]=i,end[i]=i,son[i]=0;
	for(int i=1;i<=m;i++)
		if(order[i].op=='U'){
			int px=find(order[i].x),py=find(order[i].v);
			if(px>py) swap(px,py);
			fa[py]=px;
			son[end[px]]=py;
			//printf("son[%d]:%d\n",end[px],py);
			end[px]=end[py];
		}
	
	tot=0;
	memset(end,0,sizeof(end));
	for(int i=1;i<=n;i++){
		int x=i;
		while(x>0&&(!end[x])){
			//printf("x:%d\n",x);
			end[x]=++tot;
			pos[x]=tot;
			x=son[x];
		}
	}
	for(int i=1;i<=n;i++)
		weight[pos[i]]=A[i];
	seg.build(1,1,n);
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<=m;i++){
		if(order[i].op=='U'){
			int px=find(order[i].x),py=find(order[i].v);
			if(px>py) swap(px,py);
			end[px]=end[py];
			fa[py]=px;
			//printf("pos:%d end:%d\n",pos[px],end[px]);
		}
		else if(order[i].op=='A'){
			if(order[i].bh==1)
				seg.add(1,1,n,pos[order[i].x],pos[order[i].x],order[i].v);
			else if(order[i].bh==2){
				int px=find(order[i].x);
				seg.add(1,1,n,pos[px],end[px],order[i].v);
			}
			else
				seg.add(1,1,n,1,n,order[i].v);
		}
		else{
			if(order[i].bh==1)
				seg.query_max(pos[order[i].x],pos[order[i].x]);
			else if(order[i].bh==2){
				int px=find(order[i].x);
				seg.query_max(pos[px],end[px]);
			}
			else
				seg.query_max(1,n);
		}
	}
	return 0;
}
