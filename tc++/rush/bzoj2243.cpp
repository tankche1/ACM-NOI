# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=~0U>>1;
int n,m;
int weight[maxn];
int rcol,lcol;

struct Node{
	int lc,rc,sum,lazy;
	Node() {}
	Node(int lc,int rc,int sum,int lazy=-1):lc(lc),rc(rc),sum(sum),lazy(lazy) {}
};

struct SeqmentTree{
	Node s[maxn<<2];
	
	void pushup(int o){
		s[o]=Node(s[o<<1].lc,s[o<<1|1].rc,s[o<<1].sum+s[o<<1|1].sum-(s[o<<1].rc==s[o<<1|1].lc));
	}
	
	void pushdown(int o){
		if(s[o].lazy!=-1){
			s[o<<1].lazy=s[o<<1|1].lazy=s[o<<1].lc=s[o<<1].rc=s[o<<1|1].lc=s[o<<1|1].rc=s[o].lazy;
			s[o<<1].sum=s[o<<1|1].sum=1;
			s[o].lazy=-1;
		}
	}
	
	void build(int o,int L,int R){
		if(L==R){
			s[o]=Node(weight[L],weight[L],1);return;
		}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
		pushup(o);
	}
	
	void change(int o,int L,int R,int qL,int qR,int col){
		if(qL<=L&&qR>=R){
			s[o].sum=1;s[o].lc=s[o].rc=col;s[o].lazy=col;return;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(qL<=M) change(o<<1,L,M,qL,qR,col);
		if(qR>M) change(o<<1|1,M+1,R,qL,qR,col);
		pushup(o);
	}
	
	int query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R){
			if(L==qL) lcol=s[o].lc;
			if(R==qR) rcol=s[o].rc;
			return s[o].sum;
		}
		pushdown(o);
		int M=(L+R)>>1;
		if(qR<=M) return query(o<<1,L,M,qL,qR);
			else if(qL>M) return query(o<<1|1,M+1,R,qL,qR);
				else{
					return query(o<<1,L,M,qL,qR)+query(o<<1|1,M+1,R,qL,qR)-(s[o<<1].rc==s[o<<1|1].lc);
				}
	}
};
SeqmentTree seq;

int first[maxn],next[maxn<<1],v[maxn<<1],edge=0,st_w[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];v[edge]=b;first[a]=edge++;
}

int fa[maxn],son[maxn],size[maxn],dfn[maxn],dfs_clock=0,top[maxn],dep[maxn];

void q_change(int a,int b,int c){
	int ta=top[a],tb=top[b];
	while(ta!=tb){
		if(dep[ta]<dep[tb]) swap(a,b),swap(ta,tb);
		seq.change(1,1,n,dfn[ta],dfn[a],c);//printf("ta:%d a:%d\n",ta,a);
		a=fa[ta];ta=top[a];
	}
	if(dep[a]>dep[b]) swap(a,b);
	seq.change(1,1,n,dfn[a],dfn[b],c);//printf("a:%d b:%d\n",a,b);
}

void q_ask(int a,int b){
	int ta=top[a],tb=top[b],ca=-1,cb=-1,ans=0;
	while(ta!=tb){
		if(dep[ta]<dep[tb]) swap(a,b),swap(ta,tb),swap(ca,cb);
		ans+=seq.query(1,1,n,dfn[ta],dfn[a]);ans-=rcol==ca;//printf("ta:%d a:%d\n",ta,a);
		a=fa[ta];
		ta=top[a];ca=lcol;
	}
	if(dep[a]>dep[b]) swap(a,b),swap(ca,cb);
	ans+=seq.query(1,1,n,dfn[a],dfn[b]);ans-=rcol==cb;ans-=lcol==ca;//printf("a:%d b:%d\n",a,b);
	printf("%d\n",ans);
}

void dfs_size(int x){
	size[x]=1;son[x]=0;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa[x]) continue;
		fa[v[e]]=x;//printf("x:%d v:%d\n",x,v[e]);
		dfs_size(v[e]);size[x]+=size[v[e]];
		if(size[v[e]]>size[son[x]]) son[x]=v[e];
	}
}

void dfs(int x){
	dfn[x]=++dfs_clock;
	//printf("son[%d]:%d\n",x,son[x]);
	if(son[x]) top[son[x]]=top[x],dep[son[x]]=dep[x]+1,dfs(son[x]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa[x]||v[e]==son[x]) continue;
		top[v[e]]=v[e];dep[v[e]]=dep[x]+1;
		dfs(v[e]);
	}
}

int main(){
	//freopen("input.txt","r",stdin);
	int a,b,c;
	char op[20];
	scanf("%d",&n);	scanf("%d",&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&st_w[i]);
	memset(first,-1,sizeof(first));
	for(int i=1;i<n;i++)
		scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);size[0]=0;
	fa[1]=0;dfs_size(1);top[1]=1;dep[1]=1;
	dfs(1);
	for(int i=1;i<=n;i++) 
		weight[dfn[i]]=st_w[i];
	seq.build(1,1,n);
	for(int mm=1;mm<=m;mm++){
		scanf("%s",op);
		if(op[0]=='C'){
			scanf("%d%d%d",&a,&b,&c);
			q_change(a,b,c);
		}
		else{
			scanf("%d%d",&a,&b);
			q_ask(a,b);
		}
	}
	return 0;
}
