#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=41*41*41+100;
const int maxm=maxn<<1;

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn],next[maxm<<1],edge;
	Edge edges[maxm<<1];
	int n,s,t;
	int cur[maxn],d[maxn];
	
	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap){
	//	printf("from:%d to:%d cap:%d\n",from,to,cap);
		next[edge]=first[from];
		edges[edge]=Edge(from,to,0,cap);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0);
		first[to]=edge++;
	}
	
	bool BFS(){
		for(int i=0;i<n;i++) d[i]=INF;
			d[s]=0;
		queue<int> q;q.push(s);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
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
		for(int &e=cur[x];e!=-1;e=next[e]){
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

int P,Q,R,D;
int val[50][50][50];
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

int main(){
	scanf("%d%d%d%d",&P,&Q,&R,&D);
	for(int k=1;k<=R;k++)
		for(int i=1;i<=P;i++)
			for(int j=1;j<=Q;j++)
				scanf("%d",&val[i][j][k]);
	int S=0,T=P*Q*(R+1)+1;
			dinic.init(T+1);
	for(int i=1;i<=P;i++)
		for(int j=1;j<=Q;j++){
			dinic.add_edge(S,((i-1)*Q+j-1)*(R+1)+1,INF);
			dinic.add_edge(((i-1)*Q+j-1)*(R+1)+R+1,T,INF);
			for(int k=1;k<=R+1;k++){
				if(k<=R)
				dinic.add_edge(((i-1)*Q+j-1)*(R+1)+k,((i-1)*Q+j-1)*(R+1)+k+1,val[i][j][k]);
				if(k>D){
					for(int l=0;l<4;l++){
						int x=i+dx[l],y=j+dy[l];
						if(x>=1&&x<=P&&y>=1&&y<=Q){
							dinic.add_edge(((i-1)*Q+j-1)*(R+1)+k,((x-1)*Q+y-1)*(R+1)+k-D,INF);
						}
					}
				}
			}
		}
		printf("%d\n",dinic.maxflow(S,T));
	return 0;
}
