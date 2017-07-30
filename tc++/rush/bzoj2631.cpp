# include<cstdio>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int mod = 51061;
typedef unsigned int ui;
int n,m;

inline int readint(){
	int tmp;scanf("%d",&tmp);return tmp;
}

inline char readchar(){
	char ch;
	while((ch=getchar())&&ch!='+'&&ch!='-'&&ch!='*'&&ch!='/');
	return ch;
}

int first[maxn],next[maxn<<1],v[maxn<<1],edge;

void add_edge(int a,int b){
	next[edge]=first[a];
	first[a]=edge;
	v[edge++]=b;
}

struct Node{
	ui sum,size,val,add,mul;
	bool rev;
	Node *ch[2],*parent;
	
	Node() {}
	
	void clear_mul(ui m){
		sum=sum*m%mod;
		val=val*m%mod;
		add=add*m%mod;
		mul=mul*m%mod;
	}
	
	void clear_add(ui m){
		sum=(sum+(long long)size*m)%mod;
		val=(val+m)%mod;
		add=(add+m)%mod;
	}
	
	void maintain(){
		size=ch[0]->size+1+ch[1]->size;
		sum=(val+ch[0]->sum+ch[1]->sum)%mod;
	}
	
};
Node *null;
Node seq[maxn];int seq_cnt=0;
Node *New(){
	Node *o=&seq[++seq_cnt];
	o->val=o->sum=o->size=1;o->ch[0]=o->ch[1]=null;o->mul=1;o->add=0;
	o->rev=false;
	return o;
}

void clear(Node* const x){
	if(x==null) return;
		if(x->rev){
			x->ch[0]->rev=!x->ch[0]->rev;x->ch[1]->rev=!x->ch[1]->rev;
			swap(x->ch[0]->ch[0],x->ch[0]->ch[1]);swap(x->ch[1]->ch[0],x->ch[1]->ch[1]);
			x->rev=false;
		}
		if(x->mul!=1){
			x->ch[0]->clear_mul(x->mul);
			x->ch[1]->clear_mul(x->mul);
			x->mul=1;
		}
		if(x->add){
			x->ch[0]->clear_add(x->add);
			x->ch[1]->clear_add(x->add);
			x->add=0;
		}
}

inline bool splay_parent(Node *x,Node* &y){
	return ((y=x->parent)!=null)&&(y->ch[0]==x||y->ch[1]==x);
}

inline void Rotate(Node* &o,int d){
	Node *y;
	Node *p=o->ch[!d];o->ch[!d]=p->ch[d];//if(p->ch[d]!=null) 
	p->ch[d]->parent=o;
	if(splay_parent(o,y)) o->parent->ch[o->parent->ch[0]==o?0:1]=p;//不然会影响splay_parent的判断
	p->ch[d]=o;p->parent=o->parent;o->parent=p;
	o->maintain();p->maintain();
	o=p;
}

	inline void splay(Node *o){
	clear(o);//这个很重要 因为Access中有改变的行为 标记会传错
		//for(int i=0;i<100;i++) if(tree[i]==o) printf("o:%d\n",i);
	for(Node *y,*z;splay_parent(o,y);){
		//for(int i=0;i<100;i++) if(tree[i]==y) printf("y:%d\n",i);
		if(splay_parent(y,z)){
			clear(z);clear(y);clear(o);int dd=y->ch[0]==o?0:1;
			//for(int i=0;i<100;i++) if(tree[i]==z) printf("z:%d\n",i);
			int d=z->ch[0]==y?0:1;
			if(d==dd) Rotate(z,!d),Rotate(z,!d);
				else Rotate(y,!dd),Rotate(z,!d);
		}
		else{
			clear(y);clear(o);int dd=y->ch[0]==o?0:1;
			Rotate(y,!dd);
		}
	}
}

struct LCT{
	Node *tree[maxn];

	inline Node* Access(Node *u){
		Node *v=null;
		for(;u!=null;u=u->parent){
			splay(u);//printf("accsize:%d\n",u->size);
			u->ch[1]=v;//printf("a");for(int i=0;i<100;i++) if(u==tree[i]) printf("%d\n",i);
			u->maintain();v=u;//printf("shitcsize:%d\n",u->size);
		}
		return v;
	}
	
	void make_root(Node *x){
		Access(x);
		splay(x);swap(x->ch[0],x->ch[1]);x->rev^=1;clear(x);
	}
	
	inline void link(Node *a,Node *b){
		make_root(b);b->parent=a;Access(b);
	}
	
	inline void cut(Node *a,Node *b){
		make_root(a);Access(b);
		splay(b);b->ch[0]->parent=null;b->ch[0]=null;b->maintain();
	}
	
	void make_tree(int x,int fa){
		tree[x]=New();tree[x]->parent=tree[fa];//printf("x:%d\n",x);
		for(int e=first[x];e!=-1;e=next[e]){
			if(v[e]==fa) continue;
			make_tree(v[e],x);
		}
	}
	
	inline void add(Node *a,Node *b,int val){
		make_root(a);
		Access(b);
		splay(b);
		b->clear_add(val);//printf("size:%d sum:%d\n",b->size,b->sum);
	}
	
	inline void mul(Node *a,Node *b,int val){
		make_root(a);
		Access(b);
		splay(b);
		b->clear_mul(val);
	}
	
	inline void query(Node *a,Node *b){
		make_root(a);//printf("size:%d\n",a->size);
		Access(b);//printf("size:%d\n",a->size);
		splay(b);//printf("size:%d\n",b->size);
		printf("%d\n",b->sum);
	}
	
};
LCT lct;

int main(){
	//fread(_stdin,1,BUFSIZE,stdin);
	//freopen("input.txt","r",stdin);
	char op;null=new Node();
	null->parent=null->ch[0]=null->ch[1]=NULL;null->sum=null->size=0;lct.tree[0]=null;
	n=readint();m=readint();//printf("%d %d\n",n,m);
	int a,b,c,d;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		a=readint(),b=readint(),add_edge(a,b),add_edge(b,a);
	lct.make_tree(1,0);
	while(m--){
		op=readchar();
		//printf("%c\n",op);
		if(op=='+'){//puts("s");
			a=readint();b=readint();c=readint();
			lct.add(lct.tree[a],lct.tree[b],c);
		}
		else if(op=='-'){//puts("sh");
			a=readint();b=readint();c=readint();d=readint();
			lct.cut(lct.tree[a],lct.tree[b]);lct.link(lct.tree[c],lct.tree[d]);
		}
		else if(op=='*'){//puts("shi");
			a=readint();b=readint();c=readint();
			lct.mul(lct.tree[a],lct.tree[b],c);
		}
		else{//puts("shit");
			a=readint();b=readint();
			lct.query(lct.tree[a],lct.tree[b]);
		}
	}
	return 0;
}
