#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,A[maxn];

struct Node{
	int size,bh,val;
	bool rev;
	Node *ch[2],*f;
	Node() {rev=false;}
	void maintain(){size=ch[0]->size+ch[1]->size+1;}
	void pushdown(){if(rev) swap(ch[0],ch[1]),ch[0]->rev^=1,ch[1]->rev^=1,rev=0;}
};
Node *null,seq[maxn];int seq_cnt=0;
Node *num[maxn];

Node *New(int bh,int val) {Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=o->f=null;o->size=1;o->bh=bh;o->val=val;return o;}
int one=0;
struct Splay{
	Node *root;
	
	/*void Rotate(Node* o,int d){
		Node *p=o->ch[!d];
		o->ch[!d]=p->ch[d];
		if(p->ch[d]!=null) p->ch[d]->f=o;
		if(o->f!=null) o->f->ch[o->f->ch[1]==o]=p;
		p->ch[d]=o;p->f=o->f;o->f=p;
		o->maintain();p->maintain();
		if(root==o) root=p;
	}*/
	void Rotate(Node *p){
		int d=p->f->ch[1]==p?0:1;
		Node *o=p->f;
		o->ch[!d]=p->ch[d];p->ch[d]->f=o;
		if(o->f!=null) o->f->ch[o->f->ch[1]==o]=p;
		p->ch[d]=o;
		p->f=o->f;
		o->f=p;
		if(root==o) root=p;
		o->maintain();p->maintain();
	}
	
	void insert(int bh,int val){
		Node *o=root,*last,*now;
		while(o!=null){
			o->size++;
			last=o;
			if(o->bh<bh)o=o->ch[1];
				else o=o->ch[0];
		}
		if(last->bh<bh) last->ch[1]=New(bh,val),now=last->ch[1];
		else last->ch[0]=New(bh,val),now=last->ch[0];
		now->f=last;splay(now,null);num[val]=now;
	}
	
	Node *bigger(Node* o){
		o->pushdown();
		Node *p=o->ch[1];p->pushdown();
		while(p->ch[0]!=null) p=p->ch[0],p->pushdown();
		return p;
	}
	
	void splay(Node* o,Node *fa){//printf("%d\n",o->val);printf("o->f:%d o->f->f:%d\n",o->f->val,o->f->f->val);
		while(o->f!=fa){
			if(o->f->f==fa){
				o->f->pushdown();o->pushdown();Rotate(o);
			}
			else{
				o->f->f->pushdown();o->f->pushdown();o->pushdown();
				Node *p=o->f;int d=p->f->ch[1]==p,dd=p->ch[1]==o;
				if(d==dd)
					Rotate(p),Rotate(o);
				else Rotate(o),Rotate(o);
			}
		}
		o->pushdown();
	}
	
	void print(Node *o){
		if(o==null) return;
		o->pushdown();print(o->ch[0]);//printf("bh:%d val:%d\n",o->bh,o->val);
		print(o->ch[1]);
	}
	
}ss;
struct Duty{
	int pos,val;
	Duty() {}
};
Duty duty[maxn];
bool cmp(Duty A,Duty B){
	return A.val==B.val?A.pos<B.pos:A.val<B.val;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	null=new Node();null->ch[0]=null->ch[1]=null->f=null;null->size=null->bh=null->val=0;null->rev=false;
	scanf("%d",&n);//printf("%d\n",n);
	for(int i=1;i<=n;i++)
		scanf("%d",&duty[i].val),duty[i].pos=i;
	ss.root=New(0,0);num[0]=ss.root;
	ss.root->ch[1]=New(n+1,n+1);num[n+1]=ss.root->ch[1];ss.root->ch[1]->f=ss.root;ss.root->f=null;
	sort(duty+1,duty+n+1,cmp);
	for(int i=1;i<=n;i++)
		ss.insert(duty[i].pos,i);

	for(int i=1;i<=n;i++){
		ss.splay(num[i],null);
		//puts("c");
		Node *p=ss.bigger(num[i]);
		if(i>1) printf(" ");
		printf("%d",ss.root->ch[0]->size);
		ss.splay(num[i-1],null);
		ss.splay(p,num[i-1]);
		p->ch[0]->rev^=1;
		//for(int i=1;i<=n;i++) printf("%d ",num[i]->val);puts("");
		//ss.print(ss.root);
	}puts("");
	return 0;
}
