#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxlen=2*1050*1050;
int n,m;
int cur=0;
char s[maxlen];

struct Node{
	char t;
	int size;
	bool rev;
	Node *ch[2];
	int cmp(int x){if(x==ch[0]->size+1) return -1;return x<=ch[0]->size?0:1;}
	
	Node(){}
	void maintain(){size=ch[0]->size+1+ch[1]->size;}
	void pushdown() {
		if(rev){
			swap(ch[0],ch[1]);
			ch[0]->rev^=1;ch[1]->rev^=1;
			rev=false;
		}
	}
	//Node(char t,int size,bool rev) {}
};
Node *null;
Node seq[maxlen];int seq_cnt=0;

Node *New(char t){
	Node *o=&seq[seq_cnt++];
	o->ch[0]=o->ch[1]=null;o->t=t;o->rev=false;o->size=1;
	return o;
}

struct SplayTree{
	Node *root;
	
	Node *build(int L,int R){
		int M=(L+R)>>1;
		Node *o=New(s[M]);
		if(L==R) return o;
		if(L<M) o->ch[0]=build(L,M-1);
		if(R>M) o->ch[1]=build(M+1,R);
		o->maintain();
		return o;
	}
	
	void Rotate(Node* &o,int d){
		Node *p=o->ch[!d];
		o->ch[!d]=p->ch[d];
		p->ch[d]=o;
		o->maintain();p->maintain();
		if(root==o) root=p;
		o=p;
		return;
	}
	
	void Splay(Node* &o,int k){
		o->pushdown();
		int d=o->cmp(k);
		if(d==-1) return;
		o->ch[d]->pushdown();
		if(d) k-=o->ch[0]->size+1;
		int dd=o->ch[d]->cmp(k);if(dd) k-=o->ch[d]->ch[0]->size+1;
		if(dd==-1)
			Rotate(o,!d);
		else{
			Splay(o->ch[d]->ch[dd],k);
			if(d==dd){
				Rotate(o,!d);Rotate(o,!d);
			}
			else Rotate(o->ch[d],!dd),Rotate(o,!d);
		}
	}
	
	void getrange(int L,int R){
		Splay(root,L);
		Splay(root->ch[1],R-L);
	}
	
	void update_mummy(){
		root->ch[1]->maintain();root->maintain();
	}
}ss;

int main(){
	null=new Node();null->size=0;null->ch[0]=null->ch[1]=NULL;
	char op[20];
	scanf("%d",&n);
	s[0]=s[2]='a';s[1]=' ';s[3]='\0';
	ss.root=ss.build(0,2);
	while(n--){
		//printf("n:%d\n",n);
		scanf("%s",op);
		if(op[0]=='M')
			scanf("%d\n",&cur);
		else if(op[0]=='P') cur--;
		else if(op[0]=='N') cur++;
		else if(op[0]=='I'){
			scanf("%d\n",&m);
			gets(s);//puts(s);
			ss.getrange(cur+1,cur+2);
			ss.root->ch[1]->ch[0]=ss.build(0,m-1);
			ss.update_mummy();
			//printf("ss.root:%d\n",ss.root->size);
		}
		else if(op[0]=='D'){
			scanf("%d\n",&m);
			ss.getrange(cur+1,cur+m+2);
			ss.root->ch[1]->ch[0]=null;
			ss.update_mummy();
		}
		else if(op[0]=='R'){
			scanf("%d\n",&m);
			ss.getrange(cur+1,cur+m+2);
			ss.root->ch[1]->ch[0]->rev^=1;
		}
		else if(op[0]=='G'){
			if(cur==ss.root->size-2) printf(" \n");
			else{
			ss.Splay(ss.root,cur+2);
			printf("%c\n",ss.root->t);
			}
		}
	}
	return 0;
}
