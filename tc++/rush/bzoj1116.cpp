#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=200010;
int n,m;
int first[maxn],next[maxm<<1],v[maxm<<1],edge;
bool ok=true;
bool vis[maxn];
int point;

void add_edge(int a,int b){next[edge]=first[a];v[edge]=b;first[a]=edge++;}

void dfs(int x){
	vis[x]=1;point++;
	for(int e=first[x];e!=-1;e=next[e]){
		edge++;
		if(!vis[v[e]])
			dfs(v[e]);
	}
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			point=0;edge=0;
			dfs(i);edge>>=1;
			if(edge<point) {ok=false;break;}
		}
		if(ok) puts("TAK");
			else puts("NIE");
	return 0;
}
