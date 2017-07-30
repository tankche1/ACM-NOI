# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
typedef long long LL;
const int INF=~0U>>1;
const int maxn=110;
const int maxm=1010;
LL d[maxn][maxn];
int n,m,q;
int first[maxm],nnext[4*maxm*maxm],v[4*maxm*maxm],edge=0;

void add_edge(int from,int to){
	nnext[edge]=first[from];
	v[edge]=to;
	first[from]=edge++;
}

struct tank{
	int t,c;
	tank(int t=0,int c=0):t(t),c(c) {}
};
tank qu[maxm];
bool vis[maxm];int p[maxm];
bool dfs(int x){
	//printf("x:%d\n",x);
	for(int e=first[x];e!=-1;e=nnext[e]){
		if(vis[v[e]]) continue;vis[v[e]]=true;
		if(!p[v[e]]||dfs(p[v[e]])){
			p[v[e]]=x;return true;
		}
	}
	return false;
}

bool cmp(tank a, tank b){return a.t<b.t;}

int main(){
	int tcase,t=0;
	int a,b,c;
	scanf("%d",&tcase);
	while(tcase--){
		printf("Case %d: ",++t);
		scanf("%d%d%d",&n,&m,&q);
		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++)
				d[i][j]=INF;
		for(int i=1;i<=n;i++) d[i][i]=0;
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&a,&b,&c);a++;b++;
			d[a][b]=d[b][a]=min(d[a][b],(LL)c);
		}
		for(int k=1;k<=n;k++)
			for(int i=1;i<=n;i++)
				for(int j=1;j<=n;j++)
					if(d[i][k]<d[i][j]-d[k][j]) d[i][j]=d[i][k]+d[k][j];
		for(int i=1;i<=q;i++){
			scanf("%d %d",&qu[i].c,&qu[i].t);qu[i].c++;
		}
		sort(qu+1,qu+q+1,cmp);
		edge=0;memset(first,-1,sizeof(first));
		for(int i=1;i<=q;i++)
			for(int j=i+1;j<=q;j++){
				if(qu[j].t-qu[i].t>=d[qu[i].c][qu[j].c]){
					//printf("i:%d j:%d\n",i,j);
					add_edge(i,j);
				}
			}
		memset(p,0,sizeof(p));
		int ans=q;//puts("hei");
		for(int i=1;i<=q;i++) memset(vis,0,sizeof(vis)),ans-=dfs(i);
		printf("%d\n",ans-1);
	}
	return 0;
}
