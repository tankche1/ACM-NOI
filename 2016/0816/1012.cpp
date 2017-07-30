# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=410;
const int maxm=maxn*maxn;
const int INF=~0U>>1;

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

	void clear(){
	    for(int i=0;i<edge;i++) edges[i].flow=0;
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

int x[maxn],x_cnt=0;
int plant_cost[maxn],plant_ti[maxn],plant_bh[maxn];
int shop[maxn];
int n,m,Fee;
int sum;
int S,T;

int solve(int ti){
    for(int i=1;i<=n;i++){
        if(plant_ti[i]<=ti){
            dinic.edges[plant_bh[i]].cap=plant_cost[i];
        }
        else dinic.edges[plant_bh[i]].cap=INF;
    }
    dinic.clear();
    return sum-dinic.maxflow(S,T);
}

int main(){
    int Case,k,xx;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d%d%d",&n,&m,&Fee);
        S=0;T=n+m+1;dinic.init(T+1);x_cnt=0;
        for(int i=1;i<=n;i++) scanf("%d%d",&plant_cost[i],&plant_ti[i]),x[x_cnt++]=plant_ti[i];
        sort(x,x+x_cnt);
        x_cnt=unique(x,x+x_cnt)-x;
        for(int i=1;i<=n;i++) plant_ti[i]=lower_bound(x,x+x_cnt,plant_ti[i])-x;
        sum=0;
        for(int i=1;i<=m;i++) {
            scanf("%d",&shop[i]);sum+=shop[i];
            dinic.add_edge(S,i,shop[i]);
            scanf("%d",&k);
            while(k--){
                scanf("%d",&xx);dinic.add_edge(i,m+xx,INF);
            }
        }

        for(int i=1;i<=n;i++){
            dinic.add_edge(m+i,T,INF);
            plant_bh[i]=dinic.edge-2;
        }

        int L=0,R=x_cnt-1,M;
        while(L<=R){
            M=(L+R)>>1;
            if(solve(M)>=Fee) R=M-1;
            else L=M+1;
        }

        int ans=solve(R+1);
        printf("Case #%d: ",Tcase);
        if(ans<Fee) puts("impossible");
        else{
            printf("%d %d\n",x[R+1],ans);
        }
    }
    return 0;
}
