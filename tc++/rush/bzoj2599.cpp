#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=200010;
const int maxlen=1000010;
int n,k;
int first[maxn],next[maxn<<1],v[maxn<<1],w[maxn<<1],edge,size[maxn];
bool vis[maxn];
int root,bson;
int stack[maxn],h[maxlen],top;
int ans=INF,nowsize;

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	first[a]=edge;
	v[edge]=b;
	w[edge]=c;
	edge++;
}

void dfs_size(int x,int fa){
	size[x]=1;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa||vis[v[e]]) continue;
		dfs_size(v[e],x);
		size[x]+=size[v[e]];
	}
}

void find_root(int x,int fa){
	int big=nowsize-size[x];
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa&&!vis[v[e]]){
			find_root(v[e],x);
			big=max(big,size[v[e]]);
		}
	if(big<bson) bson=big,root=x;
}

void dfs1(int x,int fa,int weight,int len){
	if(weight>k) return;
	if(h[k-weight]!=-1&&h[k-weight]+len<ans) ans=h[k-weight]+len;
	for(int e=first[x];e!=-1;e=next[e])
		if(!vis[v[e]]&&v[e]!=fa){
			dfs1(v[e],x,weight+w[e],len+1);
		}
}

void dfs2(int x,int fa,int weight,int len){
	if(weight>k) return;
	if(h[weight]==-1) stack[++top]=weight;
	if(h[weight]==-1||h[weight]>len) h[weight]=len;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa&&!vis[v[e]])
			dfs2(v[e],x,weight+w[e],len+1);
}

void clear(){
	while(top>=0)
		h[stack[top--]]=-1;
}

void calc(int x){
	//printf("x:%d\n",x);
	dfs_size(x,-1);
	bson=nowsize=size[x];
	find_root(x,-1);
	x=root;
	vis[x]=true;
	clear();stack[++top]=0;h[0]=0;
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vis[v[e]]){
			dfs1(v[e],x,w[e],1);
			dfs2(v[e],x,w[e],1);
		}
	}
	for(int e=first[x];e!=-1;e=next[e]){
		if(vis[v[e]]) continue;
		calc(v[e]);
	}
}

int main(){
	int a,b,c;
	scanf("%d%d",&n,&k);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);add_edge(a,b,c);add_edge(b,a,c);
	}
	top=-1;memset(h,-1,sizeof(h));
	calc(1);
	if(ans==INF) puts("-1");
		else 
	printf("%d\n",ans);
	return 0;
}
