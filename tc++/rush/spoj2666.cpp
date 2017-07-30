# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int inf=~0U>>1;
const int INF=inf;
int pl(int a,int b){
	if(a==-inf||b==-inf) return -inf;
		return a+b;
}
inline int getInt(){
	int ans=0;char t;bool sign=true;
	while((t=getchar())&&(t<'0'||t>'9')&&t!='-');
	if(t=='-') sign=false,t=getchar();
	do{
		ans=ans*10+t-'0';
		t=getchar();
	}while(t>='0'&&t<='9');
	if(!sign) ans=-ans;
		//printf("%d\n",ans);
	return ans;
}
const int maxn=200010;
int n,col[maxn],weight[maxn];
vector<int> line[maxn];
struct HeapNode{
	int d,u;
	bool operator <(const HeapNode &rhs) const{
		return d<rhs.d;
	}
	
	void c(int dd,int uu){
		d=dd;u=uu;
	}
};

priority_queue<HeapNode> que[maxn],all_queue;

struct IntervalTree{
	int maxl,maxr,L,R,opt;
	IntervalTree *lson,*rson;
};
IntervalTree *tree[maxn];
IntervalTree Inter[maxn<<3],*null;
int Inter_cnt=0;
IntervalTree * New(){
	IntervalTree *A=&Inter[++Inter_cnt];
	A->lson=A->rson=null;
	return A;
}

IntervalTree* build(int l,int r){
	IntervalTree *o=New();
	o->L=l,o->R=r;
	if(l==r){
		o->maxl=o->maxr=o->opt=0;
	}
	else{
		int M=(l+r)>>1;
		o->lson=build(l,M);o->rson=build(M+1,r);
	}
	return o;
}

int first[maxn],next[maxn<<1],v[maxn<<1],cost[maxn<<1],m;
void add_edge(int a,int b,int c){
	next[m]=first[a];
	first[a]=m;
	v[m]=b;
	cost[m++]=c;
}

int size[maxn],son[maxn],fa[maxn],top[maxn],bh[maxn],line_cnt,dis[maxn];
int length[maxn],num[maxn];//bh 哪条链 length是有多少个元素 num是x是链上的第几个元素

void dfs_size(int x){
	size[x]=1;son[x]=-1;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa[x]) continue;
		weight[v[e]]=cost[e];dis[v[e]]=dis[x]+cost[e];
		fa[v[e]]=x;
		dfs_size(v[e]);
		size[x]+=size[v[e]];
		if(son[x]==-1||size[v[e]]>size[son[x]]) son[x]=v[e];
	}
}

void dfs_build(int x){
	if(x==top[x]) {bh[x]=++line_cnt;length[bh[x]]=0;}
		else bh[x]=line_cnt;
	num[x]=++length[bh[x]];line[bh[x]].push_back(x);
	if(son[x]!=-1) {top[son[x]]=top[x];dfs_build(son[x]);}
	else tree[bh[x]]=build(1,length[bh[x]]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]!=fa[x]&&v[e]!=son[x]){
			top[v[e]]=v[e];
			dfs_build(v[e]);
		}
	}
	//printf("x:%d top:%d bh:%d length:%d num:%d \n",x,top[x],bh[x],length[bh[x]],num[x]);
}

