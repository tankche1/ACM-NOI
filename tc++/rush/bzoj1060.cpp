# include<stdio.h>
# include<string.h>
# include<stack>
# include<algorithm>
# define FUCK printf("fuck\n");
using namespace std;
typedef long long LL;
const int maxn=500010;
int first[maxn],next[2*maxn],v[2*maxn],dist[2*maxn],edge=0;
LL dis[maxn];
int fa[maxn],fa_dist[maxn];
int n,root;

struct state{
	int x,edge_num;
	LL add;
	
	void give(int a,int b){
		x=a;edge_num=b;
	}
	
	void give(int a,int b,LL  c){
		x=a;edge_num=b;add=c;
	}
};

void add_edge(int from,int to,int c){
	next[edge]=first[from];
	v[edge]=to;
	dist[edge]=c;
	first[from]=edge++;
}

bool isleaf[maxn];
stack<state> q;

void dfs_dis(){
	fa[root]=0;fa_dist[root]=0;
	state node;
	node.give(root,first[root]);
	q.push(node);
	for(int i=1;i<=n;i++) isleaf[i]=true;
	memset(dis,0,sizeof(dis));
	while(!q.empty()){
		loop:
		int x=q.top().x;
		for(int e=q.top().edge_num;e!=-1;e=next[e]){
			if(v[e]!=fa[x]){
				isleaf[x]=false;
				fa[v[e]]=x;fa_dist[v[e]]=dist[e];
				node.give(v[e],first[v[e]]);
				q.top().edge_num=next[e];
				q.push(node);
				goto loop;
			}
		}
		dis[fa[x]]=max((LL)(dis[x]+fa_dist[x]),dis[fa[x]]);
		q.pop();
	}
}
LL ans;

void dfs_solve(){
	LL add;
	ans=0;
	state node;
	node.give(root,first[root],0);
	q.push(node);
	while(!q.empty()){
		labelA:
		int x=q.top().x;
		for(int e=q.top().edge_num;e!=-1;e=next[e]){
			if(v[e]==fa[x]) continue;
			add=dis[root]-(LL)(q.top().add+dis[v[e]]+dist[e]);
			ans+=add;
			node.give(v[e],first[v[e]],(LL)(add+dist[e]+q.top().add));
			q.top().edge_num=next[e];
			q.push(node);
			goto labelA;
		}
		q.pop();
	}
	printf("%lld\n",ans);
}

int main(){
	//freopen("input.txt","r",stdin);
	scanf("%d%d",&n,&root);
	edge=0;memset(first,-1,sizeof(first));
	int a,b,c;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	dfs_dis();
	dfs_solve();
	return 0;
}
