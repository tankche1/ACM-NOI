#include<stdio.h>
#include<string.h>
# include<math.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=12010;
const int maxm=6010;
const int maxb=320;
int n,m;
int A[maxn];
int Two[35];
int B[maxb][maxn];

struct Node{
	Node *ch[2];
	int pos;
	Node() {}
};
Node seq[maxn*40];int seq_cnt=0;
Node *null;

inline Node *New() {Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;return o;}

Node *root[maxn];

void Add(Node* x,Node* y,int val,int pos){
	//printf("val:%d pos:%d\n",val,pos);
	for(int j=31;j>=0;j--){
		int c=(val>>j)&1;
		x->pos=pos;
		x->ch[!c]=y->ch[!c];
		x->ch[c]=&seq[seq_cnt++];x->ch[c]->ch[0]=x->ch[c]->ch[1]=null;
		x=x->ch[c];y=y->ch[c];
	}
	x->pos=pos;
}

int Ask(int L,int R,int val){// pos>=L
	Node *o=root[R];
	int ans=0;
	for(int j=31;j>=0;j--){
		int c=((val>>j)&1)^1;
		if((o->ch[c]->pos<L)) c=c^1;
		else ans|=Two[j];
		o=o->ch[c];
	}
	return ans;
}

int main(){
	freopen("input.txt","r",stdin);
	freopen("output.txt","w",stdout);
	Two[0]=1;for(int i=1;i<32;i++) Two[i]=Two[i-1]<<1;
	null=new Node();null->ch[0]=null->ch[1]=null;null->pos=-100;
	scanf("%d%d",&n,&m);
	A[0]=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		A[i]^=A[i-1];
	}
	root[0]=New(),Add(root[0],null,0,0);
	for(int i=1;i<=n;i++)
		root[i]=New(),Add(root[i],root[i-1],A[i],i);
	
	int bnum=sqrt(m);int len=(n-1)/bnum+1;
	for(int i=0;i<bnum;i++){
		for(int j=i*len+1;j<=n;j++){
			B[i][j]=max(B[i][j-1],Ask(i*len,j-1,A[j]));
		}
	}
	//return 0;
	int ans=0,L,R;
	for(int i=1;i<=m;i++){
		int j;
		scanf("%d%d",&L,&R);
		L=(L+ans%n)%n+1;R=((LL)R+ans%n)%n+1;
		if(L>R) swap(L,R);
		ans=0;
		int p=(L-1)/len+((L)%len!=1);
		//printf("L:%d R:%d p:%d p*len:%d\n",L,R,p,p*len);
		if(p*len+1<=R) ans=B[p][R];p=min(R,p*len);
		for(int j=L-1;j<=p;j++){
			ans=max(ans,Ask(L-1,R,A[j]));
		}
		printf("%d\n",ans);
		//printf("L:%d R:%d p:%d %d\n",L,R,p,p-(L-1)+1);
	}
	return 0;
}
