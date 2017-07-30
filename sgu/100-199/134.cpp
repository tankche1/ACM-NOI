# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=17000;
const int INF=maxn;
int n;
int first[maxn],next[maxn<<1],v[maxn<<1],edge=0;
vector<int> ans;int res=INF;
int size[maxn];
void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int u,int fa){
	size[u]=1;int msize=0;
	for(int e=first[u];e!=-1;e=next[e])
		if(v[e]!=fa) dfs(v[e],u),size[u]+=size[v[e]],msize=max(msize,size[v[e]]);
	msize=max(msize,n-size[u]);
	if(msize<res)
		res=msize,ans.clear(),ans.push_back(u);
	else if(msize==res)
		ans.push_back(u);
}

int main(){
	int a,b;
	scanf("%d",&n);
	edge=0;memset(first,-1,sizeof(first));
	for(int i=1;i<n;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	dfs(1,0);sort(ans.begin(),ans.end());
	printf("%d %d\n%d",res,ans.size(),ans[0]);
	for(int i=1;i<ans.size();i++)
		printf(" %d",ans[i]);puts("");
	return 0;
}
