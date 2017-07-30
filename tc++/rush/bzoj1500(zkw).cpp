/**************************************************************
SPLAY TREE!
    Problem: 1500
    User: tankche2
    Language: C++
    Result: Accepted
    Time:5508 ms
    Memory:20464 kb
****************************************************************/

# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int MAXN=500010;
const int INF=1010;
int C[MAXN];
struct Node{
	Node *ch[2];
	int sum,maxsum,mls,mrs,size,value;
	bool rev,same;

	Node(int _x=0){
		value=sum=maxsum=mls=mrs=_x;size=1;
		rev=same=false;
	}

	int cmp(int k){
		if(ch[0]->size>=k) return 0;
			else if(ch[0]->size+1==k) return -1;
				else return 1;
	}

	void update(){
		sum=ch[0]->sum+ch[1]->sum+value;
		size=ch[0]->size+ch[1]->size+1;
		maxsum=max(max(max(max(max(ch[0]->maxsum,ch[1]->maxsum),ch[0]->mrs+value+ch[1]->mls),ch[0]->mrs+value),ch[1]->mls+value),value);
		mls=max(max(ch[0]->mls,ch[0]->sum+value),ch[0]->sum+value+ch[1]->mls);
		mrs=max(max(ch[1]->mrs,ch[1]->sum+value),ch[1]->sum+value+ch[0]->mrs);
	}

	void pushdown(){
		if(rev){
			if(ch[0]->size!=0){
				ch[0]->rev=!ch[0]->rev;
				swap(ch[0]->ch[0],ch[0]->ch[1]);
				swap(ch[0]->mls,ch[0]->mrs);
			}
			if(ch[1]->size!=0){
				ch[1]->rev=!ch[1]->rev;
				swap(ch[1]->ch[0],ch[1]->ch[1]);
				swap(ch[1]->mls,ch[1]->mrs);
			}
			rev=0;
		}
		if(same){
			if(ch[0]->size!=0){
				ch[0]->same=1;
				ch[0]->value=value;
				ch[0]->sum=ch[0]->size*value;
				ch[0]->maxsum=ch[0]->mls=ch[0]->mrs=max(value,ch[0]->sum);
			}
			if(ch[1]->size!=0){
				ch[1]->same=1;
				ch[1]->value=value;
				ch[1]->sum=ch[1]->size*value;
				ch[1]->maxsum=ch[1]->mls=ch[1]->mrs=max(value,ch[1]->sum);
			}
			same=0;
		}
	}
};
Node *null;

Node *New(int _x){
	Node *o=new Node(_x);
	o->ch[0]=o->ch[1]=null;
	return o;
}

Node *build(int left,int right){
	int mid=(left+right)>>1;
	Node *o=New(C[mid]);
	if(mid>left) o->ch[0]=build(left,mid-1);
	if(mid<right) o->ch[1]=build(mid+1,right);
	o->update();
	return o;
}

struct SplayTree{
	Node *root;

	void Rotate(Node* &o,int d){
	Node *p=o->ch[!d];
	o->ch[!d]=p->ch[d];p->ch[d]=o;
	o->update();p->update();
	if(root==o) root=p;
	o=p;
	}

	void splay(Node* &o,int k){
		o->pushdown();
		int d=o->cmp(k);
		if(d!=-1){
			if(d==1) k-=o->ch[0]->size+1;
			int dd=o->ch[d]->cmp(k);
			if(dd==1) k-=o->ch[d]->ch[0]->size+1;
			o->ch[d]->pushdown();
			if(dd==-1){
				Rotate(o,!d);
			}
			else{
				splay(o->ch[d]->ch[dd],k);
				if(d==dd){
					Rotate(o,!dd);
					Rotate(o,!d);
				}
				else{
					Rotate(o->ch[d],!dd);
					Rotate(o,!d);
				}
			}
		}
	}

	void print(Node *o){
		if(o==null) return;
			o->pushdown();
		print(o->ch[0]);
		printf("value:%d size:%d mls:%d mrs:%d maxsum:%d sum:%d\n",o->value,o->size,o->mls,o->mrs,o->maxsum,o->sum);
		print(o->ch[1]);
	}

	void init(){
		root=New(-INF);//root->ch[0]=null;
		root->ch[1]=New(-INF);
		root->update();
	}

	void Insert(int pos,int tot){//puts("fuck");
		splay(root,pos+1);//puts("fuck");
		splay(root->ch[1],1);//puts("fuck");
		root->ch[1]->ch[0]=build(1,tot);
		root->ch[1]->update();
		root->update();
	}

	void Del(Node *o){
		if(o==null) return;
		Del(o->ch[0]);
		Del(o->ch[1]);
		delete o;
	}

	void Delete(int pos,int tot){
		splay(root,pos);//puts("fuck");
		//print(root);
		splay(root->ch[1],tot+1);//puts("fuck");
		Node *p=root->ch[1]->ch[0];
		Del(p);//puts("fuck");
		root->ch[1]->ch[0]=null;
		//printf("size:%d sum:%d value:%d\n",null->size,null->sum,null->value);
		root->ch[1]->update();
		root->update();
	}

	void MakeSame(int pos,int tot,int val){
		splay(root,pos);
		splay(root->ch[1],tot+1);
		Node *o=root->ch[1]->ch[0];
		o->same=1;
		o->value=val;
		o->sum=o->size*val;
		o->maxsum=o->mls=o->mrs=max(val,o->sum);
		root->ch[1]->update();
		root->update();
	}

	void Reverse(int pos,int tot){
		splay(root,pos);
		splay(root->ch[1],tot+1);
		Node *o=root->ch[1]->ch[0];
		o->rev=!o->rev;
		swap(o->ch[0],o->ch[1]);
		swap(o->mls,o->mrs);
		root->ch[1]->update();
		root->update();
	}

	int GetSum(int pos,int tot){
		splay(root,pos);
		splay(root->ch[1],tot+1);
		Node *o=root->ch[1]->ch[0];
		return o->sum;
	}

	int MaxSum(){
		return root->maxsum;
	}

};
SplayTree ss;

int n,m;
char op[20];

int main(){
	int pos,tot;
	null=new Node(-INF);null->sum=null->size=0;null->ch[0]=null->ch[1]=NULL;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&C[i]);
	ss.init();
	//ss.print(ss.root);puts("");
	ss.Insert(0,n);//ss.print(ss.root);puts("");
	for(int i=1;i<=m;i++){
		//ss.print(ss.root);puts("");
		scanf("%s",op);
		if(op[0]=='I'){
			scanf("%d%d",&pos,&tot);
			for(int i=1;i<=tot;i++) scanf("%d",&C[i]);
			ss.Insert(pos,tot);
		}
		else if(op[0]=='D'){
			scanf("%d%d",&pos,&tot);
			ss.Delete(pos,tot);
		}
		else if(op[0]=='M'&&op[2]=='K'){
			scanf("%d%d%d",&pos,&tot,&C[0]);
			ss.MakeSame(pos,tot,C[0]);
		}
		else if(op[0]=='R'){
			scanf("%d%d",&pos,&tot);
			ss.Reverse(pos,tot);
		}
		else if(op[0]=='G'){
			scanf("%d%d",&pos,&tot);
			printf("%d\n",ss.GetSum(pos,tot));
		}
		else
			printf("%d\n",ss.MaxSum());
	}
	return 0;
}
