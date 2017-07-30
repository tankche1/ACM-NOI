# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n,k,m;
int first[maxn],next[maxn*2],v[maxn*2],cost[maxn*2];
int ans,num;
bool vis[maxn];
int size[maxn],maxsize[maxn],root,Max;
int dist[maxn];

void add_edge(int a,int b,int c){
	next[m]=first[a];
	first[a]=m;
	v[m]=b;
	cost[m++]=c;
}

void dfs_size(int x,int fa){
	int tot=1;maxsize[x]=0;
	for(int e=first[x];e!=-1;e=next[e]){
		if(vis[v[e]]||v[e]==fa) continue;
		dfs_size(v[e],x);
		tot+=size[v[e]];
		maxsize[x]=max(maxsize[x],size[v[e]]);
	}
	size[x]=tot;
}

void dfs_root(int ancestor,int x,int fa){
	if(size[ancestor]-size[x]>maxsize[x]) maxsize[x]=size[ancestor]-size[x];
	if(maxsize[x]<Max) root=x,Max=maxsize[x];
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa||vis[v[e]]) continue;
		dfs_root(ancestor,v[e],x);
	}
}

void dfs_dis(int x,int fa,int d){
	dist[num++]=d;
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vis[v[e]]&&v[e]!=fa) dfs_dis(v[e],x,d+cost[e]);
	}
}

int Calc(int x,int d){
	int dis=0;
	num=0;
	dfs_dis(x,0,d);
	sort(dist,dist+num);
	int i=0,j=num-1;
	while(i<j){
		while(i<j&&dist[i]+dist[j]>k) j--;
			dis+=j-i;
		i++;
	}
	return dis;
}

void dfs(int x){
	Max=n;
	dfs_size(x,0);
	dfs_root(x,x,0);
	ans+=Calc(root,0);
	vis[root]=true;
	for(int e=first[root];e!=-1;e=next[e]){
		if(vis[v[e]]) continue;
		ans-=Calc(v[e],cost[e]);
		dfs(v[e]);
	}
}

int main(){
	int a,b,c;
	while(scanf("%d%d",&n,&k)!=EOF){
		if(!n) break;
	memset(first,-1,sizeof(first));m=0;
	for(int i=1;i<n;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	ans=0;
	memset(vis,false,sizeof(vis));
	dfs(1);
	printf("%d\n",ans);
}
	return 0;
}
