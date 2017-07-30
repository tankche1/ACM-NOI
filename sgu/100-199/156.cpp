# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxm=100010;
int first[maxn],next[maxm<<1],v[maxm<<1],deg[maxn],edge,dev[maxn];
int _first[maxn],_next[maxm<<1],_v[maxm<<1];bool used[maxm<<1];
int n,m;
vector<int> ans;
int belong[maxn];int bsize=0;
int have[maxn];

struct EDGE{
	int v;bool used;
	EDGE(int v=0,bool used=0):v(v),used(used) {}
};
vector<EDGE> G[maxn];

void add_edge(int a,int b){
	v[edge]=b;
	next[edge]=first[a];
	first[a]=edge++;
}

void dfs(int u){
	for(int e=first[u];e!=-1;e=next[e]){
		if(used[e]) continue;
		//dev[u]--;
		ans.push_back(u);//dev[G[u][e].v]--;
		used[e]=used[e^1]=1;
		dfs(v[e]);
	}
}

void print(int e,bool go){
		//printf("e:%d go:%d\n",e,go);
	if(e==ans.size()) {
		if(!have[ans[0]]){
			int x=have[ans[e-1]];
			for(int ed=_first[x];ed!=-1;ed=_next[ed])
				if(belong[_v[ed]]==ans[0])
					printf("%d ",_v[ed]);
			}
			return;
		}
	int x=ans[e];
	if(have[x]){
		printf("%d ",have[x]);print(e+1,0);return;
	}
	if(!go){
		int u=have[ans[e-1]];
		for(int ed=_first[u];ed!=-1;ed=_next[ed])
			if(belong[_v[ed]]==x)
				printf("%d ",_v[ed]);
		print(e,1);return;
	}
	else{
		int u=have[ans[e+1]];
		//if(e==ans.size()-1) u=have[ans[0]];
		for(int ed=_first[u];ed!=-1;ed=_next[ed])
			if(belong[_v[ed]]==x)
				printf("%d ",_v[ed]);
		print(e+1,0);return;
	}
}

int main(){
	int a,b;
	edge=0;memset(first,-1,sizeof(first));
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);add_edge(a,b);add_edge(b,a);deg[a]++;deg[b]++;
	}
	for(int i=1;i<=n;i++)
		if(deg[i]>=3&&(!belong[i])){
			belong[i]=++bsize;
			for(int e=first[i];e!=-1;e=next[e])
				if(deg[v[e]]>=3)
					belong[v[e]]=bsize;
		}memset(have,0,sizeof(have));
	for(int i=1;i<=n;i++)
		if(deg[i]==2)
			belong[i]=++bsize,have[bsize]=i;//for(int i=1;i<=n;i++) printf("belong[%d]:%d\n",i,belong[i]);
	memset(dev,0,sizeof(dev));
	memcpy(_first,first,sizeof(first));memcpy(_v,v,sizeof(v));memcpy(_next,next,sizeof(next));
			//for(int i=1;i<=n;i++) _first[i]=first[i];for(int i=0;i<edge;i++) _v[i]=v[i],_next[i]=next[i];
		memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=n;i++)
		if(deg[i]==2){
			for(int e=_first[i];e!=-1;e=_next[e]){
				if(deg[_v[e]]>=3||_v[e]>i)
					dev[belong[i]]++,dev[belong[_v[e]]]++,//printf("%d %d\n",belong[i],belong[_v[e]]),
					add_edge(belong[i],belong[_v[e]]),add_edge(belong[_v[e]],belong[i]);
			}
		}memset(used,false,sizeof(used));
	for(int i=1;i<=bsize;i++)
		if(dev[i]&1){puts("-1");return 0;}
	for(int i=1;i<=bsize;i++)
	if(have[i])	{
	dfs(i);break;}
	reverse(ans.begin(),ans.end());
	//	for(int i=0;i<ans.size();i++) printf("%d ",ans[i]);puts("");
	print(0,1);puts("");
	return 0;
}
/*
14 22
1 5
1 4
4 6
1 2
1 3
2 3
3 4
2 4
2 8
3 7
7 8
6 10
5 9
9 12
12 14
14 13
13 11
11 12
11 9
9 10
11 10
10 12

11 14
1 2
1 3
1 6
2 3
2 4
3 5
4 5
6 7
7 8
7 9
8 9
8 10
9 11
10 11

8 12
1 2
1 3
2 4
3 4
4 5
2 5
5 6
5 7
2 6
4 6
6 8
7 8
*/
