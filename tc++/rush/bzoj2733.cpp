#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxq=maxn*4;
int op[maxq][3];
int n,m,q;
int p[maxn],bh[maxn];
int size[maxn];
int weight[maxn];
int A[maxn];
int L[maxn],R[maxn];

int next[maxn];

int find(int x){if(x==p[x]) return x;return p[x]=find(p[x]);}

char t;int res;
int getint(){
	while((t=getchar())&&(t<'0'||t>'9'));
	res=t-'0';
	while((t=getchar())&&(t>='0'&&t<='9')) res=res*10+t-'0';
	return res;
}

struct Node{
	Node *ch[2];
	int size;
	Node() {}
};
Node *null,*root[maxn],seq[maxn*30];
int seq_cnt=0;
Node *qx,*qy;

Node *New(){
	Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->size=0;return o;
}

void Insert(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size+1;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=M){
		x->ch[0]=New();x->ch[1]=y->ch[1];
		Insert(x->ch[0],y->ch[0],L,M,val);
	}
	else{
		x->ch[1]=New();x->ch[0]=y->ch[0];
		Insert(x->ch[1],y->ch[1],M+1,R,val);
	}
}
int to[maxn];

int Ask(int x,int y,int k){
	qx=root[x];qy=root[y];
	int L=1,R=n;
	int M,c;
	if(k>qy->size-qx->size) return -1;
	for(;;){
		M=(L+R)>>1;
		if(L==R) return to[L];
		int tot=qy->ch[0]->size-qx->ch[0]->size;
		if(k<=tot) c=0;else k-=tot,c=1;
		qx=qx->ch[c];qy=qy->ch[c];
		if(c) L=M+1;else R=M;
	}
}

void add_edge(int x,int y){
	int px=find(x),py=find(y);
	if(px==py) return;
	if(size[px]>size[py]) swap(x,y),swap(px,py);
	for(int e=px;e!=-1;e=next[e]){
		bh[e]+=size[py];
		if(next[e]==-1){
			next[e]=next[py];next[py]=px;break;
		}
	}
	size[py]+=size[px];
	p[px]=py;
	p[px]=py;
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;
	char t;
	n=getint();m=getint();
	for(int i=1;i<=n;i++){
		A[i]=getint();
		to[A[i]]=i;
	}
	int tot=1;
	for(int i=1;i<=m;i++){
		op[tot][0]=1;
		op[tot][1]=getint();op[tot][2]=getint();
		tot++;
	}
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		while((t=getchar())&&t!='B'&&t!='Q');
		op[tot][0]=t=='B'?1:2;
		op[tot][1]=getint();op[tot][2]=getint();
		tot++;
	}
	
	memset(next,-1,sizeof(next));
	for(int i=1;i<=n;i++) p[i]=i,bh[i]=1,size[i]=1;
	for(int i=1;i<tot;i++){
		if(op[i][0]==1){
			add_edge(op[i][1],op[i][2]);
		}
	}
	for(int i=2;i<=n;i++)
		if(find(i)!=find(1))
			add_edge(1,i);
	for(int i=1;i<=n;i++)
		weight[bh[i]]=A[i];
	root[0]=New();
	for(int i=1;i<=n;i++){
		Node *u=New();
		Insert(u,root[i-1],1,n,weight[i]);
		root[i]=u;
	}
	for(int i=1;i<=n;i++) p[i]=i,L[i]=R[i]=bh[i];
	for(int i=1;i<tot;i++){
		if(op[i][0]==1){
			int px=find(op[i][1]),py=find(op[i][2]);
			if(px==py) continue;
			L[py]=min(L[py],L[px]),R[py]=max(R[px],R[py]);
			p[px]=py;
		}
		else{
			int px=find(op[i][1]),k=op[i][2];
			printf("%d\n",Ask(L[px]-1,R[px],k));
		}
	}
	return 0;
}

