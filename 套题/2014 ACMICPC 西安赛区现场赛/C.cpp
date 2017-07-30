# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=110;
const int maxm=maxn*maxn;
const int INF=~0U>>1;
const double eps=1e-9;

struct Edge{
	int from,to;double flow,cap;
	Edge(){}
	Edge(int from,int to,double flow,double cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int S,T,edge,n;
	Edge edges[maxm];
	int first[maxn],next[maxm];
	int cur[maxn],d[maxn];

	void init(int nn){
		n=nn+1;
		memset(first,-1,sizeof(first));
		edge=0;
	}

	void clear(){
	    for(int i=0;i<edge;i++) edges[i].flow=0;
	}

	void add_edge(int from,int to,double cap){
	    //printf("from:%d to:%d cap:%.2lf\n",from,to,cap);
		next[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0);
		first[to]=edge++;
	}

	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
			d[S]=0;
		queue<int> q;q.push(S);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
				if(edges[e].cap-edges[e].flow>eps&&d[edges[e].to]>d[x]+1){
					d[edges[e].to]=d[x]+1;
					q.push(edges[e].to);
				}
			}
		}
		return d[T]!=INF;
	}

	double DFS(int x,double a){
		if(x==T||fabs(a)<eps) return a;
		double flow=0,f;
		for(int &e=cur[x];e!=-1;e=next[e]){
			if(d[edges[e].to]==d[x]+1&&(f=DFS(edges[e].to,min(edges[e].cap-edges[e].flow,a)))>0){
				flow+=f;a-=f;
				edges[e].flow+=f;edges[e^1].flow-=f;
				if(fabs(a)<eps) break;
			}
		}
		return flow;
	}

	double maxflow(int ss,int tt){
		S=ss;T=tt;
		double flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(S,INF);
		}
		//printf("flow:%.3lf\n",flow);
		return flow;
	}

}dinic;

int n,m;
int a[maxn],du[maxn];
int g[maxn][maxn];
int S,T;
int flag;
double U;

void build(double l){
    for(int i=flag,j=1;i<dinic.edge;i+=2,j++){
        dinic.edges[i].cap=U+l*2-du[j];
        //printf("%.3lf\n",dinic.edges[i].cap);
    }
    dinic.clear();
}

int main(){
    int Case;
    scanf("%d",&Case);
    for(int Tcase=1;Tcase<=Case;Tcase++){
        scanf("%d",&n);m=0;
        for(int i=1;i<=n;i++)
            scanf("%d",&a[i]);
        memset(g,0,sizeof(g));memset(du,0,sizeof(du));
        for(int i=1;i<=n;i++){
            for(int j=i+1;j<=n;j++){
                if(a[i]>a[j]) g[i][j]=g[j][i]=1,du[i]++,du[j]++,m++;
            }
        }
        S=0;T=n+1;
        U=m;
        dinic.init(T+1);
        for(int i=1;i<=n;i++){
            dinic.add_edge(S,i,U);
        }
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                if(g[i][j]) dinic.add_edge(i,j,1);
            }
        }

        flag=dinic.edge;
        U=m;
        for(int i=1;i<=n;i++) dinic.add_edge(i,T,U+2*0-du[i]);

        double L=0,R=n,M;
        while(R-L>eps){
            M=(L+R)/2.0;
            build(M);
            if(U*n-dinic.maxflow(S,T)>0) L=M;
            else R=M;
        }
        printf("Case #%d: ",Tcase);
        printf("%.12lf\n",L);
    }
    return 0;
}
