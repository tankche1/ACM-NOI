# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=110;
const int maxm=10010;
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
int S,T;
int a[maxm],b[maxm],cap[maxm],down[maxm],type;
int du[maxn];
int bh[maxm];

int main(){
    scanf("%d%d",&n,&m);
    S=0;T=n+1;
    dinic.init(T+1);
    memset(du,0,sizeof(du));
    for(int i=1;i<=m;i++){
        scanf("%d%d%d%d",&a[i],&b[i],&cap[i],&type);
        down[i]=(type==1)?cap[i]:0;
        if(cap[i]>down[i]) bh[i]=dinic.edge,dinic.add_edge(a[i],b[i],cap[i]-down[i]);
        else bh[i]=-1;
        //printf("bh[%d]:%d cap:%d down:%d\n",i,bh[i],cap[i],down[i]);
        du[b[i]]+=down[i];du[a[i]]-=down[i];
    }
    int need=0,flow=0;
    for(int i=1;i<=n;i++){
        if(du[i]>0) {dinic.add_edge(S,i,du[i]);need+=du[i];}
        else if(du[i]<0) dinic.add_edge(i,T,-du[i]);
    }
    flow+=dinic.maxflow(S,T);
    dinic.add_edge(n,1,INF);
    int ans=dinic.maxflow(S,T);
    flow+=ans;
    if(flow!=need){
        puts("Impossible");
    }
    else{
        printf("%d\n",ans);
        for(int i=1;i<=m;i++){
            if(i>1) printf(" ");
            if(bh[i]==-1) printf("%d",cap[i]);
            else //printf("down[%d]:%d flow:%d \n",i,down[i],dinic.edges[bh[i]].flow),
                printf("%d",down[i]+dinic.edges[bh[i]].flow);
        }puts("");
    }
    return 0;
}
