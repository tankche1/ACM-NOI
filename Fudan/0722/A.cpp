# include<stdio.h>
# include<string.h>
# include<math.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=1010*1010;
int u[maxm],v[maxm],cnt;double w[maxm];int bh[maxm];
int p[maxn],people[maxn];
int first[maxn],nnext[maxn<<1],to[maxn<<1],edge=0;
double cost[maxn<<1];
int n;
double xx[maxn],yy[maxn];
double dist[maxn][maxn];
double length=0;
	
bool cmp(int a,int b){
	return w[a]<w[b];
}

void add_edge(int a,int b,double c){
	nnext[edge]=first[a];to[edge]=b;cost[edge]=c;first[a]=edge++;
}

int find(int x){
	if(x==p[x]) return x;return p[x]=find(p[x]);
}
	
void Kruskal(){
	for(int i=1;i<=n;i++) p[i]=i;
	for(int i=1;i<=cnt;i++) bh[i]=i;
	sort(bh+1,bh+cnt+1,cmp);
	memset(first,-1,sizeof(first));edge=0;length=0;
	int x,y;
	for(int i=1;i<=cnt;i++){
		x=find(u[bh[i]]);y=find(v[bh[i]]);
		if(x!=y){
			p[x]=y;add_edge(u[bh[i]],v[bh[i]],w[bh[i]]);add_edge(v[bh[i]],u[bh[i]],w[bh[i]]);length+=w[bh[i]];
		}
	}
}

void dfs(int root,int now,int fa){
	for(int e=first[now];e!=-1;e=nnext[e]){
		if(to[e]==fa) continue;
		dist[root][to[e]]=max(dist[root][now],cost[e]);
		dfs(root,to[e],now);
	}
	return;
}

int main(){
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d",&n);
		for(int i=1;i<=n;i++)
			scanf("%lf%lf%d",&xx[i],&yy[i],&people[i]);
		cnt=0;
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				u[++cnt]=i;v[cnt]=j;w[cnt]=(double)sqrt((xx[i]-xx[j])*(xx[i]-xx[j])+(yy[i]-yy[j])*(yy[i]-yy[j]));
			}
		Kruskal();
		for(int i=1;i<=n;i++){
			dist[i][i]=0;
			dfs(i,i,-1);
		}
		double ans=-1;
		int x,y;
		for(int i=1;i<=cnt;i++){
			x=u[i],y=v[i];
			ans=max(ans,(double)(people[x]+people[y])/(length-dist[x][y]));
		}
		printf("%.2lf\n",ans);
	}
	return 0;
}
