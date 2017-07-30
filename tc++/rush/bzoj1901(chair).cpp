# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int A[maxn],A2[maxn<<1],cnt;
inline int lowbit(int x) {return (x&(-x));}

struct Node{
	Node *ch[2];
	int size;
	Node() {}
};
Node *null,seq[maxn*300];
Node *root[maxn];
Node *qx[maxn],*qy[maxn];
int xcnt,ycnt;
int seq_cnt=0;
int n,m;

Node *New(){
	Node *o=&seq[seq_cnt++];
	o->ch[0]=o->ch[1]=null;o->size=0;
	return o;
}

void Insert(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size+1;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=A2[M]){
		x->ch[1]=y->ch[1];
		x->ch[0]=New();
		Insert(x->ch[0],y->ch[0],L,M,val);
	}
	else{
		x->ch[0]=y->ch[0];
		x->ch[1]=New();
		Insert(x->ch[1],y->ch[1],M+1,R,val);
	}
}

void Delete(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size-1;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=A2[M]){
		x->ch[1]=y->ch[1];
		x->ch[0]=New();
		Delete(x->ch[0],y->ch[0],L,M,val);
	}
	else{
		x->ch[0]=y->ch[0];
		x->ch[1]=New();
		Delete(x->ch[1],y->ch[1],M+1,R,val);
	}
}

int Ask(int x,int y,int k){
	xcnt=ycnt=0;
	if(x==0) qx[xcnt++]=root[0];
	for(int i=x;i>0;i-=lowbit(i)) qx[xcnt++]=root[i];
	for(int i=y;i>0;i-=lowbit(i)) qy[ycnt++]=root[i];
	//printf("x:%d y:%d k:%d\n",x,y,k);
	int L=1,R=cnt,M,c;
	for(;;){
		M=(L+R)>>1;
		if(L==R) return A2[L];
		int tot=0;
		for(int i=0;i<ycnt;i++) tot+=qy[i]->ch[0]->size;for(int i=0;i<xcnt;i++) tot-=qx[i]->ch[0]->size;
		//	printf("k:%d tot:%d\n",k,tot);
		if(k<=tot) c=0;else c=1,k-=tot;
		for(int i=0;i<ycnt;i++) qy[i]=qy[i]->ch[c];for(int i=0;i<xcnt;i++) qx[i]=qx[i]->ch[c];
		if(c) L=M+1;else R=M;
	}
}

int op[maxn][4];
int main(){
	freopen("dynamic.in","r",stdin);
	freopen("dynamic.out","w",stdout);
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),A2[i]=A[i];
	cnt=n;
	for(int i=1;i<=m;i++){
		char t;while((t=getchar())&&t!='Q'&&t!='C');
		op[i][0]=t=='C';
		if(t=='C') scanf("%d%d",&op[i][1],&op[i][2]),A2[++cnt]=op[i][2];
		else scanf("%d%d%d",&op[i][1],&op[i][2],&op[i][3]);
	}
	sort(A2+1,A2+cnt+1);
	cnt=unique(A2+1,A2+cnt+1)-(A2+1);
	//for(int i=1;i<=cnt;i++)
	//	printf("A2[%d]:%d\n",i,A2[i]);
	for(int i=0;i<=n;i++)
		root[i]=New();
	
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=lowbit(j)){
			Node *u=New();
			Insert(u,root[j],1,cnt,A[i]);
			root[j]=u;
			//printf("root[%d]size:%d\n",j,root[j]->size);
		}
	
	for(int i=1;i<=m;i++){
		if(op[i][0]==1){
			int pos=op[i][1],val=op[i][2];
			for(int j=pos;j<=n;j+=lowbit(j)){
				Node *u=New();Insert(u,root[j],1,cnt,val);
				root[j]=u;
				u=New();Delete(u,root[j],1,cnt,A[pos]);
				root[j]=u;
			}
			A[pos]=val;
		}
		else{
			int L=op[i][1],R=op[i][2],k=op[i][3];
			printf("%d\n",Ask(L-1,R,k));
		}
	}
	return 0;
}
