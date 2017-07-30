#include<stdio.h>
#include<string.h>
# include<map>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=300100;
typedef pair<int,int> pi;
map<pi,bool> id;
int n,m;
int first[maxn],next[maxm],v[maxm],edge=0;
vector<int> G[maxn];

void add_edge(int a,int b){
	v[edge]=b;
	next[edge]=first[a];
	first[a]=edge++;
}

int dfn[maxn],low[maxn],dfs_clock=0,stack[maxn],top=-1,belong[maxn],kuai=0;
int in[maxn],out[maxn],size[maxn];

void dfs(int x){
	dfn[x]=low[x]=++dfs_clock;stack[++top]=x;
	//printf("x:%d dfn:%d\n",x,dfn[x]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(!dfn[v[e]])
			dfs(v[e]),low[x]=min(low[x],low[v[e]]);
		else if(!belong[v[e]])
			low[x]=min(low[x],dfn[v[e]]);
	}
	//printf("low[%d]:%d\n",x,low[x]);
	if(low[x]==dfn[x]){
	//	printf("xx:%d\n",x);
		kuai++;size[kuai]=0;
		int u;
		do{
			u=stack[top--];
			belong[u]=kuai;size[kuai]++;
		}while(u!=x);
	}
}

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);add_edge(a,b);
	}
	
	memset(dfn,0,sizeof(dfn));dfs_clock=0;
	for(int i=1;i<=n;i++)
		if(!dfn[i]) dfs(i);
	//for(int i=1;i<=n;i++) printf("belong[%d]:%d\n",i,belong[i]);
	for(int i=1;i<=n;i++)
		for(int e=first[i];e!=-1;e=next[e])
			if(belong[i]!=belong[v[e]]&&!id.count(pi(belong[i],belong[v[e]]))) 
				in[belong[v[e]]]++,out[belong[i]]++,G[belong[i]].push_back(belong[v[e]]),id[pi(belong[i],belong[v[e]])]=1;
	int ans=0;
	bool ok=false;
	for(int i=1;i<=kuai;i++)
		if(in[i]==0) {
			ans++;
		}
	//	printf("ans:%d\n",ans);
	if(ans>1)
	for(int i=1;i<=kuai;i++)
		if(in[i]==0&&size[i]==1) {
			//ok=1;continue;
				bool tank=true;
				for(int e=0;e<G[i].size();e++){
					if(in[G[i][e]]==1) tank=false;
				}
				if(tank) {ok=true;break;}
		}
	ans-=ok;
	printf("%.6lf\n",(double)1-((double)ans/(n*1.0)));
	return 0;
}
