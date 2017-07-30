# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=1000000000;
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

int ta[maxm],tb[maxm];

bool vis[maxn];
int co[maxn];

void paint(int x){
    vis[x]=1;
    for(int e=0;e<(int)G[x].size();e++){
        int v=G[x][e];
        if(!vis[v]) vis[v]=1,co[v]=co[x]^1,paint(v);
    }
}

int main(){
    int a,b,S,T;
    while(scanf("%d%d",&n,&m)!=EOF){
        for(int i=1;i<=n;i++)scanf("%d",&w[i]);
        for(int i=1;i<=n;i++) scanf("%d",&p[i]),p[i]--;
        for(int i=1;i<=n;i++) G[i].clear();

        for(int i=1;i<=m;i++){
            scanf("%d %d",&ta[i],&tb[i]);G[ta[i]].push_back(tb[i]);G[tb[i]].push_back(ta[i]);
        }

        memset(vis,0,sizeof(vis));
        for(int i=1;i<=n;i++){
            if(!vis[i]) paint(i);
        }
        int S=n*2+1,T=n*2+2;
        dinic.init(T+1);
        for(int i=1;i<=n;i++){
            dinic.add_edge(i*2-1,i*2,w[i]);
            if(p[i]>1) continue;
            if(p[i]^co[i]) dinic.add_edge(S,2*i-1,INF);
            else dinic.add_edge(i*2,T,INF);
        }

        for(int i=1;i<=m;i++){
            dinic.add_edge(ta[i]*2,tb[i]*2-1,INF);
            dinic.add_edge(tb[i]*2,ta[i]*2-1,INF);
        }

        printf("%d\n",dinic.maxflow(S,T));
    }
    return 0;
}
