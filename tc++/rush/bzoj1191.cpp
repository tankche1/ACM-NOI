# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
int n,m;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int vis[maxn],left[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

bool dfs(int x){
	if(vis[x]) return false;
	vis[x]=1;
	for(int e=first[x];e!=-1;e=next[e]){
		if((!left[v[e]])||dfs(left[v[e]])){
			left[v[e]]=x;
			return true;
		}
	}
	return false;
}

int main(){
	scanf("%d%d",&n,&m);
	int a,b;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);a++;b++;
		add_edge(i,a);if(b!=a) add_edge(i,b);
	}
	int ans=0;
	memset(left,0,sizeof(left));
	for(int i=1;i<=m;i++){
		memset(vis,0,sizeof(vis));
		if(dfs(i)) ans++;
			else break;
	}
	printf("%d\n",ans);
	return 0;
}
