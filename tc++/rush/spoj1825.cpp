# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=200010;
const int INF=2000000001;
int n,k,m;
bool black[maxn],vis[maxn];
int first[maxn],next[maxn<<1],v[maxn<<1],edge,w[maxn<<1];
int size[maxn];
int root,Max;
int dep[maxn];
int f[maxn],g[maxn];
int ans;

struct state{
	int bh,dist;
};
state st[maxn];

bool cmp(state a,state b){
	return dep[a.bh]<dep[b.bh];
}

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	first[a]=edge;
	v[edge]=b;
	w[edge++]=c;
}

void dfs_size(int x,int fa){
	size[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(!vis[v[e]]&&v[e]!=fa){
			dfs_size(v[e],x);
			size[x]+=size[v[e]];
		}
}

void dfs_root(int x,int fa,int ancestor){
	int maxx=size[ancestor]-size[x];
	
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vis[v[e]]&&v[e]!=fa) {dfs_root(v[e],x,ancestor);maxx=max(maxx,size[v[e]]);}
	}
	if(Max>maxx) Max=maxx,root=x;
}

void dfs_dep(int x,int fa){
	dep[x]=black[x];
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vis[v[e]]&&v[e]!=fa){
			dfs_dep(v[e],x);
			dep[x]=max(dep[x],dep[v[e]]+black[x]);
		}
	}
}

void dfs_dist(int x,int fa,int dot,int dis){
	f[dot+black[x]]=max(f[dot+black[x]],dis);
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vis[v[e]]&&v[e]!=fa){
			dfs_dist(v[e],x,dot+black[x],dis+w[e]);
		}
	}
}

void dfs(int x){
	//printf("x:%d\n",x);
	Max=n;
	dfs_size(x,0);
	dfs_root(x,0,x);
	vis[root]=true;
	dfs_dep(root,0);
	int num=0;
	for(int e=first[root];e!=-1;e=next[e]){
		if(!vis[v[e]]) {st[num].bh=v[e];st[num++].dist=w[e];}
	}
	sort(st,st+num,cmp);
	memset(g,0,sizeof(g));
	g[0]=-INF;
	for(int i=0;i<num;i++){
		int v=st[i].bh,dis=st[i].dist;
		for(int j=0;j<=dep[v];j++) f[j]=0;
		if(black[v]) f[0]=-INF;
		dfs_dist(v,root,0,0);
			if(i){
				for(int j=0;j<=dep[v];j++){
					if(j+black[root]<=k){
						if(min(dep[st[i-1].bh],k-j-black[root])==0&&g[0]==-INF) continue;
						ans=max(ans,f[j]+dis+g[min(dep[st[i-1].bh],k-j-black[root])]);
					}
				}
		}
		if(f[0]!=-INF) g[0]=max(f[0]+dis,g[0]);
		for(int j=1;j<=dep[v];j++){
			if(f[j]>g[j]-dis) g[j]=f[j]+dis;//由根节点往下经过不超过j个黑点（不算根节点）的最优距离
		}
		for(int j=1;j<=dep[v];j++)
			g[j]=max(g[j],g[j-1]);
	}
	if(num>0)
	for(int j=0;j+black[root]<=k&&j<=dep[root]-black[root];j++)//由根节点往下的一条链
		ans=max(ans,g[j]);
	//for(int j=0;j<=dep[root]-black[root];j++)
	//	printf("g[%d]:%d\n",j,g[j]);
	for(int e=first[root];e!=-1;e=next[e]){
		if(!vis[v[e]]) dfs(v[e]);
	}
}

int readint(){
	char t;
	while((t=getchar())&&(t<'0'||t>'9')&&t!='-');
		bool sign=true;
	if(t=='-') sign=false,t=getchar();
		int res=0;
	do{
		res=res*10+(t-'0');
		t=getchar();
	}while(t>='0'&&t<='9');//printf("%d\n",res);
	if(!sign) res=-res;
	return res;
}

int main(){
	//freopen("input.txt","r",stdin);
	int a,b,c,x;
	n=readint();k=readint();m=readint();
	for(int i=1;i<=m;i++){
		//scanf("%d",&x);
		x=readint();
		black[x]=1;
	}
	//memset(vis,false,sizeof(vis));
	memset(first,-1,sizeof(first));
	edge=0;
	for(int i=1;i<n;i++){
		//scanf("%d%d%d",&a,&b,&c);
		a=readint();b=readint();c=readint();
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	ans=0;
	dfs(1);
	printf("%d\n",ans);
	return 0;
}
