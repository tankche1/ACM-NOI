#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int mod=20130426;
typedef long long LL;
int RR=100002;
int n;
inline void Add(int &x,int v){x=(x+v)%mod;}
inline void Mul(int &x,int v){x=(LL)x*v%mod;}
int ans,pow[maxn];

struct Node{
	int val,size,add,mul;
	Node *ch[2];
	
	void maintain(){size=ch[0]->size+1+ch[1]->size;}
	int cmp(int x) {if(x==ch[0]->size+1) return -1;return x<=ch[0]->size?0:1;}
	void pushdown(){
		if(mul!=1){
			Mul(ch[0]->val,mul);Mul(ch[1]->val,mul);
			Mul(ch[0]->add,mul);Mul(ch[1]->add,mul);
			Mul(ch[0]->mul,mul);Mul(ch[1]->mul,mul);
			mul=1;
		}
		if(add){
			Add(ch[0]->val,add);Add(ch[1]->val,add);
			Add(ch[0]->add,add);Add(ch[1]->add,add);
			add=0;
		}
	}
};
Node *null;
Node seq[maxn<<1];int seq_cnt=0;

Node* New(int val){
	Node *o=&seq[seq_cnt++];
	o->ch[0]=o->ch[1]=null;
	o->val=val;o->size=1;o->add=0;o->mul=1;
	return o;
}

struct SplayTree{
	Node *root;
	
	Node *build(int L,int R){
		Node *o;
		int M=(L+R)>>1;
		o=New(0);
		if(L<M) o->ch[0]=build(L,M-1);
		if(M<R) o->ch[1]=build(M+1,R);
		o->maintain();
		return o;
	}
	
	void Rotate(Node* &o,int d){
		Node *p=o->ch[!d];
		o->ch[!d]=p->ch[d];
		p->ch[d]=o;
		o->maintain();p->maintain();
		if(o==root) root=p;
		o=p;
	}
	
	void Splay(Node* &o,int k){
		o->pushdown();
		int d=o->cmp(k);
		if(d==-1) return;
		o->ch[d]->pushdown();
		if(d) k-=o->ch[0]->size+1;
		int dd=o->ch[d]->cmp(k);
		if(dd) k-=o->ch[d]->ch[0]->size+1;
		if(dd==-1){
			Rotate(o,!d);return;
		}
		else{
			Splay(o->ch[d]->ch[dd],k);
			if(d==dd)
				Rotate(o,!d),Rotate(o,!d);
			else
				Rotate(o->ch[d],!dd),Rotate(o,!d);
		}
	}
	
	void Range(int L,int R){
		Splay(root,L);
		Splay(root->ch[1],R-L);
	}
	
	void update_mummy(){
		root->ch[1]->maintain();
		root->maintain();
	}
	
	void cal(Node *o,int num){
		if(o==null) return;
		o->pushdown();
		//printf("%d\n",o->val);
		Add(ans,(LL)o->val*pow[num+o->ch[0]->size]%mod);
		cal(o->ch[0],num);
		cal(o->ch[1],num+1+o->ch[0]->size);
	}
	
}ss;

int main(){
	null=new Node();null->size=0;null->ch[0]=null->ch[1]=NULL;
	char op[20];
	int L,R,v;
	scanf("%d",&n);
	ss.root=ss.build(1,RR+2);
	while(n--){
		scanf("%s",op);
			if(op[0]=='m'&&op[3]=='x'){
			scanf("%d%d",&L,&R);
			ss.Range(L+2-1,L+2);
			ss.root->ch[1]->ch[0]=ss.build(1,1);
			ss.update_mummy();
			ss.Range(R+2-1+1,R+2+1+1);
			Add(ss.root->ch[1]->val,ss.root->ch[1]->ch[0]->val);ss.root->ch[1]->ch[0]=null;
			ss.update_mummy();
		}
		else if(op[0]=='m'){
			scanf("%d%d%d",&L,&R,&v);
			ss.Range(L+2-1,R+2+1);
			Mul(ss.root->ch[1]->ch[0]->val,v);
			Mul(ss.root->ch[1]->ch[0]->add,v);
			Mul(ss.root->ch[1]->ch[0]->mul,v);
			//ss.update_mummy();
		}
		else if(op[0]=='a'){
			scanf("%d%d%d",&L,&R,&v);
			ss.Range(L+2-1,R+2+1);
			Add(ss.root->ch[1]->ch[0]->add,v);
			Add(ss.root->ch[1]->ch[0]->val,v);
			//ss.update_mummy();
		}
		else{
			scanf("%d",&v);
			ans=0;
			pow[0]=1;
			for(int i=1;i<=RR;i++)
				pow[i]=(LL)pow[i-1]*v%mod;
			ss.Range(1,RR+2);
			ss.root->pushdown();
			ss.root->ch[1]->pushdown();
			ss.cal(ss.root->ch[1]->ch[0],0);
			printf("%d\n",ans);
		}
	}
	return 0;
}
