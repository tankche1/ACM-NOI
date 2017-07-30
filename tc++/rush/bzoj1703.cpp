# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=10010;
int first[maxn],next[maxm],v[maxm],edge;
bool vis[maxn];
int n,m,ans;
void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int x){
	ans--;vis[x]=true;
	for(int e=first[x];e!=-1;e=next[e])  if(!vis[v[e]]) dfs(v[e]);
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	//memset(in,0,sizeof(in));
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);
		//in[b]++;
	}
	ans=n*(n-1)/2;
	for(int i=1;i<=n;i++){
		memset(vis,false,sizeof(vis));
		dfs(i);ans++;
	}
	printf("%d\n",ans);
	return 0;
}
