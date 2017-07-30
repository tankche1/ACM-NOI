# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100010;
int n,m;

int first[maxn],v[maxn],next[maxn],edge;
void init(){memset(first,-1,sizeof(first));}

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

void add_edge(int a,int b){
	v[edge]=b;
	next[edge]=first[a];
	first[a]=edge++;
}

int x[maxn],y[maxn];
int main()
{
	queue<int> Q;
	int tcase,a,b;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d",&n,&m);
		init();edge=0;
		for(int i=1;i<=m;i++){
			scanf("%d%d",&a,&b);a++;b++;
			x[i]=a;y[i]=b;
			add_edge(a,b);
		}
		top=-1;memset(belong,0,sizeof(belong));kuai=0;
		memset(dfn,0,sizeof(dfn));dfs_clock=0;
		for(int i=1;i<=n;i++)
			if(!dfn[i]) dfs(i);
	//	for(int i=1;i<=n;i++) printf("belong[%d]:%d\n",i,belong[i]);
		memset(in,0,sizeof(in));memset(out,0,sizeof(out));
		for(int i=1;i<=m;i++){
			if(belong[x[i]]!=belong[y[i]])
				out[belong[x[i]]]++,in[belong[y[i]]]++;
		}
		
		int ans=0,tt;
		for(int i=1;i<=kuai;i++)
			if(in[i]==0) ans++,tt=i;
		if(ans>1) puts("Confused");
		else{
			for(int i=1;i<=n;i++) if(belong[i]==tt) printf("%d\n",i-1);
		}
		puts("");
	}
	return 0;
}
