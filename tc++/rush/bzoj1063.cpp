# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=100010;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
LL dp[maxn][11][3];
int n,m,mod;
int Q[maxn],head,tail;
bool vis[maxn];
int fa[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void BFS(){
	memset(vis,false,sizeof(vis));
	head=0;tail=-1;
	Q[++tail]=1;vis[1]=true;fa[1]=0;
	while(head<=tail){
		int x=Q[head++];
		for(int e=first[x];e!=-1;e=next[e])
			if(!vis[v[e]])
				Q[++tail]=v[e],vis[v[e]]=1,fa[v[e]]=x;
	}
}

void solve() {
	for(int l=tail;l>=0;l--){
		int x=Q[l];
		for(int b=0;b<=10;b++){
			dp[x][b][0]=1;dp[x][b][1]=dp[x][b][2]=0;
			for(int e=first[x];e!=-1;e=next[e]){
				if(v[e]==fa[x]) continue;
				LL r0,r1;
				if(b-1<0) r0=0;else r0=dp[v[e]][b-1][0]+dp[v[e]][b-1][1]+dp[v[e]][b-1][2];
				r1=dp[v[e]][b][0]+dp[v[e]][b][1];
				dp[x][b][2]=r0*dp[x][b][2]+r1*dp[x][b][1];
				dp[x][b][1]=r0*dp[x][b][1]+r1*dp[x][b][0];
				dp[x][b][0]=r0*dp[x][b][0];
				for(int k=0;k<3;k++)
					if(dp[x][b][k]>0){
						if(dp[x][b][k]%mod) dp[x][b][k]%=mod;
						else dp[x][b][k]=mod;
					}
			}
	}
	}
}

int main(){
	int a,b;
	memset(first,-1,sizeof(first));edge=0;
	scanf("%d%d%d",&n,&m,&mod);
	if(m!=n-1) {puts("-1");puts("-1");return 0;}
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b);add_edge(b,a);
	}
	BFS();
	solve();
	for(int ans=0;ans<=10;ans++){
		if(dp[1][ans][0]+dp[1][ans][1]+dp[1][ans][2]>0){
			printf("%d\n%lld\n",ans,(dp[1][ans][0]+dp[1][ans][1]+dp[1][ans][2])%mod);return 0;
		}
	}
	return 0;
}
