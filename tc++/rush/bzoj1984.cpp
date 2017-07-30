# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],w[maxn<<1],edge;
int tot,A[maxn];

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

struct SegmentTree{
	int _max[maxn<<2];
	int same[maxn<<2],add[maxn<<2];
	
	void build(int o,int L,int R){
		same[o]=-1;add[o]=0;
		if(L==R){
			_max[o]=A[L];return;
		}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
		_max[o]=max(_max[o<<1],_max[o<<1|1]);
	}
	
	void pushdown(int o){
		if(same[o]!=-1){
			add[o<<1]=add[o<<1|1]=0;
			same[o<<1]=same[o<<1|1]=-1;
			_max[o<<1]=same[o];
			_max[o<<1|1]=same[o];
			same[o]=-1;
		}
		if(add[o]!=0){
			add[o<<1]+=add[o];add[o<<1|1]+=add[o];
			_max[o<<1]+=add[o];
			_max[o<<1|1]+=add[o];
			add[o]=0;
		}
	}
	
	void update(int o,int L,int R,int qL,int qR,int val,int op){
		if(qL<=L&&qR>=R){
			if(op==1){
				_max[o]=val;
				add[o]=0;
				same[o]=val;
			}
			else if(op==2){
				_max[o]+=val;add[o]+=val;
			}
			else tot=max(tot,_max[o]);
			return;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(qL<=M) update(o<<1,L,M,qL,qR,val,op);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,val,op);
		_max[o]=max(_max[o<<1],_max[o<<1|1]);
	}
}seq;

int size[maxn],top[maxn],fa[maxn],son[maxn],deep[maxn],bh[maxn],ctop;
int weight[maxn],tbh=0;

void dfs_size(int x){
	size[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]){
			weight[v[e]]=w[e];
			fa[v[e]]=x,deep[v[e]]=deep[x]+1,dfs_size(v[e]),size[x]+=size[v[e]];
			if(!son[x]||size[v[e]]>size[son[x]]) son[x]=v[e];
		}
		//printf("x:%d fa:%d son:%d\n",x,fa[x],son[x]);
}

void dfs_build(int x){
	bh[x]=++tbh;
	if(son[x]) top[son[x]]=top[x],dfs_build(son[x]);
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]&&v[e]!=son[x]){
			top[v[e]]=++ctop;
			dfs_build(v[e]);
		}
}

void update(int a,int b,int val,int op){
	int ta=top[a],tb=top[b];
	//printf("a:%d b:%d ta:%d tb:%d\n",a,b,ta,tb);
	tot=0;
	while(ta!=tb){
		if(deep[ta]<deep[tb]) swap(a,b);
			//printf("ta:%d a:%d\n",ta,a);
		seq.update(1,1,n,bh[ta],bh[a],val,op);
		a=fa[ta];ta=top[a];
	}
	if(deep[a]>deep[b]) swap(a,b);
	if(bh[a]+1<=bh[b])
	seq.update(1,1,n,bh[a]+1,bh[b],val,op);
	if(op==3) printf("%d\n",tot);
}

char op[20];
int main(){
	int a,b,c;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
	memset(son,0,sizeof(son));
	fa[1]=0;deep[1]=1;weight[1]=0;dfs_size(1);
	ctop=0;top[1]=++ctop;dfs_build(1);
	for(int i=1;i<=n;i++)
		A[bh[i]]=weight[i];
	seq.build(1,1,n);
	int uu,vv,ww,k;
	while(scanf("%s",op)){
		if(op[1]=='h'){
			scanf("%d%d",&k,&ww);
			uu=fa[v[2*k]]==v[2*k+1]?v[2*k]:v[2*k+1];
			vv=(fa[v[2*k]]!=v[2*k+1])?v[2*k]:v[2*k+1];
			update(uu,vv,ww,1);
		}
		else if(op[1]=='o'){
			scanf("%d%d%d",&uu,&vv,&ww);
			update(uu,vv,ww,1);
		}
		else if(op[1]=='d'){
			scanf("%d%d%d",&uu,&vv,&ww);
			update(uu,vv,ww,2);
		}
		else if(op[1]=='a'){
			scanf("%d%d",&uu,&vv);
			update(uu,vv,0,3);
		}
		else break;
	}
	return 0;
}
