# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=60;

int n,m;

struct Edge{
	int u,v;double dist;
	void n(int uu,int vv,double ddist) {u=uu;v=vv;dist=ddist;}
};

struct BellmanFord{
	vector<int> G[maxn];
	vector<Edge> edges;
	int n;
	double d[maxn];
	bool  inq[maxn];
	int cnt[maxn];
	
	void init(int nn){
		n=nn;
		for(int i=1;i<=n;i++)
			G[i].clear();
		edges.clear();
	}
	
	void add_edge(int a,int b,double c){
		Edge E;E.n(a,b,c);
		edges.push_back(E);
		G[a].push_back(edges.size()-1);
	}
	
	bool negativeCycle(){
		queue<int> q;
		for(int i=1;i<=n;i++) d[i]=0,inq[i]=true,q.push(i),cnt[i]=0;
		while(!q.empty()){
			int x=q.front();q.pop();inq[x]=false;
			//printf("d[%d]:%.2lf\n",x,d[x]);
			for(int i=0;i<G[x].size();i++){
				int e=edges[G[x][i]].v;
				//printf("i:%d e:%d dist:%.2lf\n",i,e,edges[G[x][i]].dist);
				if(d[e]>d[x]+edges[G[x][i]].dist){
					d[e]=d[x]+edges[G[x][i]].dist;
					if(!inq[e]){
						inq[e]=true;
						q.push(e);
						if(++cnt[e]>=n) return true;
					}
				}
			}
		}
		return false;
	}
	
};
BellmanFord Bellman;

void change_graph(double val,int fuck){
	val*=fuck;
	for(int i=0;i<Bellman.edges.size();i++)
	{Bellman.edges[i].dist+=val;}//printf("%.2lf\n",Bellman.edges[i].dist);}
		
}

int main(){
	int a,b,c;
	int tcase;
	int maxc=0;
	scanf("%d",&tcase);
	for(int T=1;T<=tcase;T++){
	scanf("%d%d",&n,&m);
	Bellman.init(n);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c),Bellman.add_edge(a,b,(double)c);maxc=max(maxc,c);}
	change_graph(maxc+1,-1);
		printf("Case #%d: ",T);
	if(!Bellman.negativeCycle()) printf("No cycle found.\n");
	else{
		change_graph(maxc+1,1);
	double L=0,R=maxc;
		while(R-L>(1e-3)){
			double M=(L+R)/2.0;
				//printf("L:%.2lf R:%.2lf M:%.2lf\n",L,R,M);
			change_graph(M,-1);
			if(Bellman.negativeCycle())
			R=M;
			else L=M;
			change_graph(M,1);
		}
		printf("%.2lf\n",R);
	}
}
	return 0;
}
/*
1
2 2
1 2 2
2 1 3
*/
