#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxx=3000010;
const int maxy=40000010;
int n,m,A[maxn];
typedef pair<int,int> pi;
const int INF=maxn;
vector<pi> G[maxn];

struct Duty{
	int pre,pos,suff;
	Duty() {}
	Duty(int pre,int pos,int suff):pre(pre),pos(pos),suff(suff) {}
};
Duty duty[maxn];
struct tank{
	int value,pos;
	tank() {}
	tank(int value,int pos):value(value),pos(pos) {}
	bool operator < (const tank &rhs)const{
		return value==rhs.value?pos<rhs.pos:value<rhs.value;
	}
};
tank B[maxn*3];
bool appear[maxn];

bool cmp(Duty A,Duty B){
	return A.pre<B.pre;
}

struct SegmenTree{
	int _max;
	SegmenTree *ch[2];
	SegmenTree() {}
};
SegmenTree *snull,qseg[maxy];
int qseg_cnt=0;

SegmenTree *News(){
	SegmenTree *o=&qseg[qseg_cnt++];o->_max=0;o->ch[0]=o->ch[1]=snull;return o;
}

struct Node{
	SegmenTree *sgt;
	Node *ch[2];
	Node() {}
};
Node *root[maxn],*null,seq[maxx];int seq_cnt=0;

Node *New(){
	Node *o=&seq[seq_cnt++];o->sgt=snull;o->ch[0]=o->ch[1]=null;return o;
}

void Addy(SegmenTree* &x,SegmenTree* &y,int L,int R,int pos,int val){
	x->_max=max(y->_max,val);
	if(L==R) return;
	int M=(L+R)>>1;
	if(pos<=M)
		x->ch[1]=y->ch[1],x->ch[0]=News(),Addy(x->ch[0],y->ch[0],L,M,pos,val);
	else x->ch[0]=y->ch[0],x->ch[1]=News(),Addy(x->ch[1],y->ch[1],M+1,R,pos,val);
}

void Addx(pi p,Node* &x,Node* &y,int L,int R,int val){
	x->sgt=News();
	Addy(x->sgt,y->sgt,1,n+1,p.second,val);
	if(L==R) return;
	int M=(L+R)>>1;
	if(p.first<=M){
		x->ch[1]=y->ch[1];x->ch[0]=New();Addx(p,x->ch[0],y->ch[0],L,M,val);
	}
	else{
		x->ch[0]=y->ch[0];x->ch[1]=New();Addx(p,x->ch[1],y->ch[1],M+1,R,val);
	}
}

int queryy(SegmenTree* &x,int L,int R,int qL,int qR){
	if(qL<=L&&qR>=R){
		return x->_max;
	}
	int M=(L+R)>>1,ans=-INF;
	if(qL<=M) ans=max(ans,queryy(x->ch[0],L,M,qL,qR));
	if(qR>M) ans=max(ans,queryy(x->ch[1],M+1,R,qL,qR));
	return ans;
}

int queryx(Node* &x,pi A,pi B,int L,int R){
	if(A.first<=L&&B.first>=R){
		return queryy(x->sgt,1,n+1,A.second,B.second);
	}
	int M=(L+R)>>1,ans=-INF;
	if(A.first<=M) ans=max(ans,queryx(x->ch[0],A,B,L,M));
	if(B.first>M) ans=max(ans,queryx(x->ch[1],A,B,M+1,R));
	return ans;
}

int query(int L,int R){
	return queryx(root[L-1],pi(L,R+1),pi(R,n+1),1,n);
}

int main(){
	//freopen("input.txt","r",stdin);
//freopen("output.txt","w",stdout);
	snull=new SegmenTree();snull->ch[0]=snull->ch[1]=snull;snull->_max=0;
	null=new Node();null->ch[0]=null->ch[1]=null;null->sgt=snull;
	scanf("%d%d",&n,&m);
	memset(appear,false,sizeof(appear));
	int cnt=0;
	for(int i=1;i<=n;i++){
		scanf("%d",&A[i]);
		if(!appear[A[i]]) B[cnt++]=tank(A[i],0),B[cnt++]=tank(A[i],n+1),appear[A[i]]=1;
		B[cnt++]=tank(A[i],i);
	}
	sort(B,B+cnt);
	int pos=0;
	for(int i=0;i<cnt;i++){
		if(B[i].pos>0&&B[i].pos<=n){
			//duty[pos++]=Duty(B[i-1].pos,B[i].pos,B[i+1].pos);
			G[B[i-1].pos].push_back(pi(B[i].pos,B[i+1].pos));
		}
	}
	Node *last;
	for(int i=0;i<n;i++){
		root[i]=i==0?null:root[i-1];
		for(int e=0;e<G[i].size();e++){
			last=root[i];root[i]=New();
			Addx(G[i][e],root[i],last,1,n,A[G[i][e].first]);
		}
	}
	int ans=0,l,r;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&l,&r);
		l=(l+ans)%n+1;r=(r+ans)%n+1;
		if(l>r) swap(l,r);
		printf("%d\n",ans=query(l,r));
	}
	return 0;
}
