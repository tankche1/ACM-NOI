# include<stdio.h>
# include<string.h>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=200010;
int n,k;
vector<int> tuan[maxn];
int col[maxn],fa[maxn],first[maxn],next[maxn],v[maxn],edge;
int maxd[maxn],depth[maxn],bh[maxn];//第i种颜色到根的最远距离 i到根的距离
int dp[maxn][18];
int Step=17;
int Two[19];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int x,int dep){
	depth[x]=dep;
	if(depth[x]>maxd[col[x]]) maxd[col[x]]=depth[x],bh[col[x]]=x;
	for(int e=first[x];e!=-1;e=next[e])
		dfs(v[e],dep+1);
}

void prepare(){
	for(int i=1;i<=n;i++)
		dp[i][0]=fa[i];
	for(int j=1;j<=Step;j++)
		for(int i=1;i<=n;i++)
			dp[i][j]=dp[dp[i][j-1]][j-1];
}

int lca(int a,int b){
	int j=Step;
	int ans=0;
	if(depth[a]<depth[b]) swap(a,b);
	int t=depth[a]-depth[b];
	for(int j=Step;j>=0;j--)
		if(t&(1<<j)) ans+=Two[j],a=dp[a][j];
	while(a!=b){
		while(j>0&&dp[a][j]==dp[b][j]) j--;
		a=dp[a][j];b=dp[b][j];ans+=Two[j]<<1;
	}
	return ans;
}

int main(){
	Two[0]=1;
	for(int i=1;i<=Step;i++) Two[i]=Two[i-1]<<1;
	scanf("%d%d",&n,&k);
	int root;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=n;i++){
		scanf("%d%d",&col[i],&fa[i]);tuan[col[i]].push_back(i);
		if(fa[i]==0) root=i;
		else add_edge(fa[i],i);
	}
	fa[root]=root;
	memset(maxd,0,sizeof(maxd));
	dfs(root,0);
	prepare();
	for(int i=1;i<=k;i++){
		int x=bh[i];
		int ans=0;
		for(int j=0;j<tuan[i].size();j++)
			if(x!=tuan[i][j])
				ans=max(ans,lca(x,tuan[i][j]));
		printf("%d\n",ans);
	}
	return 0;
}
