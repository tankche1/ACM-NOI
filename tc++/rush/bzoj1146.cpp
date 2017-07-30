#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=80010;
const int maxv=maxn*6*18;
const int Step=17;
int n,q;
int A[maxn];
int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;
int rangeL[maxn],rangeR[maxn],dfs_clock;
int f[maxn],dep[maxn],Two[Step+1];

struct Duty{
	int pos,value,op;
	Duty() {}
	Duty(int pos,int value,int op):pos(pos),value(value),op(op) {}
	bool operator < (const Duty &rhs)const{
		return pos<rhs.pos;
	}
};
Duty duty[maxn<<1];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int x,int fa){
	f[x]=fa;dep[x]=dep[fa]+1;
	rangeL[x]=++dfs_clock;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa)
			dfs(v[e],x);
	rangeR[x]=dfs_clock;
}

int num[maxn<<1],cnum;

struct Node{
	int size;
	Node *ch[2];
	Node() {}
};
Node *null,qnode[maxv];int q_cnt=0;
Node *root[maxn];

Node *New(){
	Node *o=&qnode[q_cnt++];o->ch[0]=o->ch[1]=null;o->size=0;return o;
}

void Add(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size+1;
	int M=(L+R)>>1;
	if(L==R) return;
	if(val<=M) x->ch[1]=y->ch[1],x->ch[0]=New(),Add(x->ch[0],y->ch[0],L,M,val);
	else x->ch[0]=y->ch[0],x->ch[1]=New(),Add(x->ch[1],y->ch[1],M+1,R,val);
}

void Del(Node* &x,Node* &y,int L,int R,int val){
	x->size=y->size-1;
	int M=(L+R)>>1;
	if(L==R) return;
	if(val<=M) x->ch[1]=y->ch[1],x->ch[0]=New(),Del(x->ch[0],y->ch[0],L,M,val);
	else x->ch[0]=y->ch[0],x->ch[1]=New(),Del(x->ch[1],y->ch[1],M+1,R,val);
}
int dp[maxn][18];

void prepare(){
	for(int i=1;i<=n;i++)
		dp[i][0]=f[i];
	for(int j=1;j<=Step;j++){
		for(int i=1;i<=n;i++)
			dp[i][j]=dp[dp[i][j-1]][j-1];
	}
}

int LCA(int a,int b){
	if(dep[a]<dep[b]) swap(a,b);
	int t=dep[a]-dep[b];
	for(int j=Step;j>=0;j--)
		if(t&Two[j])
			a=dp[a][j];
	int j=Step;
	while(a!=b){
		while(j>0&&dp[a][j]==dp[b][j]) j--;
		a=dp[a][j];b=dp[b][j];
	}
	return a;
}
Node *qx[5],*qy[5];int qx_cnt,qy_cnt;

int Query(int a,int b,int k){
	int anc=LCA(a,b);qx_cnt=qy_cnt=0;
	qx[qx_cnt++]=root[rangeL[a]];qx[qx_cnt++]=root[rangeL[b]];qy[qy_cnt++]=root[rangeL[anc]];
	if(anc!=1) qy[qy_cnt++]=root[rangeL[f[anc]]];
	int L=1,R=cnum,sum=0,M;
	for(int i=0;i<qx_cnt;i++) sum+=qx[i]->size;for(int i=0;i<qy_cnt;i++) sum-=qy[i]->size;
	if(sum<k) return -1;
	while(L!=R){
		sum=0;M=(L+R)>>1;
		for(int i=0;i<qx_cnt;i++) sum+=qx[i]->ch[1]->size;for(int i=0;i<qy_cnt;i++) sum-=qy[i]->ch[1]->size;
		if(sum<k) {R=M,k-=sum;for(int i=0;i<qx_cnt;i++) qx[i]=qx[i]->ch[0];for(int i=0;i<qy_cnt;i++) qy[i]=qy[i]->ch[0];}
		else {L=M+1;for(int i=0;i<qx_cnt;i++) qx[i]=qx[i]->ch[1];for(int i=0;i<qy_cnt;i++) qy[i]=qy[i]->ch[1];}
	}
	return L;
}
int gop[maxn],ga[maxn],gb[maxn];

int main(){
	//freopen("input.txt","r",stdin);
	null=new Node();null->ch[0]=null->ch[1]=null;null->size=0;
	Two[0]=1;for(int i=1;i<=Step;i++) Two[i]=Two[i-1]<<1;
	int op,a,b,k;
	scanf("%d%d",&n,&q);
	for(int i=1;i<=n;i++)
		scanf("%d",&A[i]),num[i]=A[i];
	
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	dfs_clock=0;dep[1]=0;
	dfs(1,1);
	
	cnum=n;for(int i=1;i<=q;i++) {scanf("%d%d%d",&gop[i],&ga[i],&gb[i]);if(gop[i]==0) num[++cnum]=gb[i];}
	sort(num+1,num+cnum+1);
	cnum=unique(num+1,num+cnum+1)-num-1;
	for(int i=1;i<=n;i++)
		A[i]=lower_bound(num+1,num+cnum+1,A[i])-num;
	
	int cnt=0;
	for(int i=1;i<=n;i++){
		duty[cnt++]=Duty(rangeL[i],A[i],1);
		if(i!=1) duty[cnt++]=Duty(rangeR[i]+1,A[i],-1);
	}
	sort(duty,duty+cnt);
	
	int pos=0;
	root[0]=null;
	Node *last;
	for(int i=1;i<=dfs_clock;i++){
		root[i]=root[i-1];
		while(duty[pos].pos==i){
			Node *last=root[i];
			if(duty[pos].op==1) root[i]=New(),Add(root[i],last,1,cnum,duty[pos].value);
			else root[i]=New(),Del(root[i],last,1,cnum,duty[pos].value);
			pos++;
		}
	}
	prepare();
	for(int i=1;i<=q;i++){
		op=gop[i],a=ga[i];b=gb[i];
		if(op==0){
			b=lower_bound(num+1,num+cnum+1,b)-num;
			last=root[rangeL[a]];root[rangeL[a]]=New();Del(root[rangeL[a]],last,1,cnum,A[a]);
			last=root[rangeL[a]];root[rangeL[a]]=New();Add(root[rangeL[a]],last,1,cnum,b);
			if(a!=1){
			last=root[rangeR[a]+1];root[rangeR[a]+1]=New();Add(root[rangeR[a]+1],last,1,cnum,A[a]);
			last=root[rangeR[a]+1];root[rangeR[a]+1]=New();Del(root[rangeR[a]+1],last,1,cnum,b);
			}
			A[a]=b;
		}
		else{
			int ans=Query(a,b,op);
			if(ans==-1) puts("invalid request!");
			else printf("%d\n",ans);
		}
	}
	return 0;
}
