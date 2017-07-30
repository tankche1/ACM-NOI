# include<stdio.h>
# include<string.h>
# include<algorithm>
# define FUCK printf("fuck\n");
using namespace std;
const int INF=1<<29;
const int maxn=30005;

struct Node{
	Node *ch[2],*parent;
	int label,w,sum,Max,path_parent,v;
	
	Node() {}
	
	Node(int label,int w,int v):label(label),w(w),v(v){sum=Max=w;}
	
	void maintain(){
		sum=w+ch[0]->sum+ch[1]->sum;
		Max=max(ch[0]->Max,ch[1]->Max);
		Max=max(Max,w);
	}
};
Node *null;
Node seq[maxn];

void rotate(Node* &o,int d){
	Node *p=o->ch[!d];p->path_parent=o->path_parent;int dd=o->parent->ch[0]==o?0:1;o->parent->ch[dd]=p;
	p->parent=o->parent;o->ch[!d]=p->ch[d];p->ch[d]->parent=o;p->ch[d]=o;p->parent=o->parent;o->parent=p;
	o->maintain();o=p;o->maintain();
}

void splay(Node* &o){
	while(o->parent!=null){
		int d=o->parent->ch[0]==o?0:1;
		Node *p=o->parent;
		if(o->parent->parent==null)
		rotate(p,d^1);
		else{
			int dd=p->parent->ch[0]==p?0:1;
			if(d==dd){
				Node *q=p->parent;
				rotate(q,!dd);
				rotate(q,!d);
			}
			else{
				rotate(p,!d);
				Node *q=p->parent;
				rotate(q,!dd);
			}
		}
	}
	//o->maintain();
}

int n;
int w[maxn];
int first[maxn],next[2*maxn],v[2*maxn],edge;
struct LCT{
	Node *tree[maxn];
	
	void build(int x,int dep,int fa){
		tree[x]=&seq[x];
		seq[x]=Node(x,w[x],dep);
		tree[x]->ch[0]=tree[x]->ch[1]=tree[x]->parent=null;
		tree[x]->path_parent=fa;
		for(int e=first[x];e!=-1;e=next[e]){
			if(v[e]!=fa){
				build(v[e],dep+1,x);
			}
		}
	}
	
	void Access(Node *u){
		Node *v=null;
		do{
			splay(u);
			if(u->ch[1]!=null) {
				u->ch[1]->parent=null;
				u->ch[1]->path_parent=u->label;
			}
			u->ch[1]=v;
			if(v!=null){
				v->parent=u;
			}
			u->maintain();
			v=u;
			u=tree[u->path_parent];
		}while(v->path_parent!=0);
	}
	
	int lca(Node *a,Node *b){
		if(a==b) return a->label;
		if(a->v>b->v) swap(a,b);
		Access(a);
		Access(b);
		splay(a);
		if(a->path_parent==0)
			return a->label;
		return a->path_parent;
	}
	
	void change(int x,int y){
		splay(tree[x]);
		tree[x]->w=y;
		tree[x]->maintain();
	}
	
	Node* prev(int x){
		splay(tree[x]);
		if(tree[x]->ch[0]==null) return tree[x];
		x=tree[x]->ch[0]->label;
		while(tree[x]->ch[1]!=null)
			x=tree[x]->ch[1]->label;
		return tree[x];
	}
	
	int qmax(int x,int y){
		int p=lca(tree[x],tree[y]);//printf("a:%d b:%d p:%d\n",x,y,p);
		Access(tree[x]);
		Access(tree[y]);
		//splay(tree[p]);
		if(p!=1)
		Access(prev(p));
		splay(tree[x]);
		splay(tree[y]);
		return max(tree[x]->Max,tree[y]->Max);
	}
	
	Node* root(Node *x){
		while(x->parent!=null) x=x->parent;
			return x;
	}
	
	int qsum(int a,int b){
		int p=lca(tree[a],tree[b]);
		Access(tree[a]);
		Access(tree[b]);
		//splay(tree[p]);
		if(p!=1)
			Access(prev(p));
		splay(tree[a]);
		if(root(tree[b])!=tree[a]){
			splay(tree[b]);
			return tree[a]->sum+tree[b]->sum;
		}
		return tree[a]->sum;
	}
	
};
LCT lct;

void add_edge(int a,int b){next[edge]=first[a];v[edge]=b;first[a]=edge++;}

int main(){
	char op[20];
	int a,b,q,x,y;
	null=new Node();
	null->sum=null->w=0;
	null->Max=-INF;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));
	edge=0;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&w[i]);
	lct.build(1,1,0);
	scanf("%d",&q);
	while(q--){
		scanf("%s%d%d",op,&x,&y);
		if(op[0]=='C'){
			lct.change(x,y);
		}
		else if(op[1]=='M')
			printf("%d\n",lct.qmax(x,y));
		else printf("%d\n",lct.qsum(x,y));
	}
	return 0;
}
