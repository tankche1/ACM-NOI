#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int INF=~0U>>3;
int n,m;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int size[maxn],son[maxn],fa[maxn],bh[maxn],top[maxn],num[maxn],bh_cnt=0,tp_size[maxn];
vector<int> tp[maxn];
int dis[maxn],black[maxn];
int pl(int a,int b){
	if(a==-INF||b==-INF) return -INF;
		return a+b;
}

struct HeapNode{
	int d,u;
	HeapNode() {}
	HeapNode(int d,int u):d(d),u(u) {}
	bool operator <(const HeapNode &rhs) const{
		return d<rhs.d;
	}
};
priority_queue<HeapNode> que[maxn];//储存每个点的d值
priority_queue<HeapNode> all_que;//储存所有链的opt值

struct Node{
	Node *ch[2];
	int maxl,maxr,opt;
};
Node *null;
Node seq[maxn<<2];int seq_cnt=0;
Node *tree[maxn];

Node *New(){
	Node *o=&seq[seq_cnt++];
	o->maxl=o->maxr=o->opt=-INF;o->ch[0]=o->ch[1]=null;
	return o;
}

void maintain(Node *o,int x,int L,int R){
	int M=(L+R)>>1;
	o->maxl=max(o->ch[0]->maxl,pl(dis[tp[bh[x]][M]]-dis[tp[bh[x]][L-1]],o->ch[1]->maxl));
	o->maxr=max(o->ch[1]->maxr,pl(dis[tp[bh[x]][R-1]]-dis[tp[bh[x]][M-1]],o->ch[0]->maxr));
	o->opt=max(max(o->ch[0]->opt,o->ch[1]->opt),pl(dis[tp[bh[x]][M]]-dis[tp[bh[x]][M-1]],pl(o->ch[0]->maxr,o->ch[1]->maxl)));
}

Node *build(int L,int R){
	Node *o=New();
	if(L==R) return o;
	int M=(L+R)>>1;
	o->ch[0]=build(L,M);o->ch[1]=build(M+1,R);
	return o;
}

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs_size(int x){
	size[x]=1;son[x]=0;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]) {dis[v[e]]=dis[x]+1,fa[v[e]]=x,dfs_size(v[e]),size[x]+=size[v[e]];if(size[v[e]]>size[son[x]]) son[x]=v[e];}
}

void dfs_build(int x){
	if(son[x]){
		tp[bh[x]].push_back(son[x]);
		top[son[x]]=top[x];num[son[x]]=num[x]+1;tp_size[bh[x]]++;bh[son[x]]=bh[x];dfs_build(son[x]);
	}
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]&&v[e]!=son[x]){
			top[v[e]]=v[e];bh[v[e]]=++bh_cnt;num[v[e]]=1;tp_size[bh[v[e]]]=1;tp[bh[v[e]]].push_back(v[e]);
			dfs_build(v[e]);
			tree[bh[v[e]]]=build(1,tp_size[bh[v[e]]]);
	}
}

void get(int x,int &d,int &u,int no){
	while(!que[x].empty()){
			u=que[x].top().u;
			if(tree[bh[u]]->maxl+1!=que[x].top().d||u==no) {que[x].pop();continue;}
			d=que[x].top().d;que[x].pop();break;
	}
}

void update(Node *o,int L,int R,int x){
	
	// printf("L:%d R:%d x:%d\n",L,R,x);
	if(L==R){
		int d1=-INF,d2=-INF,p1,p2;
		get(x,d1,p1,0);
		get(x,d2,p2,p1);//puts("oh");
		//printf("d1:%d d2:%d\n",d1,d2);
		if(black[x]){
			o->maxl=o->maxr=max(0,d1);
			o->opt=max(max(0,pl(d1,d2)),d1);
		}
		else{
			o->maxl=o->maxr=d1;
			o->opt=max(-INF,d1+d2);
		}
		if(d1!=-INF) que[x].push(HeapNode(d1,p1));
		if(d2!=-INF) que[x].push(HeapNode(d2,p2));
		//他可能是只有一个节点的链
	}
	else{
		int M=(L+R)>>1;
		if(num[x]<=M)
			update(o->ch[0],L,M,x);
		else update(o->ch[1],M+1,R,x);
		maintain(o,x,L,R); 
	}
	if(R==tp_size[bh[x]]){//这是链的根节点
		if(o->opt!=-INF) all_que.push(HeapNode(o->opt,x));
		if(fa[top[x]]!=0){
			que[fa[top[x]]].push(HeapNode(o->maxl+1,top[x]));
			//printf("que[%d]: d:%d u:%d\n",fa[top[x]],o->maxl+1,top[x]);
		}
	}
	//printf("L:%d R:%d x:%d opt:%d maxl:%d maxr:%d \n",L,R,x,o->opt,o->maxl,o->maxr);
}

void dfs_init(int x){
//	printf("x:%d\n",x);
	if(son[x]) dfs_init(son[x]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]!=son[x]&&v[e]!=fa[x])
			dfs_init(v[e]);
	}
	update(tree[bh[x]],1,tp_size[bh[x]],x);
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("hide.in","r",stdin);
	//freopen("hide.out","w",stdout);
	char op[20];
	null=new Node();null->maxl=null->maxr=null->opt=-INF;null->ch[0]=null->ch[1]=null;
	int a,b;
	scanf("%d",&n);
	edge=0;memset(first,-1,sizeof(first));
	for(int i=1;i<n;i++)
		scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);
	for(int i=1;i<=n;i++) black[i]=true;
	fa[1]=0;size[0]=0;dis[1]=1;
	dfs_size(1);
	top[1]=1;num[1]=1;bh[1]=++bh_cnt;tp_size[1]=1;tp[1].push_back(1);//bh_cnt=1;
	dfs_build(1);tree[1]=build(1,tp_size[1]);
	scanf("%d",&m);
	dfs_init(1);
	//for(int i=0;i<tp[bh[1]].size();i++) printf("tp:%d\n",tp[bh[1]][i]);
	for(int i=1;i<=m;i++){
		scanf("%s",op);
		if(op[0]=='G'){
			bool ok=false;
			while(!all_que.empty()){
				if(all_que.top().d!=tree[bh[all_que.top().u]]->opt) {all_que.pop();continue;}
				printf("%d\n",all_que.top().d);ok=true;break;
			}
			if(!ok) puts("-1");
		}
		else{
			scanf("%d",&a);black[a]^=1;
			while(top[a]!=1){
				update(tree[bh[a]],1,tp_size[bh[a]],a);
				a=fa[top[a]];//printf("a:%d\n",a);
			}
			update(tree[bh[a]],1,tp_size[bh[a]],a);
		}
	}
	return 0;
}
