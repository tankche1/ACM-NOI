# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=10010;
const int maxedge=(maxm+2*maxn)*2;
const int INF=~0U>>1;

struct Edge{
	int from,to,flow,cap,cost;
	
	void give(int fr,int t,int fl,int ca,int co){
		from=fr;to=t;flow=fl;cap=ca;cost=co;
	}
};
Edge node;

struct MCMF{
	int n,m;
	int first[maxn],next[maxedge];
	Edge edges[maxedge];
	int d[maxn],pre[maxn],a[maxn];
	bool inq[maxn];
	
	void init(int n){
		this->n=n;
		memset(first,-1,sizeof(first));
		m=0;
	}
	
	void add_edge(int from,int to,int cap,int cost){
		printf("from:%d to:%d cap:%d cost:%d\n",from,to,cap,cost);
		node.give(from,to,0,cap,cost);
		next[m]=first[from];
		first[from]=m;
		edges[m++]=node;
		node.give(to,from,0,0,-cost);
		next[m]=first[to];
		first[to]=m;
		edges[m++]=node;
	}
	
	bool BellmanFord(int s,int t,int &flow,int &cost){
		queue<int> q;
		for(int i=0;i<n;i++) d[i]=INF;
		d[s]=0;
		q.push(s);a[s]=INF;
		memset(inq,false,sizeof(inq));
		while(!q.empty()){
			int x=q.front();printf("size:%d \n",q.size());q.pop();printf("x:%d\n",x);//for(int i=0;i<n;i++) printf("d[%d]:%d",i,d[i]);
			printf("size:%d \n",q.size());
			int  aa;
			scanf("%d",&aa);
			inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				int v=edges[e].to;
				if(edges[e].cap>edges[e].flow&&d[v]>d[x]+edges[e].cost){
				//	printf("v:%d d[v]:%d newd[v]:%d\n",v,d[v],d[x]+edges[e].cost);
					
					a[v]=min(a[x],edges[e].cap-edges[e].flow);
					pre[v]=e;
					if(!inq[v]){
						inq[v]=true;q.push(v);
					//	printf("vv:%d\n",v);
					}
					d[v]=d[x]+edges[e].cost;
				}
			}
		}
		if(d[t]==INF) return false;
		flow+=a[t];
		cost+=a[t]*d[t];
		int u=t;
		while(u!=s){
			edges[pre[u]].flow+=a[t];
			edges[pre[u]^1].flow-=a[t];
			u=edges[pre[u]].from;
		}
		return true;
	}
	
	int Mincost(int s,int t){
		int flow=0,cost=0;
		while(BellmanFord(s,t,flow,cost));
			return cost;
	}
	
};
MCMF g;

int n,m,day[maxn];
int a,b,c;
int S,T;
void init(){
	scanf("%d%d",&n,&m);
	S=0;T=n+2;day[0]=day[n+1]=0;
	g.init(T+1);
	for(int i=1;i<=n;i++)
		scanf("%d",&day[i]);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		g.add_edge(b+1,a,INF,c);
	}
	for(int i=1;i<=n;i++)
		g.add_edge(i,i+1,INF,0);
	for(int i=1;i<=n+1;i++)
		if(day[i-1]-day[i]>0)
			g.add_edge(S,i,day[i-1]-day[i],0);
		else if(day[i-1]-day[i]<0)
			g.add_edge(i,T,day[i]-day[i-1],0);
}

int main(){
	init();
	printf("%d\n",g.Mincost(S,T));
	return 0;
}
