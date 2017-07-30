#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
typedef long long LL;
int n,m;
LL x[maxn],y[maxn];
int stack[maxn],top;
const int Step=17;
int dp[maxn][Step+1];
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int Two[Step+1];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

bool Slope(LL xA,LL yA,LL xB,LL yB,LL xC,LL yC){//kAB>kBC
	return (yB-yA)*(xC-xB)>(yC-yB)*(xB-xA);
}
int dep[maxn],fa[maxn];

void dfs(int x,int fa){
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa)
			dep[v[e]]=dep[x]+1,dfs(v[e],x);
}

int LCA(int a,int b){
	if(dep[a]<dep[b]) swap(a,b);
	int t=dep[a]-dep[b];
	for(int j=Step;j>=0;j--)
		if(t&Two[j]) t-=Two[j],a=dp[a][j];
	int j=Step;
	while(a!=b){
		while(j>0&&dp[a][j]==dp[b][j]) j--;
		a=dp[a][j];b=dp[b][j];
		//printf("a:%d b:%d\n",a,b);
	}
	return a;
}

int main(){
	Two[0]=1;for(int i=1;i<=Step;i++) Two[i]=Two[i-1]<<1;
	scanf("%d",&n);
	for(int i=1;i<=n;i++)
		scanf("%lld%lld",&x[i],&y[i]);
	fa[n]=n;
	stack[top=0]=n;
	memset(first,-1,sizeof(first));edge=0;
	for(int i=n-1;i>=1;i--){
		int L=0,R=top-1;
		while(L<=R){
			int M=(L+R)>>1;
			if(Slope(x[i],y[i],x[stack[M]],y[stack[M]],x[stack[M+1]],y[stack[M+1]])) R=M-1;
			else L=M+1;
		}
		fa[i]=stack[R+1];
		//printf("fa[%d]:%d\n",i,fa[i]);
		add_edge(fa[i],i);add_edge(i,fa[i]);
		while(top&&!Slope(x[i],y[i],x[stack[top]],y[stack[top]],x[stack[top-1]],y[stack[top-1]])) top--;
		stack[++top]=i;
	}dep[n]=0;
	dfs(n,-1);
	for(int i=1;i<=n;i++)
		dp[i][0]=fa[i];
	for(int i=1;i<=Step;i++){
		for(int j=1;j<=n;j++){
			dp[j][i]=dp[dp[j][i-1]][i-1];
			//printf("dp[%d][%d]:%d\n",j,i,dp[j][i]);
		}
	}
	scanf("%d",&m);
	int a,b;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		printf("%d ",LCA(a,b));
	}puts("");
	return 0;
}
