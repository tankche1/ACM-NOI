# include<stdio.h>
# include<queue>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=40010;
int n,m;
int first[maxn],next[maxn<<1],v[maxn<<1],w[maxn<<1],edge;
int fa[maxn],size[maxn];
bool used[maxn];
int num;

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

void dfs_size(int x){
	size[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa[x]) fa[v[e]]=x,dfs_size(v[e]),size[x]+=size[v[e]];
}

void choose(int &x){
	int mx=0,son;
	for(int e=first[x];e!=-1;e=next[e]){
		if(!used[v[e]]&&size[v[e]]>mx)
			mx=size[v[e]],son=v[e];
	}
	if(mx>num/2){
		fa[x]=son;size[x]-=size[son];size[son]+=size[x];fa[son]=0;
		x=son;
		choose(x);
	}
}

int dist[maxn],cnt;
typedef pair<int,int> pi;

int cal(int root,int dis){
	cnt=0;
	queue<pi> Q;
	Q.push(pi(root,dis));
	while(!Q.empty()){
		pi now=Q.front();Q.pop();dist[cnt++]=now.second;
		for(int e=first[now.first];e!=-1;e=next[e]){
			if(v[e]!=fa[now.first]&&!used[v[e]])
				Q.push(pi(v[e],now.second+w[e]));
		}
	}
	sort(dist,dist+cnt);
	//printf("root:%d dis:%d\n",root,dis);for(int i=0;i<cnt;i++) printf("%d ",dist[i]);puts("");
	int tail=cnt-1;
	int res=0;
	for(int i=0;i<tail;i++){
		while(tail>i&&dist[tail]+dist[i]>m) tail--;
		res+=tail-i;
	}
	//printf("res:%d\n",res);
	return res;
}

int ans=0;
void solve(int x){
	num=size[x];
	if(num==1) return;
	choose(x);//printf("x:%d\n",x);
	ans+=cal(x,0);
	for(int e=first[x];e!=-1;e=next[e])
		if(!used[v[e]])
			ans-=cal(v[e],w[e]);
	used[x]=1;
	for(int e=first[x];e!=-1;e=next[e]){
		if(!used[v[e]]) solve(v[e]);
	}
}

int main(){
	int a,b,c;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<n;i++)
		scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
	scanf("%d",&m);
	fa[1]=0;
	dfs_size(1);memset(used,false,sizeof(used));
	solve(1);
	printf("%d\n",ans);
	return 0;
}
