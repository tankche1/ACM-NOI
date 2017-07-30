# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxnode=40;
const int maxm=1600;
const int INF=100000;
int n,m,ans;
int a[10][10];

struct Edge{
	int from,to,flow,cap,cost;
	Edge() {}
	Edge(int from,int to,int flow,int cap,int cost):from(from),to(to),flow(flow),cap(cap),cost(cost) {}
};
Edge node;

struct Dinic{
	int first[maxnode],next[maxm];
	Edge edges[maxm];
	int d[maxnode],a[maxnode],p[maxnode];
	bool inq[maxnode];
	int n,m;

	void init(int a){
		n=a;m=0;
		memset(first,-1,sizeof(first));
	}

	void _clear(){
	    for(int e=0;e<m;e++) edges[e].flow=0;
	}

	void add_edge(int from,int to,int cap,int cost){
	    //printf("from:%d to:%d cap:%d cost:%d\n",from,to,cap,cost);
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
Dinic g;
int num[10];
bool vis[10];
int bh[10][10];

void prepare(){
    int S=0,T=3*n+1;
    g.init(T+1);
    for(int i=1;i<=n;i++){
        g.add_edge(S,i,1,0);
    }

    g.add_edge(1,n+n,1,0);g.add_edge(1,n+1,1,0);
    g.add_edge(n,n+n-1,1,0);g.add_edge(n,n+n,1,0);
    for(int i=2;i<n;i++){
        g.add_edge(i,n+i-1,1,0);
        g.add_edge(i,n+i,1,0);
    }

    for(int i=1;i<=n;i++){
        g.add_edge(2*n+i,T,1,0);
    }

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int res=0;
            /*if(j<n){
                res+=a[num[j]][i]+a[num[j+1]][i];
            }
            else res+=a[num[1]][i]+a[num[n]][i];*/
            //printf("i:%d j:%d res:%d\n",i,j,res);

            g.add_edge(n+j,2*n+i,1,res);bh[i][j]=g.m-2;
        }
    }

}

void solve(){
    int S=0,T=3*n+1;
    g._clear();

    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            int res=0;
            if(j<n){
                res+=a[num[j]][i]+a[num[j+1]][i];
            }
            else res+=a[num[1]][i]+a[num[n]][i];
            //printf("i:%d j:%d res:%d\n",i,j,res);
            g.edges[bh[i][j]].cost=res;
            g.edges[bh[i][j]+1].cost=-res;
            //g.add_edge(n+j,2*n+i,1,res);bh[i][j]=g.m-2;
        }
    }

    ans=min(ans,g.Mincost(S,T));
}

int block=0;

bool dfs(int cur){
    if(cur>n){
        if(++block>5000) return true;
           // for(int i=1;i<=n;i++) printf("num[%d]:%d\n",i,num[i]);
        solve();
        return false;;
    }

    for(int i=n;i>=1;i--){
        if(!vis[i]){
            num[cur]=i;vis[i]=1;if(dfs(cur+1)) return true;vis[i]=0;
        }
    }
    return false;
}

int main(){
    int x,y;
    while(scanf("%d%d",&n,&m)!=EOF){
        memset(a,0,sizeof(a));
        for(int i=1;i<=m;i++){
            scanf("%d%d",&x,&y);
            a[x][y]=1;
        }

        prepare();
        memset(vis,false,sizeof(vis));ans=n;
        block=0;num[1]=1;vis[1]=1;dfs(2);


        printf("%d\n",ans);
    }
    return 0;
}
