# include<stdio.h>
# include<string.h>
# include<algorithm>
# include<vector>
using namespace std;
const int maxn=10010;
const int INF=~0U>>1;
int weight[maxn],n;

struct IntervalTree{
	int Max[maxn<<1];
	
	void pushup(int o){
		Max[o]=max(Max[o<<1],Max[o<<1|1]);
	}
	
	void build(int o,int L,int R){
		if(L==R){
			Max[o]=weight[L];
		}
		else{
			int M=(L+R)>>1;
			build(o<<1,L,M);
			build(o<<1|1,M+1,R);
			pushup(o);
		}
	//	printf("o:%d L:%d R:%d Max:%d\n",o,L,R,Max[o]);
	}
	
	void change(int o,int L,int R,int goal,int val){
		if(L==R&&goal==L){
			Max[o]=val;
		}
		else{
			int M=(L+R)>>1;
			if(goal<=M)
				change(o<<1,L,M,goal,val);
			else change(o<<1|1,M+1,R,goal,val);
			pushup(o);
		}
	}
	
	int query(int o,int L,int R,int qL,int qR){
		if(qL<=L&&qR>=R){
			return Max[o];
		}
		int M=(L+R)>>1;
		int ans=-INF;
		if(qL<=M) ans=max(ans,query(o<<1,L,M,qL,qR));
		if(qR>M) ans=max(ans,query(o<<1|1,M+1,R,qL,qR));
		return ans;
	}
	
	int find(int qL,int qR){
		if(qL>qR) return -INF;
		return query(1,1,n,qL,qR);
	}
	
};
IntervalTree tree;

int getInt(){
	int ans=0;char t;bool sign=true;
	while((t=getchar())&&(t<'0'||t>'9')&&t!='-');
	if(t=='-') sign=false,t=getchar();
	do{
		ans=ans*10+t-'0';
		t=getchar();
	}while(t>='0'&&t<='9');
	if(!sign) ans=-ans;
	return ans;
}

int first[maxn],next[maxn<<1],cost[maxn<<1],v[maxn<<1],m;
int x[maxn],y[maxn];

void add_edge(int a,int b,int c){
	next[m]=first[a];
	first[a]=m;
	v[m]=b;
	cost[m++]=c;
}

int size[maxn];
int son[maxn],fa[maxn];

void dfs_size(int x){
	size[x]=1;son[x]=-1;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]!=fa[x]){
			fa[v[e]]=x;
			dfs_size(v[e]);size[x]+=size[v[e]];
			if(son[x]==-1||size[v[e]]>size[son[x]]) son[x]=v[e];
		}
	}
}

int dfn[maxn],dfs_clock;
int top[maxn];int dep[maxn];

void dfs_build(int x,int anc){
	dfn[x]=++dfs_clock;top[x]=anc;
	if(son[x]!=-1) {dep[son[x]]=dep[x]+1;dfs_build(son[x],anc);}
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==son[x]) weight[dfn[v[e]]]=cost[e];
		if(v[e]!=son[x]&&v[e]!=fa[x]){
			dep[v[e]]=dep[x]+1;
			dfs_build(v[e],v[e]);weight[dfn[v[e]]]=cost[e];
		}
	}
}

int QUERY(int a,int b){
	int ta=top[a],tb=top[b];
	int ans=-INF;
	while(ta!=tb){
		if(dep[ta]<dep[tb]){
			swap(a,b);swap(ta,tb);
		}
		ans=max(ans,tree.query(1,1,n,dfn[ta],dfn[a]));
		a=fa[ta];
		ta=top[a];
	}
	if(dep[a]>dep[b]) swap(a,b);
	//	printf("dfn[%d]:%d dfn[%d]:%d dep[%d]:%d dep[%d]:%d\n",a,dfn[a],b,dfn[b],a,dep[a],b,dep[b]);
	ans=max(ans,tree.find(dfn[a]+1,dfn[b]));
	return ans;
}

char op[10];
int w;
int main(){
	int tcase;
	tcase=getInt();
	while(tcase--){
		m=0;
		n=getInt();
		memset(first,-1,sizeof(first));
		for(int i=1;i<n;i++){
			x[i]=getInt();y[i]=getInt();w=getInt();
			add_edge(x[i],y[i],w);
			add_edge(y[i],x[i],w);
		}
		fa[1]=0;dfs_clock=0;weight[1]=-INF;dep[1]=0;
		dfs_size(1);
		dfs_build(1,1);
		//for(int i=1;i<=n;i++) printf("dfn[%d]:%d weight[%d]:%d\n",i,dfn[i],i,weight[i]);
		tree.build(1,1,n);
		for(;;){
			scanf("%s",op);
			//puts(op);
			if(op[0]=='C'){
				int num=getInt(),new_weight=getInt();
				int a=fa[x[num]]==y[num]?x[num]:y[num];
				tree.change(1,1,n,dfn[a],new_weight);
			}
			else if(op[0]=='Q'){
				int a=getInt(),b=getInt();
				//printf("%d %d\n",a,b);
				if(a==b) printf("0\n");
					else
				printf("%d\n",QUERY(a,b));
			}
			else
				break;
		}
	}
	return 0;
}
