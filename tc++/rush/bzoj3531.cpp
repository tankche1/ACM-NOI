#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=maxn*200;
int n,q;
int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;
int dep[maxn],fa[maxn],dfn[maxn],son[maxn],tp[maxn],size[maxn],dfs_clock,top_size;
int w[maxn],c[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs_size(int x){
	size[x]=1;son[x]=0;
	for(int e=first[x];e!=-1;e=next[e])
		if(fa[x]!=v[e]){
			fa[v[e]]=x;dep[v[e]]=dep[x]+1;
			dfs_size(v[e]);
			size[x]+=size[v[e]];
			if(size[v[e]]>size[son[x]]) son[x]=v[e];
		}
}

void dfs(int x){
	dfn[x]=++dfs_clock;
	if(son[x]) tp[son[x]]=tp[x],dfs(son[x]);
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]&&v[e]!=son[x])
			tp[v[e]]=v[e],dfs(v[e]);
}

struct Node{
	int sum,_max;
	Node *ch[2];
	Node() {}
};
Node *null,seq[maxm];int seq_cnt=0;

Node *New(){
	Node *o=&seq[seq_cnt++];
	o->ch[0]=o->ch[1]=null;o->sum=o->_max=0;return o;
}

struct SegmenTree{
	Node *root;
	SegmenTree() {}
	void build() {root=null;}
	void add(int l,int r,int pos,int val) {add(root,l,r,pos,val);}
	
	void add(Node* &o,int L,int R,int pos,int val){
		//printf("L:%d R:%d pos:%d val:%d o==null:%d o:%d\n",L,R,pos,val,o==null,o);
		if(o==null) o=New();//printf("L:%d R:%d pos:%d val:%d o==null:%d o:%d\n",L,R,pos,val,o==null,o);
		if(L==R) {o->sum+=val,o->_max+=val;return;}
		int M=(L+R)>>1;
		if(pos<=M) //printf("o->ch[0]:%d\n",o->ch[0]),
			add(o->ch[0],L,M,pos,val);
		else //printf("o->ch[1]:%d\n",o->ch[1]),
			add(o->ch[1],M+1,R,pos,val);
		o->_max=max(o->ch[0]->_max,o->ch[1]->_max);
		o->sum=o->ch[0]->sum+o->ch[1]->sum;
	}
	
	int query(int l,int r,int ql,int qr,int op) {return query(root,l,r,ql,qr,op);}
	int query(Node* &o,int L,int R,int qL,int qR,int op){
		if(o==null) return 0;
		if(qL<=L&&qR>=R){
			return op==1?o->sum:o->_max;
		}
		int ans=0,M=(L+R)>>1;
		if(qL<=M) {
			if(op==1) ans+=query(o->ch[0],L,M,qL,qR,op);
			else ans=max(ans,query(o->ch[0],L,M,qL,qR,op));
		}
		if(qR>M){
			if(op==1) ans+=query(o->ch[1],M+1,R,qL,qR,op);
			else ans=max(ans,query(o->ch[1],M+1,R,qL,qR,op));
		}
		return ans;
	}
}seg[maxn];

int query_sum(int a,int b,int c){
	//puts("insum");
	int ans=0;
	int ta=tp[a],tb=tp[b];
	while(ta!=tb){
		if(dep[ta]<dep[tb]) swap(a,b),swap(ta,tb);//printf("a:%d b:%d ta:%d tb:%d\n",a,b,ta,tb);
		ans+=seg[c].query(1,n,dfn[ta],dfn[a],1);
		a=fa[tp[a]];ta=tp[a];
	}
	if(dep[a]>dep[b]) swap(a,b);
	ans+=seg[c].query(1,n,dfn[a],dfn[b],1);
//	puts("outsum");
	return ans;
}

int query_max(int a,int b,int c){
	//puts("inmax");
	int ans=0;
	int ta=tp[a],tb=tp[b];
	while(ta!=tb){
		//printf("a:%d b:%d\n",a,b);
		if(dep[ta]<dep[tb]) swap(a,b),swap(ta,tb);
		ans=max(ans,seg[c].query(1,n,dfn[ta],dfn[a],2));
		a=fa[tp[a]];ta=tp[a];
	}
	if(dep[a]>dep[b]) swap(a,b);
	ans=max(ans,seg[c].query(1,n,dfn[a],dfn[b],2));
	//puts("outmax");
	return ans;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	null=new Node();null->ch[0]=null->ch[1]=null;null->sum=null->_max=0;//printf("null:%d\n",null);
	int a,b;
	char op[20];
	scanf("%d%d",&n,&q);//printf("%d %d\n",n,q);
	for(int i=1;i<=n;i++)
		scanf("%d%d",&w[i],&c[i]);//,printf("%d %d\n",w[i],c[i]);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);//,printf("%d %d\n",a,b);

	//puts("fuck");
	fa[1]=1;size[0]=0;dep[1]=1;
	dfs_size(1);
	dfs_clock=0;tp[1]=1;dfs(1);
	
	//for(int i=1;i<=240;i++) printf("fa[%d]:%d tp:%d\n",i,fa[i],tp[i]);
	//printf("fa[240]:%d tp:%d fa[tp]:%d ta:%d\n",fa[240],tp[240],fa[tp[240]],tp[fa[tp[240]]]);return 0;
	for(int i=1;i<=100000;i++) seg[i].build();
	for(int i=1;i<=n;i++)
		seg[c[i]].add(1,n,dfn[i],w[i]);
	
	for(int i=1;i<=q;i++){
		//printf("i:%d\n",i);
		scanf("%s",op);//printf("%s ",op);
		scanf("%d%d",&a,&b);//printf("%d %d\n",a,b);continue;
		if(op[0]=='C'&&op[1]=='C'){
			seg[c[a]].add(1,n,dfn[a],-w[a]);
			seg[b].add(1,n,dfn[a],w[a]);
			c[a]=b;
		}
		else if(op[0]=='C'&&op[1]=='W'){
			seg[c[a]].add(1,n,dfn[a],b-w[a]);
			w[a]=b;
		}
		else if(op[1]=='S') printf("%d\n",query_sum(a,b,c[b]));
		else printf("%d\n",query_max(a,b,c[b]));
	}
	return 0;
}
/*
5 6
3 1
2 3
1 2
3 3
5 1
1 2
1 3
3 4
3 5
QS 1 5
CC 3 1
QS 1 5
CW 3 3
QS 1 5
QM 2 4
*/
