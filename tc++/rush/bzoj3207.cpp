#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=200010;
const LL hash1=10000007;
const LL hash2=300001;
const LL tt=1000000;
const int maxv=maxn*20;
LL tp1,tp2;
int n,m,k,N;
LL A[maxn],B[maxn],num[maxn];
int cnt=0;

struct Node{
	int size;
	Node *ch[2];
	Node() {}
};
Node *null,seq[maxv];int seq_cnt=0;
Node *root[maxn];

Node* New(){
	Node *o=&seq[seq_cnt++];o->ch[0]=o->ch[1]=null;o->size=0;return o;
}

void Add(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size+1;
	if(L==R) return;
	int M=(L+R)>>1;
	if(val<=M) x->ch[1]=y->ch[1],x->ch[0]=New(),Add(x->ch[0],y->ch[0],L,M,val);
	else x->ch[0]=y->ch[0],x->ch[1]=New(),Add(x->ch[1],y->ch[1],M+1,R,val);
}

bool Query(Node* &x,Node* &y,int L,int R,int val){
	if(L==R) return x->size-y->size>=1;
	int M=(L+R)>>1;
	if(val<=M) return Query(x->ch[0],y->ch[0],L,M,val);
	else return Query(x->ch[1],y->ch[1],M+1,R,val);
}

int main(){
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;
	int L,R,x;
	LL val;
	scanf("%d%d%d",&n,&m,&k);N=n+1;
	for(int i=1;i<=n;i++)
		scanf("%lld",&A[i]);
	tp1=tp2=1;
	for(int i=1;i<k;i++) tp1=tp1*N%hash1,tp2=tp2*N%hash2;
	LL now1=0,now2=0;
	for(int i=1;i<k;i++){
		now1=(now1*N+A[i])%hash1,now2=(now2*N+A[i])%hash2;
	}
	
	cnt=0;
	for(int i=k;i<=n;i++){
		now1=(now1*N+A[i])%hash1;now2=(now2*N+A[i])%hash2;
		B[i-k+1]=now1*tt+now2;num[cnt++]=B[i-k+1];
		now1=(now1+(A[i-k+1]*(hash1-tp1)))%hash1;now2=(now2+(A[i-k+1]*(hash2-tp2)))%hash2;
	}
	
	sort(num,num+cnt);
	num[cnt++]=hash1*tt+hash2;
	cnt=unique(num,num+cnt)-num;
	//puts("fucjk");
	root[0]=null;
	//for(int i=0;i<cnt;i++) printf("num[%d]:%lld\n",i,num[i]);
	for(int i=1;i+k-1<=n;i++){
		//printf("B[i]:%lld\n",B[i]);
		B[i]=lower_bound(num,num+cnt,B[i])-num;
		//printf("%lld\n",B[i]);
		root[i]=New();Add(root[i],root[i-1],0,cnt-1,B[i]);
	}
	
	
	for(int i=1;i<=m;i++){
		scanf("%d%d",&L,&R);now1=0;now2=0;
		for(int i=1;i<=k;i++){
			scanf("%d",&x);
			now1=(now1*N+x)%hash1,now2=(now2*N+x)%hash2;
		}
		val=now1*tt+now2;
		int pos=lower_bound(num,num+cnt,val)-num;
		//printf("pos:%d\n",pos);
		if(num[pos]!=val) puts("Yes");
		else{
			bool ok=Query(root[R-k+1],root[L-1],0,cnt-1,pos);
			if(ok) puts("No");
			else puts("Yes");
		}
	}
	
	return 0;
}
