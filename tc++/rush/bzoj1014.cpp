# include<stdio.h>
# include<string.h>
# include<algorithm>
# define FUCK printf("fuck\n");
using namespace std;
const int maxn=100010;
const int maxm=150010;
const int x=97;
char s[maxn];
unsigned pow[maxn+maxm];

void getpow(){
	pow[0]=1;
	for(int i=1;i<maxn+maxm;i++)
	pow[i]=pow[i-1]*x;
}

struct Node{
	int v;
	int size;
	Node *ch[2];
	unsigned h;
	
	Node() {}
	
	void maintain(){
		size=1+ch[0]->size+ch[1]->size;
		h=ch[0]->h+v*pow[ch[0]->size]+ch[1]->h*pow[ch[0]->size+1];
	}
	
	int cmp(int k){
		if(k==ch[0]->size+1) return -1;
		return k<=ch[0]->size?0:1;
	}
};
Node *null;

void rotate(Node* &o,int d){
	Node *p=o->ch[!d];o->ch[!d]=p->ch[d];p->ch[d]=o;
	o->maintain();p->maintain();o=p;
}

void splay(Node* &o,int k){
	int d=o->cmp(k);
	if(d==1) k-=o->ch[0]->size+1;
	if(d!=-1){
		Node *p=o->ch[d];
		int d2=p->cmp(k);
		if(d2!=-1){
			int k2=d2==0?k:k-p->ch[0]->size-1;
			splay(p->ch[d2],k2);
			if(d2==d) rotate(o,!d); else rotate(o->ch[d],!d2);
		}
		rotate(o,!d);
	}
}

struct SplayTree{
	Node seq[maxn+maxm];
	Node *root;
	int cnt;
	
	void init(){
		cnt=0;
		root=&seq[cnt++];
	}
	
	Node* build(int L,int R){
		//printf("L：%d R:%d\n",L,R);
		if(L>R) return null;
		int M=(L+R)>>1;
		Node *o=&seq[cnt++];
		o->v=s[M]-'a';
		o->ch[0]=build(L,M-1);
		o->ch[1]=build(M+1,R);
		o->maintain();
		return o;
	}
	
	void build(int n){
		root=build(0,n);
	}
	
	Node* New(int v){
		Node *o=&seq[cnt++];
		o->size=1;o->v=v;o->h=v;
		o->ch[0]=o->ch[1]=null;
		return o;
	}
	
	Node* &range(int L,int R){//root=L root->ch[1]=R
		splay(root,L);
		splay(root->ch[1],R-L);
		return root->ch[1]->ch[0];
	}
	
	void update_rson_lson(){
		root->ch[1]->maintain();root->maintain();
	}
	
	void print(Node *o){
		if(o==null) return;
			print(o->ch[0]);printf("%c",'a'+o->v);
		print(o->ch[1]);
	}
	
	void print(){
		print(root);printf("\n");
	}
};
SplayTree ss;

char op[10];
int m,n;
int main(){
	getpow();
	null=new Node();
	null->size=0;null->ch[0]=null->ch[1]=NULL;
	null->v=0;null->h=0;
	scanf("%s",s+1);
	s[0]='a';n=strlen(s);//printf("n:%d\n",n);
	s[n]='a';int len=n-1;
	scanf("%d",&m);
	ss.init();
	ss.build(n);
	int x,y;char d;
	while(m--){
		scanf("%s",op);scanf("%d",&x);
		if(op[0]=='I'){ 
			while((d=getchar())&&(!(d>='a'&&d<='z')));
			ss.range(x+1,x+2)=ss.New(d-'a');
			ss.update_rson_lson();len++;
		}
		else if(op[0]=='R'){
			while((d=getchar())&&(!(d>='a'&&d<='z')));
			ss.range(x,x+2);ss.root->ch[1]->ch[0]->h=ss.root->ch[1]->ch[0]->v=d-'a';
			ss.update_rson_lson();
		}
		else{//FUCK
			scanf("%d",&y);if(x>y) swap(x,y);
			int L=0,R=ss.root->size-2-y+1;
			while(L<=R){
				int M=(L+R)>>1;
				unsigned h=ss.range(x,x+M+1)->h;//printf("h:%d\n",h);
				h-=ss.range(y,y+M+1)->h;
				if(!h) L=M+1;
					else R=M-1;
			}
			printf("%d\n",L-1);
		}
		//ss.print();
	}
	return 0;
}

/*
madamimadam
7
*/
