# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=30010;
const int INF=1<<29;
int n;

struct Node{
	int label,path_parent;//维护链上根节点的path_parent
	Node *ch[2],*parent;
	int Max,sum,w,v;
	
	Node(){}
	
	Node(int label,int w,int v):label(label),w(w),v(v){
		sum=Max=w;
	}
	
	void maintain(){
		Max=max(ch[0]->Max,ch[1]->Max);
		Max=max(Max,w);
		sum=w+ch[0]->sum+ch[1]->sum;
	}
};
Node *null;
Node *tree[maxn];

void rotate(Node* &o,int d){
	Node *p=o->ch[!d];p->path_parent=o->path_parent;int dd=o->parent->ch[0]==o?0:1;o->parent->ch[dd]=p;
	o->ch[!d]=p->ch[d];p->ch[d]->parent=o;p->ch[d]=o;p->parent=o->parent;o->parent=p;o->maintain();o=p;o->maintain();
}

void splay(Node* &o){
	while(o->parent!=null){
		int d=o->parent->ch[0]==o?0:1;
		Node *p=(o->parent);
		if(o->parent->parent==null){
			rotate(p,!d);
		}
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
	o->maintain();
}

bool vis[maxn];
void print(Node *x){
	if(x==null) return;
		vis[x->label]=1;
		print(x->ch[0]);
	printf(" %d",x->label);
	print(x->ch[1]);
}
void print(){
	memset(vis,false,sizeof(vis));
	for(int i=1;i<=n;i++)
		if(!vis[i]) {splay(tree[i]);printf("new: ");print(tree[i]);printf("\n");}
}

Node* prev(Node *u){
	splay(u);
	if(u->ch[0]==null) return u;
	u=u->ch[0];
	while(u->ch[1]!=null) u=u->ch[1];
	return u;
}

void Access(Node* u){
	//printf("access:%d\n",u->label);
	Node *v=null;
	do{
		splay(u);
		if(u->ch[1]!=null){
		u->ch[1]->path_parent=u->label;
		u->ch[1]->parent=null;
		}
		u->ch[1]=v;
		if(v!=null) {v->parent=u;}
		u->maintain();
		v=u;
		u=tree[u->path_parent];
	}while(v->path_parent!=0);
	//print();
}

int lca(Node *a,Node *b){
	if(a==b) return a->label;
	if(a->v>b->v) swap(a,b);
	Access(a);//print();
	Access(b);//print();
	splay(a);
	int p=a->path_parent;
	return p==0?a->label:p;
}

int qmax(int a,int b){
	int p=lca(tree[a],tree[b]);
	//printf("a:%d b:%d p:%d\n",a,b,p);
	//print();
	Access(tree[a]);//print();
	Access(tree[b]);
	Node* pa=prev(tree[p]);
	if(tree[p]->label!=1)
		Access(pa);
	splay(tree[a]);
	splay(tree[b]);
	//printf("%d %d\n",tree[a]->Max,tree[b]->Max);
	int ans=max(tree[a]->Max,tree[b]->Max);
	return ans;
}

Node* root(Node *o){
	while(o->parent!=null) o=o->parent;
	return o;
}

int qsum(int a,int b){
	int p=lca(tree[a],tree[b]);
	Access(tree[a]);
	Access(tree[b]);
	Node* pa=prev(tree[p]);
	if(tree[p]->label!=1)
		Access(pa);
	splay(tree[a]);
	int ans=tree[a]->sum;
	if(root(tree[b])!=tree[a]){
		splay(tree[b]);
		ans+=tree[b]->sum;
	}
	return ans;
}

void change(int o,int nw){
	splay(tree[o]);
	tree[o]->w=nw;
	tree[o]->maintain();
}

int a,b;
int first[maxn],next[maxn*2],v[maxn*2],edge,w[maxn];
void add_edge(int a,int b) {next[edge]=first[a];v[edge]=b;first[a]=edge++;}

void build(int o,int dep,int fa){
	//printf("o:%d dep:%d fa:%d\n",o,dep,fa);
	tree[o]=new Node(o,w[o],dep);
	tree[o]->path_parent=fa;tree[o]->parent=tree[o]->ch[0]=tree[o]->ch[1]=null;
	for(int e=first[o];e!=-1;e=next[e]){
		if(v[e]!=fa)
		build(v[e],dep+1,o);
	}
}



int main(){
	null=new Node();
	null->ch[0]=null->ch[1]=NULL;null->w=null->sum=0;null->Max=-INF;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	for(int i=1;i<=n;i++) scanf("%d",&w[i]);
	build(1,1,0);
	char op[20];int q,x,y;
	scanf("%d",&q);
	//print();
	while(q--){
		scanf("%s%d%d",op,&x,&y);
		if(op[0]=='C'){
			change(x,y);
		}
		else if(op[1]=='M'){
			printf("%d\n",qmax(x,y));
		}
		else{
			printf("%d\n",qsum(x,y));
		}
		//print();
	}
	return 0;
}
/*
4

1 2

2 3

4 1

4 2 1 3

12
QMAX 3 2
*/
