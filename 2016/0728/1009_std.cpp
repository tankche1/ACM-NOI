# include<stdio.h>
# include<string.h>
# include<vector>
# include<queue>
# include<algorithm>
using namespace std;

const int maxn=105*105+105+15+2;
const int maxm=maxn*10;
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
	queue<int> q;

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
		q.push(s);
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

int n;
char s[maxn];
int type[11][2];
int w[maxn][maxn];

int main(){
    freopen("1009.in","r",stdin);
    freopen("output.txt","w",stdout);
    int Tnum;
    scanf("%d",&Tnum);
    for(int Tcase=1;Tcase<=Tnum;Tcase++){
        scanf("%d",&n);
        scanf("%s",s+1);
        for(int i=0;i<10;i++){
            scanf("%d%d",&type[i][0],&type[i][1]);
        }

        int ans=0,sum=0;
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                scanf("%d",&w[i][j]);sum+=w[i][j];
            }
        }
        int S=0,T=n*n+n+10+1;
        dinic.init(T+1);
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                dinic.add_edge(S,(i-1)*n+j,w[i][j]);
                dinic.add_edge((i-1)*n+j,n*n+i,INF);
                dinic.add_edge((i-1)*n+j,n*n+j,INF);
            }
            dinic.add_edge(n*n+i,T,type[s[i]-'0'][0]);
            dinic.add_edge(n*n+i,n*n+n+s[i]-'0'+1,INF);
        }

        for(int i=0;i<10;i++){
            dinic.add_edge(n*n+n+i+1,T,type[i][1]-type[i][0]);
        }

        sum-=dinic.maxflow(S,T);

        printf("Case #%d: ",Tcase);
        printf("%d\n",sum);
    }
    return 0;
}
