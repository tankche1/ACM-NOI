# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n,m;
vector<int> G1[maxn],G2[maxn];
int in[maxn],out[maxn];
queue<int> Q;
bool vis[maxn];

void dfs(int x){
	printf("%d ",x);
	for(int i=0;i<(int)G1[x].size();i++)
		--in[G1[x][i]];
	for(int i=0;i<(int)G1[x].size();i++)
		if(in[G1[x][i]]==0) {dfs(G1[x][i]);break;}
	return;
}

int main()
{
	int Tcase;
	int a,b,x,tot;
	bool miss,ok;
	int ans;
	scanf("%d",&Tcase);
	while(Tcase--){
		scanf("%d%d",&n,&m);
		for(int i=1;i<=n;i++) G1[i].clear(),G2[i].clear();
		memset(in,0,sizeof(in));memset(out,0,sizeof(out));
		for(int i=1;i<=m;i++){
			scanf("%d%d",&a,&b);in[b]++;out[a]++;
			G1[a].push_back(b);G2[b].push_back(a);
		}
		memset(vis,false,sizeof(vis));
		for(int i=1;i<=n;i++) if(out[i]==0) Q.push(i),vis[i]=1;
		tot=0;
		miss=false;
		while(!Q.empty()){
			if(Q.size()>1) miss=1;
			x=Q.front();Q.pop();
			ok=true;
			for(int i=0;i<(int)G2[x].size();i++){
				ok=false;
				if(--out[G2[x][i]]==0){
					vis[G2[x][i]]=1;
					Q.push(G2[x][i]);
				}
			}
			if(ok) tot++,ans=x;
		}
		ok=1;
		for(int i=1;i<=n;i++)
			if(!vis[i]) {ok=false;break;}
		if(!ok) {puts("recheck hints");continue;}
		if(miss) {puts("missing hints");continue;}
		dfs(ans);puts("");
	}
	return 0;
}
