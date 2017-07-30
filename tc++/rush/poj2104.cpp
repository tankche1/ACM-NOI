# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=100010;
const int maxnode=maxn*18;
int n,m;
int A[maxn],A2[maxn],cnt;

struct Node{
	Node *ch[2];
	int size;
	Node() {}
	void maintain(){size=ch[0]->size+ch[1]->size;}
}*null;
Node seq[maxnode];int seq_cnt=0;

Node *New(){
	Node *o=&seq[seq_cnt++];
	o->ch[0]=o->ch[1]=null;o->size=0;
	return o;
}

struct ChairTree{
	Node *root[maxn];
	
	void build(Node* &y,Node* &x,int l,int r,int t){
		y=New();
		int m=(l+r)>>1;
		if(l==r){
			*y=*x;
			y->size++;
			return;
		}
		if(t<=A2[m]){
			build(y->ch[0],x->ch[0],l,m,t);
			y->ch[1]=x->ch[1];
			y->maintain();
		}
		else{
			build(y->ch[1],x->ch[1],m+1,r,t);
			y->ch[0]=x->ch[0];
			y->maintain();
		}
	}
	
	void find(Node* &x1,Node* &x2,int l,int r,int k){
		if(l==r) {printf("%d\n",A2[l]);return;}
		int m=(l+r)>>1;
		if(x2->ch[0]->size-x1->ch[0]->size>=k)
			find(x1->ch[0],x2->ch[0],l,m,k);
		else find(x1->ch[1],x2->ch[1],m+1,r,k-(x2->ch[0]->size-x1->ch[0]->size));
	}
		
}fotile;

int main(){
	int a,b,k;
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),A2[i]=A[i];
	sort(A2+1,A2+n+1);cnt=unique(A2+1,A2+n+1)-(A2+1);
	fotile.root[0]=New();
	for(int i=1;i<=n;i++)
		fotile.build(fotile.root[i],fotile.root[i-1],1,cnt,A[i]);
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&a,&b,&k),fotile.find(fotile.root[a-1],fotile.root[b],1,cnt,k);
	return 0;
}
