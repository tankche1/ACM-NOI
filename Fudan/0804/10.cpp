# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=210;
const int maxm=510;
const int INF=~0U>>1;
int n,m,k;
int s[maxm][maxn],cnt,id[maxm];
int u[maxm],v[maxm],edge=0,bh[maxn][maxn];
bool ban[maxm];
int idi[710];
int p[maxn];
int find(int x){if(x==p[x]) return x;return p[x]=find(p[x]);}

void BFS(int st){
    int x,y,px,py;
    cnt++;s[cnt][0]=0;
    for(int i=1;i<=n;i++) p[i]=i;
    for(int i=1;i<=edge;i++){
        if(ban[i]) continue;
        px=find(u[i]);py=find(v[i]);
        p[px]=py;
    }
    py=find(st);//printf("cnt:%d\n",cnt);
    for(int i=1;i<=n;i++){
        if(find(i)==py) s[cnt][++s[cnt][0]]=i;//,printf("i:%d\n",i);
    }
}

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[710],nnext[710*710],edge;
	Edge edges[710*710];
	int n,s,t;
	int cur[710],d[710];

	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
	}

	void clear(){
	    for(int e=0;e<edge;e++)
            edges[e].flow=0;
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

	void Back(int x){
	    for(int e=first[x];e!=-1;e=nnext[e]){
            if(edges[e].flow==0) continue;
            edges[e].flow=edges[e^1].flow=0;
            if(edges[e].to>cnt){
                for(int ee=first[edges[e].to];ee!=-1;ee=nnext[ee])
                   edges[ee].flow=edges[ee^1].flow=0;
            }
	    }
	}
}dinic;
int ans,S,T;
void solve(){
    int L,R,M,now=ans;
    for(int tt=1;tt<=cnt;tt++){
        now-=dinic.edges[id[tt]].flow;
        dinic.Back(tt);
        dinic.edges[id[tt]].cap=dinic.edges[id[tt]].flow=0;
        M=0;
        now+=dinic.maxflow(S,T);
        if(now!=ans)
           for(M=1;M<=k;M++){
               dinic.edges[id[tt]].cap=M;
               now+=dinic.maxflow(S,T);
               if(now==ans) break;
           }
        if(tt!=1) printf(" ");
        printf("%d",M);
    }puts("");
}

int main(){
    int tcase,op,x,a,b;
    scanf("%d",&tcase);
    while(tcase--){
        scanf("%d%d%d",&n,&m,&k);
        memset(ban,false,sizeof(ban));cnt=0;edge=0;
        //memset(bh,0,sizeof(bh));
        for(int i=1;i<=m;i++){
            scanf("%d",&op);
            if(op==1){
                scanf("%d",&x);
                BFS(x);
            }
            else if(op==2){
                scanf("%d%d",&a,&b);edge++;u[edge]=a;v[edge]=b;bh[a][b]=bh[b][a]=edge;
            }
            else{
                scanf("%d",&x);
                while(x--){
                    scanf("%d%d",&a,&b);
                    ban[bh[a][b]]=1;
                }
            }
        }
        S=0,T=cnt+n+1;
        dinic.init(T+1);
        for(int i=1;i<=cnt;i++){
            id[i]=dinic.edge;
            dinic.add_edge(S,i,k);
        }
        for(int i=1;i<=cnt;i++){
            for(int j=1;j<=s[i][0];j++)
                dinic.add_edge(i,cnt+s[i][j],1);
        }
        for(int i=1;i<=n;i++){
            idi[cnt+i]=dinic.edge;
            dinic.add_edge(cnt+i,T,1);
        }
        ans=dinic.maxflow(S,T);
        printf("%d\n",ans);
        solve();
    }
    return 0;
}
