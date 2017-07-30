#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=10010;
int left[maxn];
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int n;
int ans[maxn];
bool vis[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

bool dfs(int x){
	vis[x]=1;
	for(int e=first[x];e!=-1;e=next[e]){
		if(left[v[e]]==-1||(!vis[left[v[e]]]&&dfs(left[v[e]]))){
			left[v[e]]=x;return true;
		}
	}
	return false;
}

int main(){
	int x;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=0;i<n;i++){
		scanf("%d",&x);
		int a=(i+x)%n,b=(i-x+n)%n;
		if(a<b) swap(a,b);
		add_edge(i,a);add_edge(i,b);
	}
	memset(left,-1,sizeof(left));memset(vis,false,sizeof(vis));
	for(int i=n-1;i>=0;i--){
		memset(vis,0,sizeof(vis));
		if(!dfs(i)) {puts("No Answer");return 0;}
	}
	for(int i=0;i<n;i++)
		ans[left[i]]=i;
	for(int i=0;i<n-1;i++)
		printf("%d ",ans[i]);
	printf("%d",ans[n-1]);
	puts("");
	return 0;
}
