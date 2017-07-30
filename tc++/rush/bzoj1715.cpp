# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=510;
const int maxm=210+2510*2;
const int INF=~0U>>1;
int n,m,w;

struct Bellman_Ford{
	int n;
	int first[maxn],next[maxm],v[maxm],dist[maxm],edge;
	bool inq[maxn];
	int cnt[maxn];
	int d[maxn];
	
	void init(int nn){
		memset(first,-1,sizeof(first));edge=0;n=nn;
	}
	
	void add_edge(int a,int b,int c){
		next[edge]=first[a];
		v[edge]=b;
		dist[edge]=c;
		first[a]=edge++;
	}
	
	bool negativeCycle(int s){
		queue<int> q;
		memset(cnt,0,sizeof(cnt));
		memset(inq,false,sizeof(inq));
		for(int i=1;i<=n;i++)
			d[i]=INF;
		d[s]=0;q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]>d[x]+dist[e]){
					d[v[e]]=d[x]+dist[e];
					if(!inq[v[e]]){
						inq[v[e]]=true;
						q.push(v[e]);
						if(++cnt[v[e]]>=n) return true;
					}
				}
			}
		}
		return false;
	}

};
Bellman_Ford g;

int main(){
	int a,b,c;
	int tcase;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&n,&m,&w);
		//memset(first,-1,sizeof(first));edge=0;
		g.init(n);
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&a,&b,&c);
			g.add_edge(a,b,c);
			g.add_edge(b,a,c);
		}
		for(int i=1;i<=w;i++){
			scanf("%d%d%d",&a,&b,&c);
			g.add_edge(a,b,-c);
		}
		if(g.negativeCycle(1)) puts("YES");
			else puts("NO");
	}
	return 0;
}