void update(IntervalTree *o,int num,int x){
	//printf("x:%d L;%d R:%d\n",x,o->L,o->R);
	HeapNode h;
		if(o->L==o->R){
			int d1=-inf,p1=-1,d2=-inf,p2=-1;
			while(!que[x].empty()){
				//printf("d:%d u:%d\n",que[x].top().d,que[x].top().u);
				if(pl(tree[bh[que[x].top().u]]->maxl,weight[que[x].top().u])!=que[x].top().d) {que[x].pop();continue;}	
				d1=que[x].top().d;p1=que[x].top().u;que[x].pop();break;
			}
			//printf("d1:%d p1:%d\n",d1,p1);
			while(!que[x].empty()){
				//printf("d:%d u:%d maxl:%d weight:%d\n",que[x].top().d,que[x].top().u,tree[bh[que[x].top().u]]->maxl,weight[que[x].top().u]);
				if((que[x].top().u==p1)||(pl(tree[bh[que[x].top().u]]->maxl,weight[que[x].top().u])!=que[x].top().d)) {que[x].pop();continue;}
				d2=que[x].top().d;p2=que[x].top().u;break;
			}//printf("d2:%d p2:%d\n",d2,p2);
			h.c(d1,p1);
			if(d1!=-inf) que[x].push(h);
			if(col[x])
			o->maxl=o->maxr=max(d1,0);
			else o->maxl=o->maxr=d1;
			if(col[x]) o->opt=max(0,max(pl(d1,d2),d1));
				else o->opt=pl(d1,d2);
					//puts("a");
			if(length[bh[x]]==1){
				if(o->maxl!=-inf&&x!=1){
					h.c(o->maxl+weight[x],x);
					que[fa[x]].push(h);
				}
			h.c(o->opt,x);
			if(o->opt!=-inf) all_queue.push(h);
			}
		//	printf("x:%d L:%d R:%d maxl:%d maxr:%d opt:%d\n",x,o->L,o->R,o->maxl,o->maxr,o->opt);
		}
		int M=(o->L+o->R)>>1;
		if(num<=M) update(o->lson,num,x);
		else update(o->rson,num,x);
		o->maxl=max(o->lson->maxl,pl(o->rson->maxl,dis[line[bh[x]][M+1-1]]-dis[line[bh[x]][o->L-1]]));
		o->maxr=max(o->rson->maxr,pl(o->lson->maxr,dis[line[bh[x]][o->R-1]]-dis[line[bh[x]][M-1]]));
		o->opt=max(o->lson->opt,o->rson->opt);
		o->opt=max(o->opt,pl(pl(dis[line[bh[x]][M+1-1]]-dis[line[bh[x]][M-1]],o->rson->maxl),o->lson->maxr));
		if(o->R==length[bh[x]]){
			if(top[x]!=1&&o->maxl!=-inf){
				h.c(o->maxl+weight[top[x]],top[x]);
				//printf("h.d:%d h.u:%d\n",h.d,h.u);
				que[fa[top[x]]].push(h);
			}
			h.c(o->opt,top[x]);
			if(o->opt!=-inf) all_queue.push(h);
		}
			//printf("x:%d L:%d R:%d maxl:%d maxr:%d opt:%d\n",x,o->L,o->R,o->maxl,o->maxr,o->opt);
}

void dfs_init(int x){
	if(son[x]!=-1) dfs_init(son[x]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]!=son[x]&&v[e]!=fa[x])
			dfs_init(v[e]);
	}
	update(tree[bh[x]],num[x],x);
}

int main(){
	//freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	null=New();//null->maxl=null->m
	int a,b,c;
	char s[20];
	memset(col,1,sizeof(col));
	n=getInt();m=0;memset(first,-1,sizeof(first));
	for(int i=1;i<n;i++){
		a=getInt();b=getInt();c=getInt();
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	fa[1]=0;top[1]=1;line_cnt=0;dis[1]=0;
	dfs_size(1);
	dfs_build(1);
	dfs_init(1);
	int op=getInt();
	while(op--){
		scanf("%s",s);
		if(s[0]=='A'){
			int flag=0;
			while(!all_queue.empty()){
				if(tree[bh[all_queue.top().u]]->opt!=all_queue.top().d) {all_queue.pop();continue;}
				flag=true;printf("%d\n",all_queue.top().d);break;
			}
			if(!flag) puts("They have disappeared.");
		}
		else{
			int x;x=getInt();col[x]=!col[x];
			while(top[x]!=1){
			update(tree[bh[x]],num[x],x);
				x=fa[top[x]];
			}
			update(tree[bh[x]],num[x],x);
		}
	}
	return 0;
}
