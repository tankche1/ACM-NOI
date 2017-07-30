# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=50010;
int u[maxm],v[maxm],next[maxm],first[maxn],Ti[maxm],edge;
int n,m;
double ans;
int val[maxn];
double d[maxn];
bool vis[maxn];

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	u[edge]=a;v[edge]=b;Ti[edge]=c;
	first[a]=edge++;
}

bool dfs(int x){
	//printf("d[%d]:%.2lf\n",x,d[x]);
	vis[x]=true;
	for(int e=first[x];e!=-1;e=next[e]){
		if(d[v[e]]<(d[x]+(double)val[v[e]]-ans*Ti[e])){
			if(vis[v[e]]) return true;
			d[v[e]]=(d[x]+(double)val[v[e]]-ans*Ti[e]);
			if(dfs(v[e])) return true;
		}
	}
	vis[x]=false;
	return false;
}

bool check(){
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++){
		memset(vis,false,sizeof(vis));
		if(dfs(i)) return true;
	}
	return false;
}

int main(){
	int a,b,c;
	scanf("%d%d",&n,&m);
	int _max=0;
	for(int i=1;i<=n;i++)
		scanf("%d",&val[i]),_max=max(_max,val[i]);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
	}
	double L=0,R=_max;
	while(R-L>1e-3){
		double M=(L+R)/2.0;ans=M;
			//printf("M:%.2lf\n",M);
		if(check()) L=M;
			else R=M;
	}
	printf("%.2lf\n",L);
	return 0;
}
