# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxm=10010;
const int maxn=110;
int m,n;
bool Win[maxm],vis[maxm];int p[maxm];
char s[maxn][maxn];
inline int pos(int x,int y) {return (x-1)*n+y;}
int first[maxm],next[maxm<<2],v[maxm<<2],edge=0;
void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void Retravel(int x){
	if(vis[x]) return;
	vis[x]=Win[x]=1;
	for(int e=first[x];e!=-1;e=next[e]){
		Retravel(p[v[e]]);
	}
}

bool dfs(int x){
	for(int e=first[x];e!=-1;e=next[e]){
		if(vis[v[e]]) continue;vis[v[e]]=true;
		if(!p[v[e]]||dfs(p[v[e]])){
			p[v[e]]=x,p[x]=v[e];return true;
		}
	}
	return false;
}

int main(){
	char t;
	scanf("%d%d",&m,&n);
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++){
			while((t=getchar())&&t!='.'&&t!='#');
			s[i][j]=t;
		}
	memset(first,-1,sizeof(first));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='.'){
				if(i!=m&&s[i+1][j]=='.')
					add_edge(pos(i,j),pos(i+1,j)),add_edge(pos(i+1,j),pos(i,j));
				if(j!=n&&s[i][j+1]=='.') add_edge(pos(i,j),pos(i,j+1)),add_edge(pos(i,j+1),pos(i,j));
			}
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='.'&&!p[pos(i,j)]) memset(vis,0,sizeof(vis)),dfs(pos(i,j));
	memset(vis,0,sizeof(vis));
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='.'&&!p[pos(i,j)]) Retravel(pos(i,j));
	bool ok=false;
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='.'&&Win[pos(i,j)]) ok=true;
	if(ok) puts("WIN");
		else puts("LOSE");
	for(int i=1;i<=m;i++)
		for(int j=1;j<=n;j++)
			if(s[i][j]=='.'&&Win[pos(i,j)]) printf("%d %d\n",i,j);
	return 0;
}
