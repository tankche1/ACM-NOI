# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=500010;
const int maxm=1000010;
vector<int> G[maxn];
vector<int> Cost[maxn];
int n,m;
int cur[maxn];

int S[maxn],top;
int L[maxn],R[maxn];
int fa[maxn],val[maxn],Len[maxn];

struct SegmenTree{
	int lazy[maxn<<2],c[maxn<<2];

	void build(int o,int L,int R){
		lazy[o]=0;c[o]=Len[L];
		if(L==R) {return;}
		int M=(L+R)>>1;
		build(o<<1,L,M);
		build(o<<1|1,M+1,R);
	}

	void pushdown(int o){
		if(lazy[o]!=0){
			lazy[o<<1]+=lazy[o];lazy[o<<1|1]+=lazy[o];c[o<<1]+=lazy[o];c[o<<1|1]+=lazy[o];
			lazy[o]=0;
		}
	}

	void update(int o,int L,int R,int qL,int qR,int v){
		if(qL<=L&&qR>=R){
			c[o]+=v;lazy[o]+=v;return;
		}
		int M=(L+R)>>1;
		pushdown(o);
		if(qL<=M) update(o<<1,L,M,qL,qR,v);
		if(qR>M) update(o<<1|1,M+1,R,qL,qR,v);
	}

	int query(int o,int L,int R,int pos){
		if(L==R) return c[o];
		int M=(L+R)>>1;
		pushdown(o);
		if(pos<=M) return query(o<<1,L,M,pos);
		else return query(o<<1|1,M+1,R,pos);
	}
}seg;


int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int a,b,c;
	scanf("%d%d",&n,&m);
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		G[a].push_back(b);G[b].push_back(a);
		Cost[a].push_back(c);Cost[b].push_back(c);
	}

	int tblock=0;
	memset(cur,0,sizeof(cur));
	S[top=0]=1;fa[1]=1;val[1]=0;Len[1]=0;
	while(top>=0){
		Loop:
		int x=S[top];
		if(cur[x]==0) L[x]=++tblock;
		//printf("x:%d L[x]:%d len:%d\n",x,L[x],Len[L[x]]);
		for(;cur[x]<(int)G[x].size();cur[x]++){
            if(G[x][cur[x]]==fa[x]) continue;
			S[++top]=G[x][cur[x]];fa[S[top]]=x;val[tblock+1]=Cost[x][cur[x]];
			Len[tblock+1]=Len[L[x]]+Cost[x][cur[x]];
			cur[x]++;goto Loop;
		}
		R[x]=tblock;
		top--;
	}

	char op;
	seg.build(1,1,n);
	for(int i=1;i<=m;i++){
		while((op=getchar())&&op!='S'&&op!='P');
		if(op=='S'){
		   scanf("%d%d%d",&a,&b,&c);
		   if(fa[a]==b) swap(a,b);
		   seg.update(1,1,n,L[b],R[b],c-val[L[b]]);val[L[b]]=c;
	   }
	   else{
		   scanf("%d",&a);
		   printf("%d\n",seg.query(1,1,n,L[a]));
	   }
	}


	return 0;
}
