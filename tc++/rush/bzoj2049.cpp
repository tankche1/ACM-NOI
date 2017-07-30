# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n,m;

struct Node{
	int size;
	bool rev;
	Node *parent,*ch[2];
	Node(){}
	void maintain(){
		size=1+ch[0]->size+ch[1]->size;
	}
	void clear(){
		if(rev){
			ch[0]->rev^=1;ch[1]->rev^=1;
			swap(ch[0]->ch[0],ch[0]->ch[1]);swap(ch[1]->ch[0],ch[1]->ch[1]);
			rev=false;
		}
	}
};
Node *null;
Node seq[maxn];int seq_cnt=0;
Node *New(){
	Node *o=&seq[++seq_cnt];o->size=1;
	o->ch[0]=o->ch[1]=o->parent=null;o->rev=false;
	return o;
}

inline bool splay_parent(Node *x,Node* &y){
	return ((y=x->parent)!=null)&&(y->ch[0]==x||y->ch[1]==x);
}

inline void Rotate(Node* &o,int d){
	Node *y;
	Node *p=o->ch[!d];
	o->ch[!d]=p->ch[d];p->ch[d]->parent=o;
	if(splay_parent(o,y)) y->ch[y->ch[0]==o?0:1]=p;
	p->ch[d]=o;p->parent=o->parent;o->parent=p;
	
	o->maintain();p->maintain();
	//printf("osize:%d psize:%d\n",o->size,p->size);
	o=p;
}

struct LCT{
	Node *tree[maxn];
	
	inline void splay(Node *o){
	o->clear();
	//for(int i=0;i<200;i++) if(tree[i]==o) printf("o:%d\n",i);
	for(Node *y,*z;splay_parent(o,y);){
		//for(int i=0;i<200;i++) if(tree[i]==y) printf("y:%d\n",i);
		if(splay_parent(y,z)){
			z->clear();y->clear();o->clear();
		//	for(int i=0;i<200;i++) if(tree[i]==z) printf("z:%d\n",i);
			int d=z->ch[0]==y?0:1;int dd=y->ch[0]==o?0:1;
			if(d==dd) Rotate(z,!dd),Rotate(z,!dd);
				else Rotate(y,!dd),Rotate(z,!d);
		}
		else{
			y->clear();o->clear();
			int dd=y->ch[0]==o?0:1;
			Rotate(y,!dd);
		}
	}
}


	void build(){
		for(int i=1;i<=n;i++) tree[i]=New();
	}
	
	void Access(Node *u){
		Node *v=null;
		for(;u!=null;u=u->parent){
			splay(u);
			u->ch[1]=v;
			u->maintain();v=u;
		}
	}
	
	void makeroot(Node *u){
		Access(u);splay(u);swap(u->ch[0],u->ch[1]);u->rev^=1;u->clear();
	}
	
	void Link(Node *u,Node *v){
		makeroot(u);u->parent=v;Access(u);
	}
	
	void Cut(Node *u,Node *v){
		
		makeroot(u);Access(v);splay(v);//for(int i=0;i<200;i++) if(v==tree[i]) printf("v:%d\n",i);
		//	for(int i=0;i<200;i++) if(v->ch[0]==tree[i]) printf("v:%d\n",i);
		//	printf("%d\n",v->size);printf("%d\n",v->ch[0]->size);
		v->ch[0]->parent=null;v->ch[0]=null;v->maintain();//printf("%d\n",v->size);
	}
	
	void Query(Node *a,Node *b){
		//for(int i=0;i<200;i++) if(a==tree[i]) printf("a:%d\n",i);
		//	for(int i=0;i<200;i++) if(b==tree[i]) printf("b:%d\n",i);
		while(a->parent!=null) a=a->parent;
		while(b->parent!=null) b=b->parent;
		//		for(int i=0;i<200;i++) if(a==tree[i]) printf("a:%d\n",i);
		//	for(int i=0;i<200;i++) if(b==tree[i]) printf("b:%d\n",i);
		if(a==b) puts("Yes");
			else puts("No");
	}
};
LCT lct;

int main(){
	null=new Node();null->parent=null->ch[0]=null->ch[1]=NULL;null->size=0;
	int a,b;char op[20];
	scanf("%d%d",&n,&m);
	lct.build();
	while(m--){
		scanf("%s",op);scanf("%d%d",&a,&b);
		if(op[0]=='C') lct.Link(lct.tree[a],lct.tree[b]);
			else if(op[0]=='D') lct.Cut(lct.tree[a],lct.tree[b]);
				else lct.Query(lct.tree[a],lct.tree[b]);
	}
	return 0;
}
