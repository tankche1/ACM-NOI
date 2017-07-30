# include<stdio.h>
# include<string.h>
# include<algorithm>
using namespace std;
const int maxn=3010;
const int maxm=10010;
typedef long long LL;
int n,m;
int first[maxn],next[maxm],v[maxm];
double dist[maxm];int edge;
double d[maxn];
bool vis[maxn];
double val;
void add_edge(int a,int b,double c){
	next[edge]=first[a];
	v[edge]=b;
	dist[edge]=c;
	first[a]=edge++;
}

bool dfs(int x){
	vis[x]=true;
	//printf("val:%.6lf d[%d]:%.6lf\n",val,x,d[x]);
	for(int e=first[x];e!=-1;e=next[e]){
		if(d[x]+dist[e]-val<d[v[e]]){
			if(!vis[v[e]]){
				d[v[e]]=d[x]+dist[e]-val;
				if(dfs(v[e])){
					return true;
				}
			}
			else{
					return true;
			}
		}
	}
	vis[x]=false;
	return false;
}

bool check(double MI){
	val=MI;
	memset(d,0,sizeof(d));
	for(int i=1;i<=n;i++){
		memset(vis,false,sizeof(vis));
		if(dfs(i)) return true;
	}
	return false;
}

int main(){
	int a,b;double c;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	double _min=0,_max=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%lf",&a,&b,&c);
		add_edge(a,b,c);
		if(c<0) _min=min(_min,c);
			else _max=max(_max,c);
	}
	double L=_min,R=_max;double M;
		while(R-L>1e-9){
			M=(L+R)/2.0;
			if(check(M)) R=M;
			else L=M;
		}
		printf("%.8lf\n",M);
	return 0;
}
/*
4 5
1 2 5
2 3 5
3 1 5
2 4 3
4 1 3

2 2
1 2 -2.9
2 1 -3.1

*/
