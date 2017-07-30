# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=600;
const int maxm=maxn*40;
const int INF=~0U>>1;

struct Edge{
	int from,to,flow,cap;
	Edge(){}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
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

	void add_edge(int from,int to,int cap){
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
				if(edges[e].cap>edges[e].flow&&d[edges[e].to]>d[x]+1){
					d[edges[e].to]=d[x]+1;
					q.push(edges[e].to);
				}
			}
		}
		return d[T]!=INF;
	}

	int DFS(int x,int a){
		if(x==T||a==0) return a;
		int flow=0,f;
		for(int &e=cur[x];e!=-1;e=next[e]){
			if(d[edges[e].to]==d[x]+1&&(f=DFS(edges[e].to,min(edges[e].cap-edges[e].flow,a)))>0){
				flow+=f;a-=f;
				edges[e].flow+=f;edges[e^1].flow-=f;
				if(a==0) break;
			}
		}
		return flow;
	}

	int maxflow(int ss,int tt){
		S=ss;T=tt;
		int flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(S,INF);
		}
		return flow;
	}

}dinic;

int n,m;
int nn,mm;
int Limit[300],u[300],w[300][300];
int S,T;
int choose[300][2],num[300][2];
int Edge[300][2];
int main()
{
    int TT,tmp,x,Big;
    scanf("%d",&TT);
    for(int Tcase=1;Tcase<=TT;Tcase++){
        scanf("%d%d",&n,&m);
        nn=1<<n;
        mm=1<<m;
        for(int i=0;i<nn;i++)
            scanf("%d",&Limit[i]);
        for(int i=0;i<nn;i++)
            scanf("%d",&u[i]);

        for(int i=0;i<nn;i++){
            for(int j=0;j<mm;j++)
                scanf("%d",&w[i][j]),w[i][j]+=1025;
        }

        for(int i=0;i<nn;i++){
            if(Limit[i]==0) choose[i][0]=0;
            else{
                Big=0;
                for(int j=0;j<Limit[i];j++)
                    if(Big<w[i][j]) Big=w[i][j],num[i][0]=j;
                choose[i][0]=Big;
            }

            Big=0;
            for(int j=Limit[i];j<mm;j++)
                if(Big<w[i][j]) Big=w[i][j],num[i][1]=j;
            choose[i][1]=Big;
        }

        S=0;T=nn*2+1;
        dinic.init(T+1);
        int ans=-1025*nn;

        for(int i=0;i<nn;i++){
            tmp=0;
            x=i;
            while(x>0) tmp+=x&1,x>>=1;
            if(tmp&1){
                dinic.add_edge(S,2*i+1,choose[i][0]);ans+=choose[i][0];Edge[i][0]=dinic.edge-2;
                dinic.add_edge(2*i+2,T,choose[i][1]);ans+=choose[i][1];Edge[i][1]=dinic.edge-2;
                dinic.add_edge(2*i+1,2*i+2,INF);

                for(int k=0;k<n;k++){
                    x=i^(1<<(k));
                    dinic.add_edge(2*i+1,2*x+2,u[i]^u[x]);ans+=u[i]^u[x];
                }
            }
            else{
                dinic.add_edge(S,2*i+1,choose[i][1]);ans+=choose[i][1];Edge[i][0]=dinic.edge-2;
                dinic.add_edge(2*i+2,T,choose[i][0]);ans+=choose[i][0];Edge[i][1]=dinic.edge-2;
                dinic.add_edge(2*i+1,2*i+2,INF);
            }
            //printf("i:%d ans:%d\n",i,ans);
        }
        //puts("fuck");
        //printf("ans:%d\n",ans);
        ans=0;
        ans-=dinic.maxflow(S,T);
        //printf("ans:%d\n",ans);
        int pos;

        for(int i=0;i<nn;i++){
            tmp=0;
            x=i;
            while(x>0) tmp+=x&1,x>>=1;
            if(tmp&1){
                if(dinic.d[2*i+1]==INF)
                    pos=num[i][1];
                else pos=num[i][0];
            }
            else{
                if(dinic.d[2*i+1]==INF)
                    pos=num[i][0];
                else pos=num[i][1];
            }
            if(choose[i][0]==0) pos=num[i][1];
            printf("%d",pos);
            if(i!=nn-1) printf(" ");
        }puts("");
    }
	return 0;
}
