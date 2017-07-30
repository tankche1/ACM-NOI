# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=1010<<1;
const int maxm=10010*2;
vector<int> G[maxn];

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn],nnext[maxm<<1],edge;
	Edge edges[maxm<<1];
	int n,s,t;
	int cur[maxn],d[maxn];

	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
	}

	void add_edge(int from,int to,int cap){
		nnext[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap);
		first[from]=edge++;
		nnext[edge]=first[to];
		edges[edge]=Edge(to,from,0,0);
		first[to]=edge++;
	}

	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
			d[s]=0;
		queue<int> q;q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=nnext[e]){
				if(edges[e].cap>edges[e].flow&&d[edges[e].to]>d[x]+1){
					d[edges[e].to]=d[x]+1;
					q.push(edges[e].to);
				}
			}
		}
		return d[t]!=INF;
	}

	int DFS(int x,int a){
		if(x==t||a==0) return a;
			int flow=0,f;
		for(int &e=cur[x];e!=-1;e=nnext[e]){
			if(d[edges[e].to]==d[x]+1&&(f=DFS(edges[e].to,min(edges[e].cap-edges[e].flow,a)))>0){
				flow+=f;
				a-=f;
				edges[e].flow+=f;
				edges[e^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}

	int maxflow(int ss,int tt){
		s=ss;t=tt;
		int flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(s,INF);
		}
		return flow;
	}
}dinic;

int n,m;
int p[maxn],w[maxn];
int type[maxn];

void dfs(int x){
    for(int e=0;e<(int)G[x].size();e++){
        if(type[G[x][e]]==-1){
            type[G[x][e]]=type[x]^1;dfs(G[x][e]);
        }
    }
}
int ta[maxm],tb[maxm];

int main(){
    int a,b,S,T;
    while(scanf("%d%d",&n,&m)!=EOF){
        S=0;T=2*n+1;dinic.init(T+1);
        for(int i=1;i<=n;i++) scanf("%d",&w[i]),G[i].clear();
        for(int i=1;i<=n;i++) scanf("%d",&p[i]);

        for(int i=1;i<=m;i++){
            scanf("%d%d",&a,&b);G[a].push_back(b);G[b].push_back(a);
            ta[i]=a;tb[i]=b;
            ////dinic.add_edge(a,n+b,INF);dinic.add_edge(b,n+a,INF);
        }

        for(int i=1;i<=n;i++) type[i]=-1;
        for(int i=1;i<=n;i++){
            if(type[i]==-1){
                type[i]=0;dfs(i);
            }
        }

        for(int i=1;i<=n;i++){
            dinic.add_edge(i,n+i,w[i]);
            if((type[i]==0&&p[i]==1)||(type[i]==1&&p[i]==2)) dinic.add_edge(S,i,INF);
            else if((type[i]==0&&p[i]==2)||(type[i]==1&&p[i]==1)) dinic.add_edge(n+i,T,INF);
        }

        for(int i=1;i<=m;i++){
            dinic.add_edge(n+ta[i],tb[i],INF);
            dinic.add_edge(n+tb[i],ta[i],INF);
        }

        printf("%d\n",dinic.maxflow(S,T));
    }
    return 0;
}
