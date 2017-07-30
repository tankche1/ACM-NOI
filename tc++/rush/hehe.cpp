# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxnode=200*maxn;
int n,m,A[maxn],A2[maxn<<1],cnt;
inline int lowbit(int x) {return x&(-x);}

struct Node{
	Node *ch[2];
	int size;
	Node(){}
};

Node *null,seq[maxnode],*root[maxn];
int seq_cnt=0;

Node *New(){
	Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->size=0;
	return o;
}

void Insert(Node* &x,int L,int R,int val){
	x->size++;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=A2[M]){
		if(x->ch[0]==null) x->ch[0]=New();
		Insert(x->ch[0],L,M,val);
	}
	else{
		if(x->ch[1]==null) x->ch[1]=New();
		Insert(x->ch[1],M+1,R,val);
	}
}
void Delete(Node* &x,int L,int R,int val){
	x->size--;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=A2[M]){
		Delete(x->ch[0],L,M,val);
	}
	else{
		Delete(x->ch[1],M+1,R,val);
	}
}
Node* qx[maxn],*qy[maxn];
int numx,numy;

int Ask(int ql,int qr,int k){
	//printf("ql:%d qr:%d k:%d\n",ql,qr,k);
	numx=numy=0;
	if(ql==0) qx[numx++]=root[0];
	for(int i=ql;i>0;i-=lowbit(i)) qx[numx++]=root[i];
	for(int i=qr;i>0;i-=lowbit(i)) qy[numy++]=root[i];
	int L=1,R=cnt,c;
	for(;;){
		if(L==R) return A2[L];
		int M=(L+R)>>1;
		int tot=0;
		for(int i=0;i<numx;i++) tot-=qx[i]->ch[0]->size;for(int i=0;i<numy;i++) tot+=qy[i]->ch[0]->size;
			//printf("tot:%d L:%d R:%d M:%d A:%d\n",tot,L,R,M,A2[M]);
		if(k<=tot) c=0;else c=1,k-=tot;
		for(int i=0;i<numx;i++) qx[i]=qx[i]->ch[c];for(int i=0;i<numy;i++) qy[i]=qy[i]->ch[c];
		if(c==0) R=M;else L=M+1;
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
		char t;
		while((t=getchar())&&t!='C'&&t!='Q');
		op[i][0]=t=='C';
		scanf("%d%d",&op[i][1],&op[i][2]);if(t=='Q') scanf("%d",&op[i][3]);else A2[++cnt]=op[i][2];
	}
	sort(A2+1,A2+cnt+1);
	cnt=unique(A2+1,A2+cnt+1)-(A2+1);
	for(int i=0;i<=n;i++) root[i]=New();
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j+=lowbit(j))
			Insert(root[j],1,cnt,A[i]);
	
	for(int i=1;i<=m;i++){
		if(op[i][0]==1){
			int pos=op[i][1],val=op[i][2];
			for(int j=i;j<=n;j+=lowbit(j)){
				Delete(root[j],1,cnt,A[pos]);Insert(root[j],1,cnt,val);
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
