#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;
int start[maxn],end[maxn];
vector<int> ans;

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int x,int fa,int dep,int change0,int change1){
	//printf("x:%d fa:%d dep:%d change0:%d change1:%d\n",x,fa,dep,change0,change1);
	int now;
	if(dep==0&&change0) now=start[x]^1;
	else if(dep&&change1) now=start[x]^1;
	else now=start[x];
	if(now!=end[x]) {
		ans.push_back(x);
		for(int e=first[x];e!=-1;e=next[e])
			if(v[e]!=fa){
				if(dep==0) dfs(v[e],x,dep^1,change0^1,change1);
				else dfs(v[e],x,dep^1,change0,change1^1);
			}
	}
	else
		for(int e=first[x];e!=-1;e=next[e])
			if(v[e]!=fa){
				dfs(v[e],x,dep^1,change0,change1);
			}
}

int main(){
	int a,b;
	scanf("%d",&n);
	memset(first,-1,sizeof(first));
	for(int i=1;i<n;i++)
		scanf("%d%d",&a,&b),add_edge(a,b),add_edge(b,a);
	for(int i=1;i<=n;i++) scanf("%d",&start[i]);
	for(int i=1;i<=n;i++) scanf("%d",&end[i]);
	dfs(1,0,0,0,0);
	printf("%d\n",ans.size());
	sort(ans.begin(),ans.end());
	for(int i=0;i<ans.size();i++)
		printf("%d\n",ans[i]);
	return 0;
}
