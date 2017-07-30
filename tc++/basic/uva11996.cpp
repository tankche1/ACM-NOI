# include<stdio.h>
# include<string.h>
# include<algorithm>
# define FUCK printf("fuck\n");
using namespace std;
const int maxn=200010;
const int maxm=200010;
const int x=97;
unsigned pow[maxn+maxm];

void get_pow(){
	pow[0]=1;
	for(int i=1;i<maxn+maxm;i++)
	{pow[i]=pow[i-1]*x;}//printf("%d\n",pow[i]);}
	//printf("fuck\n");
}

struct Node{
	Node* ch[2];
	int v;
	unsigned h1,h2;
	int flip;
	int size;
	
	Node() {}
	
	void maintain(){
		size=ch[0]->size+ch[1]->size+1;
		h1=ch[0]->h1+v*pow[ch[0]->size]+ch[1]->h1*pow[ch[0]->size+1];
		h2=ch[1]->h2+v*pow[ch[1]->size]+ch[0]->h2*pow[ch[1]->size+1];
	}
	
	int cmp(int x){
		if(x==ch[0]->size+1) return -1;
		return x<=ch[0]->size?0:1;
	}
	
	void reserve(){
		swap(h1,h2);
		swap(ch[0],ch[1]);
		flip=!flip;
	}
	
	void pushdown(){
		if(flip){
			flip=0;
			ch[0]->reserve();
			ch[1]->reserve();
		}
	}
};
Node *null;

char s[200010];

void rotate(Node* &o,int d){
	Node *p=o->ch[!d];
	o->ch[!d]=p->ch[d];
	p->ch[d]=o;
	o->maintain();
	p->maintain();
	o=p;
}

void splay(Node* &o,int k){
	o->pushdown();
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->size+1;
	if(d!=-1){
		Node *p=o->ch[d];
		p->pushdown();
		int d2=p->cmp(k);
		int k2=(d2==0?k:k-p->ch[0]->size-1);
		if(d2!=-1){
			splay(p->ch[d2],k2);
			if(d==d2) rotate(o,d^1);else rotate(o->ch[d],d);
		}
		rotate(o,d^1);
	}
}

struct SplayTree{
	Node* root;
	Node seq[maxn+maxm];
	int cnt;
	
	Node* New(int v){
		Node* o=&seq[cnt++];
		o->v=v;o->size=1;
		o->flip=0;
		o->ch[0]=o->ch[1]=null;
		o->h1=o->h2=v;
		return o;
	}
	
	void init(){
		cnt=0;
		root=&seq[cnt++];
	}
	
	Node* build(int L,int R){
		if(L>R) return null;
		int M=(L+R)>>1;
		Node *o=&seq[cnt++];
		o->v=s[M]-'0';o->flip=0;
		o->ch[0]=build(L,M-1);
		o->ch[1]=build(M+1,R);
		o->maintain();
		return o;
	}
	
	Node* &range(int L,int R){//(L,R)
		//print();
		splay(root,L);
		//print();
		splay(root->ch[1],R-L);//print();
		return root->ch[1]->ch[0];
	}
	
	void update_rson_lson(){
		root->ch[1]->maintain();
		root->maintain();
	}
	
	void build(int n){
		root=build(0,n);
	}
	
	void print(Node *o){
		if(o==null) return;
			o->pushdown();
		print(o->ch[0]);
		printf("%d",o->v);
		print(o->ch[1]);
	}
	
	void print(){
		print(root);
		printf("\n");
	}
};
SplayTree ss;

int n,m;
int main(){
	get_pow();
	null=new Node();
	null->size=null->h1=null->h2=null->v=null->flip=0;
	while(scanf("%d%d",&n,&m)!=EOF){
		scanf("%s",s+1);s[0]='0';
		s[n+1]='0';
		ss.init();
		ss.build(n+1);
		//ss.print();
		int op,p,c,p1,p2;
		while(m--){
			scanf("%d",&op);
			if(op==1){
				scanf("%d%d",&p,&c);
				//Node* o=ss.New(c);//ss.root->ch[1]->ch[0]=o;
				ss.range(p+1,p+2)=ss.New(c);
				//ss.print();
				//printf("%d\n",ss.root->ch[1]->ch[0]->v);
				ss.update_rson_lson();
			}
			else if(op==2){
				scanf("%d",&p);
				ss.range(p,p+2)=null;
				ss.update_rson_lson();
			}
			else if(op==3){
				scanf("%d%d",&p1,&p2);
				ss.range(p1,p2+2)->reserve();
				ss.update_rson_lson();
			}
			else{
				scanf("%d%d",&p1,&p2);
				int L=0,R=ss.root->size-2-p2+1;
				while(L<=R){
					int M=(L+R)>>1;
					unsigned h1=ss.range(p1,p1+M+1)->h1;
					//unsigned h2=ss.root->ch[1]->ch[0]->h2;
					h1-=ss.range(p2,p2+M+1)->h1;
					//h2-=ss.root->ch[1]->ch[0]->h2;
				//	if(!h1&&!h2) L=M+1;
					if(!h1) L=M+1;
						else R=M-1;
				}
				printf("%d\n",L-1);
			}
			//ss.print();
		}
	}
	return 0;
}
