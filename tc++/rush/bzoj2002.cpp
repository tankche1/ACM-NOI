# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int maxm=100010;
int k[maxn];
int n,m;
int op,x,y;

struct Node{
	Node *ch[2],*f;
	bool rev;
	int size,bh;
	
	void maintain(){
		size=1+ch[0]->size+ch[1]->size;
	}
};
Node *null;
Node seq[maxn];int seq_cnt=0;

Node *New(int bh){
	Node *o=&seq[seq_cnt++];
	o->size=1;o->bh=bh;
	o->ch[0]=o->ch[1]=o->f=null;o->rev=false;
	return o;
}

bool havef(Node *o){
	return (o->f!=null)&&(o->f->ch[0]==o||o->f->ch[1]==o);
}

void pushdown(Node *o){
	if(o->rev){
		swap(o->ch[0],o->ch[1]);
		o->ch[0]->rev^=1;o->ch[1]->rev^=1;
		o->rev=0;
	}
}

void Rotate(Node *p){
	int d=p->f->ch[0]==p;
	Node *o=p->f;
	o->ch[!d]=p->ch[d];p->ch[d]->f=o;
	if(havef(o)) o->f->ch[o->f->ch[1]==o]=p;
	p->f=o->f;
	p->ch[d]=o;o->f=p;
	o->maintain();p->maintain();
}

void Splay(Node *o){
	Node *p;
	while(havef(o)){
		p=o->f;
		if(havef(p)){
			pushdown(p->f);pushdown(p);pushdown(o);
			p=p->f;
			int d=p->ch[1]==o->f;
			int dd=o->f->ch[1]==o;
			if(d==dd)
				Rotate(o->f),Rotate(o);
			else Rotate(o),Rotate(o);
		}
		else pushdown(p),pushdown(o),Rotate(o);
	}
}

struct LCT{
	Node *tree[maxn];
	
	void Access(Node *x){
		Node *y=null;
		while(x!=null){
			Splay(x);
			pushdown(x);
			x->ch[1]=y;
			x->maintain();
			y=x;
			x=x->f;
		}
	}
	
	void makeroot(Node *x){
		Access(x);
		Splay(x);
		x->rev^=1;
	}
	
	void Link(Node *x,Node *y){
		makeroot(x);
		x->f=y;
		Access(x);
	}
	
	void Cut(Node *x,Node *y){
		Access(x);
		Splay(y);
		if(y->f==x){
			y->f=null;
		}
		else {
			Access(y);
			Splay(x);
			if(x->f==y){
				x->f=null;
			}
		}
	}
	
	int query(Node *x){
		makeroot(tree[n+1]);
		Access(x);
		Splay(x);
		return x->size;
	}
};
LCT lct;

int main(){
	//freopen("input.txt","r",stdin);
	null=new Node();null->size=0;
	scanf("%d",&n);
	for(int i=1;i<=n;i++){
		lct.tree[i]=New(i),scanf("%d",&k[i]);if(i+k[i]>n) k[i]=n+1-i;
	}
	lct.tree[n+1]=New(n+1);
	for(int i=1;i<=n;i++)
	lct.Link(lct.tree[i],lct.tree[i+k[i]]);
	scanf("%d",&m);
	for(int i=1;i<=m;i++){
		scanf("%d",&op);
		if(op==1){
			scanf("%d",&x);x++;
			printf("%d\n",lct.query(lct.tree[x])-1);
		}
		else{
			scanf("%d%d",&x,&y);x++;
			lct.Cut(lct.tree[x],lct.tree[x+k[x]]);//puts("CUT");
			k[x]=x+y>n?n+1-x:y;
			lct.Link(lct.tree[x],lct.tree[x+k[x]]);
		}
	}
	return 0;
}
