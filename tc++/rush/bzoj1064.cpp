#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=maxn*10;
int n,m;
int first[maxn],next[maxm<<1],v[maxm<<1],w[maxm<<1],edge;
int bh[maxn];
int tree_max=0,tree_min;
int treesum=0;
bool have_cycle;
int lans,rans=1;
bool vis[maxn];

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}

void dfs(int x){
	vis[x]=1;
	tree_max=max(tree_max,bh[x]);
	tree_min=min(tree_min,bh[x]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(!vis[v[e]]){
			bh[v[e]]=bh[x]+w[e];
			dfs(v[e]);
		}
		else{
			if(bh[v[e]]==bh[x]+w[e]) continue;
			if(!have_cycle) rans=abs(bh[x]+w[e]-bh[v[e]]);
			else rans=gcd(rans,abs(bh[x]+w[e]-bh[v[e]]));
			have_cycle=1;
		}
	}
}

int main(){
	//freopen("party.in","r",stdin);
	//freopen("party.out","w",stdout);
	int a,b;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);
		add_edge(a,b,1);add_edge(b,a,-1);
	}
	memset(vis,0,sizeof(vis));
	tree_max=0;have_cycle=false;treesum=0;
	for(int i=1;i<=n;i++)
		if(!vis[i]){
			bh[i]=1;tree_max=0;tree_min=1;
			dfs(i);treesum+=tree_max-tree_min+1;
		}
	if(have_cycle){
		if(rans<3) lans=rans=-1;
		else{
			for(lans=3;lans<=rans;lans++){
				if(rans%lans==0) break;
			}
		}
	}
	else{
		if(treesum<3)
			lans=rans=-1;
		else lans=3,rans=treesum;
	}
	printf("%d %d\n",rans,lans);
	return 0;
}
