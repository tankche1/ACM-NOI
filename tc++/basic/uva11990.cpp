# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int maxm=100010;
typedef long long LL;
inline int lowbit(int x) {return x&(-x);}

struct Node{
	Node *ch[2];
	int v;
	int s;
	int lazy;
	Node():lazy(0) {}
	int ch_s(int d) {return ch[d]==NULL?0:ch[d]->s;}
};

struct RankTree{
	Node *nodes,*root;
	int *v;
	int n,next;

	RankTree(int n,int *A):n(n) {
		nodes=new Node[n];
		v=new int[n];
		for(int i=0;i<n;i++) v[i]=A[i];
		sort(v,v+n);
		next=0;
		root=build(0,n-1);
		delete[] v;
	}

	Node* build(int L,int R){
		if(L>R) return NULL;
		int M=(L+R)>>1;
		int u=next++;
		nodes[u].v=v[M];
		nodes[u].ch[0]=build(L,M-1);
		nodes[u].ch[1]=build(M+1,R);
		nodes[u].s=nodes[u].ch_s(0)+nodes[u].ch_s(1)+1;
		return &nodes[u];
	}

	int count(int v,int type){
		Node *u=root;
		int res=0;
		while(u!=NULL){
			if(u->v==v) {res+=u->ch_s(type);break;}
			int c=v<(u->v)?0:1;
			if(c!=type){
				//	res+=u->ch_s(type)+1; 不能这样写 因为有可能该节点已经被删除
				res+=u->s - u->ch_s(c);
			}
			u=u->ch[c];
		}
		return res;
	}

	void erase(int v){
		Node *u=root;
		while(u!=NULL){
			u->s--;
			if(u->v==v) {u->lazy=1;break;}
			int c=v<u->v?0:1;
			u=u->ch[c];
		}
	}

	~RankTree(){
		delete[] nodes;
	}
};

struct FenwickRankTree{
	vector<RankTree*> C;
	int n;

	void init(int n,int *A){
		this->n=n;
		C.resize(n+1);
		for(int i=1;i<=n;i++)
			C[i]=new RankTree(lowbit(i),A+i-lowbit(i)+1);
	}

	void clear() {for(int i=1;i<=n;i++) delete C[i];}

	int count(int x,int v,int type){
		int res=0;
		while(x>0){
			res+=C[x]->count(v,type);
			x-=lowbit(x);
		}
		return res;
	}

	void erase(int x,int v){
		while(x<=n){
			C[x]->erase(v);
			x+=lowbit(x);
		}
	}

};
FenwickRankTree frt;

struct FenwickTree{
	int n;
	vector<int> C;

	void init(int n){
		this->n=n;
		C.resize(n+1);
		fill(C.begin(),C.end(),0);
	}

	void add(int x,int d){
		while(x<=n){
			C[x]+=d;x+=lowbit(x);
		}
	}

	int sum(int x){
		int res=0;
		while(x>0){
			res+=C[x];x-=lowbit(x);
		}
		return res;
	}
};
FenwickTree ft;

int n,m,A[maxn],pos[maxn];

LL get_first(){
	ft.init(n+1);
	LL res=0;
	for(int i=n;i>=1;i--){
		res+=ft.sum(A[i]-1);
		ft.add(A[i],1);
	}
	return res;
}
int main(){
	int x;
	while(scanf("%d%d",&n,&m)!=EOF){
		for(int i=1;i<=n;i++)
		{scanf("%d",&A[i]);pos[A[i]]=i;}
		LL ans=get_first();
		ft.init(n);
		frt.init(n,A);
		for(int i=1;i<=m;i++){
			printf("%lld\n",ans);
			scanf("%d",&x);
			ft.add(x,1);
			int a=frt.count(pos[x]-1,x,1);
			int b=x-1-ft.sum(x-1);//有b个比x小的树
			int c=frt.count(pos[x]-1,x,0);
			b-=c;
			ans-=a+b;
			frt.erase(pos[x],x);
		}
		frt.clear();
	}
	return 0;
}
