# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=10010;
int n,tot;
double ans=0;
int first[maxn],next[maxn<<1],v[maxn<<1],edge;
int size[maxn];

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

void dfs(int x,int fa){
	size[x]=1;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa) dfs(v[e],x),size[x]+=size[v[e]];
			//printf("x:%d %d\n",x,size[x]);
	ans+=((n-size[x])*(size[x])/(tot*1.0))*((n-size[x])*(size[x])/(tot*1.0));
}

int main(){
	int a,b;
	while(scanf("%d",&n)!=EOF){
		tot=n*(n-1)/2;
		ans=0;
		memset(first,-1,sizeof(first));edge=0;
		for(int i=1;i<n;i++){
			scanf("%d%d",&a,&b);
			add_edge(a,b),add_edge(b,a);
		}
		dfs(1,0);
		printf("%.6lf\n",ans);
	}
	return 0;
}
