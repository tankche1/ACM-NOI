#include<stdio.h>
#include<string.h>
# include<math.h>
# include<queue>
#include<algorithm>
using namespace std;
const int maxn=1010;
const int INF=~0U>>1;
typedef long long LL;
int n;
int a[maxn],b[maxn];
int sum=0;
int gcd(int a,int b){
	if(b==0) return a;
	return gcd(b,a%b);
}

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn],next[maxn*maxn*2],edge;
	Edge edges[maxn*maxn*2];
	int n,s,t;
	int cur[maxn],d[maxn];
	
	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
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

int main(){
	//LL ttt=(LL)1<<60;
//	printf("%d\n",(int)sqrt(ttt));
	scanf("%d",&n);
	int S=0,T=n+1;
	dinic.init(T+1);
	for(int i=1;i<=n;i++)
		scanf("%d",&a[i]);
	for(int i=1;i<=n;i++)
		scanf("%d",&b[i]),sum+=b[i];
	for(int i=1;i<=n;i++){
		if(a[i]&1)
			dinic.add_edge(S,i,b[i]);
		else dinic.add_edge(i,T,b[i]);
	}
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(gcd(a[i],a[j])==1){
				int x=i,y=j;
				LL t=(LL)a[x]*a[x]+(LL)a[y]*a[y];LL tt=sqrt(t);
				if(tt*tt==t){
					if(a[y]&1) swap(x,y);
					dinic.add_edge(x,y,INF);
				}
			}
		}
	}
	printf("%d\n",sum-dinic.maxflow(S,T));
	return 0;
}
