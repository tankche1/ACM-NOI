# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=(1e+9)+10;
int n,m;
int A[maxn];

struct Node{
	Node *ch[2];
	int size,val,maxs,maxl,maxr,sum;
	Node() {}
	Node(int size,int val):size(size),val(val) {sum=maxs=maxl=maxr=val;}
	void update(){
		size=ch[0]->size+ch[1]->size+1;
		maxs=max(max(max(max(max(ch[0]->maxs,ch[1]->maxs),ch[0]->maxr+val),ch[0]->maxr+val+ch[1]->maxl),val+ch[1]->maxl),val);
		maxl=max(max(ch[0]->maxl,ch[0]->sum+val),ch[0]->sum+val+ch[1]->maxl);
		maxr=max(max(ch[1]->maxr,ch[1]->sum+val),ch[1]->sum+val+ch[0]->maxr);
		sum=val+ch[0]->sum+ch[1]->sum;
	}
	int cmp(int x) {if(x==ch[0]->size+1) return -1;return x<=ch[0]->size?0:1;}
};
Node *null;
Node seq[maxn<<1];int seq_cnt=0;

Node *New(int val){
	Node *o=&seq[seq_cnt++];
	o->size=1;
	o->val=o->maxs=o->maxl=o->maxr=o->sum=val;
	o->ch[0]=o->ch[1]=null;
	return o;
}

struct Splay{
	Node *root;
	
	void init(){
		root=New(0);root->ch[1]=New(0);
		root->update();
	}
	
	void Rotate(Node* &o,int d){
		Node *p=o->ch[!d];
		o->ch[!d]=p->ch[d];p->ch[d]=o;
		o->update();p->update();
		if(o==root) root=p;
		o=p;
	}
	
	void splay(Node* &o,int k){
		int d=o->cmp(k);
		if(d!=-1){
			Node *p=o->ch[d];
			if(d) k-=o->ch[0]->size+1;
			int dd=p->cmp(k);
			if(dd!=-1){
				int kk=dd==1?k-p->ch[0]->size-1:k;
				splay(p->ch[dd],kk);
				if(d==dd)
					Rotate(o,!d);
				else Rotate(o->ch[d],!dd);
			}
			Rotate(o,!d);
		}
	}
	
	void print(Node *o){
		if(o==null) return;
			//printf("%d\n",o->val);//if(pp==3) {int sh;scanf("%d",&sh);}
			print(o->ch[0]);printf("%d ",o->val);print(o->ch[1]);
	}
	
	void print(){
		print(root);puts("ga");
	}
	
	void Do(int pos,int s){
		//printf("pos:%d s:%d\n",pos,s);print();
		splay(root,pos);//printf("pos:%d s:%d\n",pos,s);print();
		splay(root->ch[1],s);//printf("pos:%d s:%d\n",pos,s);print();
	}
	
	void Done(){
		root->ch[1]->update();
		root->update();
	}
	
	void insert(int pos,int val){//在第i个数后
		Do(pos,1);//puts("fuck");
		root->ch[1]->ch[0]=New(val);
		//puts("fuck");
		Done();
	}
	
	void query(int qL,int qR){
		Do(qL,qR-qL+2);
		printf("%d\n",root->ch[1]->ch[0]->maxs);
	}
	
	void replace(int pos,int val){
		Do(pos,2);
		root->ch[1]->ch[0]=New(val);
		Done();
	}
	
	void del(int pos){
		Do(pos,2);
		root->ch[1]->ch[0]=null;
		Done();
	}
	
};
Splay ss;

int main(){
	char op[20];
	int pos,val,qL,qR;
	null=new Node();null->ch[0]=null->ch[1]=NULL;null->size=null->val=null->sum=0;null->maxs=null->maxl=null->maxr=-INF;
	scanf("%d",&n);
	ss.init();
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),ss.insert(i,A[i]);
	scanf("%d",&m);
	for(int mm=1;mm<=m;mm++){
		scanf("%s",op);
		if(op[0]=='I'){
			scanf("%d%d",&pos,&val);
			ss.insert(pos,val);
		}
		else if(op[0]=='Q'){
			scanf("%d%d",&qL,&qR);
			ss.query(qL,qR);
		}
		else if(op[0]=='R'){
			scanf("%d%d",&pos,&val);
			ss.replace(pos,val);
		}
		else{
			scanf("%d",&pos);
			ss.del(pos);
		}
	}
	return 0;
}
