# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=13*13*13;
const int maxm=maxn*6;
const int INF=100000;
int n;
int px[110],py[110],pz[110];
int dx[6]={-1,1,0,0,0,0},dy[6]={0,0,-1,1,0,0},dz[6]={0,0,0,0,-1,1};

int index(int a,int b,int c){
    return c+b*12+a*144;
}

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

int main(){
    int T,nx,ny,nz;
    scanf("%d",&T);
    for(int Tcase=1;Tcase<=T;Tcase++){
        scanf("%d",&n);
        for(int i=1;i<=n;i++){
            scanf("%d%d%d",&px[i],&py[i],&pz[i]);
        }
        int S=0,T=12*12*12;
        dinic.init(T+1);

        for(int x=0;x<12;x++){
            for(int y=0;y<12;y++){
                for(int z=0;z<12;z++){
                    int flag=1;
                    flag&=(x&&x<11);flag&=(y&&y<11);flag&=(z&&z<11);
                    if(!flag){
                        dinic.add_edge(S,index(x,y,z),INF);
                    }

                    for(int t=0;t<6;t++){
                        nx=x+dx[t],ny=y+dy[t],nz=z+dz[t];
                        if(nx>=0&&nx<12&&ny>=0&&ny<12&&nz>=0&&nz<12){
                            dinic.add_edge(index(x,y,z),index(nx,ny,nz),1);
                        }
                    }
                }
            }
        }

        for(int i=1;i<=n;i++){
            px[i]++;py[i]++;pz[i]++;
            dinic.add_edge(index(px[i],py[i],pz[i]),T,INF);
        }

        printf("%d\n",dinic.maxflow(S,T));
    }
    return 0;
}
