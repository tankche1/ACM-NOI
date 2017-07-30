# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=10010;
const int maxnode=110;
const int maxm=30*30*2;
const int INF=1000000;
int c[26][26];
int n,k,m;
char s[maxn];
char stu[maxn];

struct Edge{
	int from,to,flow,cap,cost;
	Edge() {}
	Edge(int from,int to,int flow,int cap,int cost):from(from),to(to),flow(flow),cap(cap),cost(cost) {}
};

struct MCMF{
	int first[maxnode],next[maxm];
	Edge edges[maxm];
	int d[maxnode],a[maxnode],p[maxnode];
	bool inq[maxnode];
	int n,m;
	
	void init(int a){
		n=a;m=0;
		memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap,int cost){
		next[m]=first[from];
		first[from]=m;
		edges[m++]=Edge(from,to,0,cap,cost);
		next[m]=first[to];
		first[to]=m;
		edges[m++]=Edge(to,from,0,0,-cost);
	}
	
	bool BellmanFord(int s,int t,int &flow,int &cost){
		queue<int> q;
		q.push(s);
		a[s]=INF;
		p[s]=0;
		memset(inq,false,sizeof(inq));
		for(int i=0;i<n;i++) d[i]=INF;
		d[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				int v=edges[e].to;
				if(edges[e].cap>edges[e].flow&&d[v]>d[x]+edges[e].cost){
					d[v]=d[x]+edges[e].cost;
					a[v]=min(a[x],edges[e].cap-edges[e].flow);
					p[v]=e;
					if(!inq[v]) inq[v]=true,q.push(v);
				}
			}
		}
		if(d[t]==INF) return false;
		flow+=a[t];
		cost+=a[t]*d[t];
		int u=t;
		while(u!=s){
			edges[p[u]].flow+=a[t];
			edges[p[u]^1].flow-=a[t];
			u=edges[p[u]].from;
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

int main(){
	int tcase,S,T;
	char tt;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%d%d%d",&n,&k,&m);
		for(int i=0;i<n;i++){
			while((tt=getchar())&&(tt<'A'||tt>'Z'));
			s[i]=tt;
		}
		for(int i=1;i<=m;i++){
			for(int j=0;j<n;j++){
				while((tt=getchar())&&(tt<'A'||tt>'Z'));
				stu[j]=tt;
			}
			S=0;T=26+26+1;
			g.init(T+1);
			memset(c,0,sizeof(c));
			for(int j=0;j<n;j++)
				c[stu[j]-'A'][s[j]-'A']++;
			for(int i=1;i<=26;i++)
				g.add_edge(S,i,1,0);
			for(int i=27;i<=52;i++)
				g.add_edge(i,T,1,0);
			for(int i=0;i<26;i++)
				for(int j=0;j<26;j++)
					g.add_edge(i,j,1,-c[i][j]);
			//puts("hei");
			int ans=-g.Mincost(S,T);
			double output=(double)ans/n;
			printf("%.4lf\n",output);
		}
	}
	return 0;
}
