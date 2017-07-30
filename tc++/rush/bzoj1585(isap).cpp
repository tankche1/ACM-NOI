# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
# define in(x) x
# define out(x) p+x
using namespace std;
const int maxn=3010*2;
const int maxm=(20000*2+maxn)<<1;
const int INF=~0U>>1;
int p,n,c;
bool nocut[maxn];

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct ISAP{
	int first[maxn],next[maxm],edge,n;
	Edge edges[maxm];
	int cur[maxn],d[maxn];
	int num[maxn];
	int p[maxn];
	bool vis[maxn];
	int s,t;
	
	void init(int nn){
		n=nn;
		memset(first,-1,sizeof(first));edge=0;
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
		memset(vis,false,sizeof(vis));
		queue<int> q;q.push(t);vis[t]=true;d[t]=0;
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int e=first[x];e!=-1;e=next[e]){
				if(edges[e^1].flow<edges[e^1].cap&&(!vis[edges[e^1].from])){
					d[edges[e^1].from]=d[x]+1;
					vis[edges[e^1].from]=1;
					q.push(edges[e^1].from);
				}
			}
		}
		return vis[s];
	}
	
	int Augment(){
		int x=t,a=INF;
		while(x!=s){
			Edge e=edges[p[x]];
			a=min(a,e.cap-e.flow);
			x=e.from;
		}
		x=t;
		while(x!=s){
			edges[p[x]].flow+=a;
			edges[p[x]^1].flow-=a;
			x=edges[p[x]].from;
		}
		return a;
	}
	
	int maxflow(int S,int T){
		s=S;t=T;
		int flow=0;
		BFS();
		memset(num,0,sizeof(num));
		for(int i=0;i<n;i++) num[d[i]]++;
		int x=s;
		for(int i=0;i<n;i++) cur[i]=first[i];
		while(d[s]<n){
			
			if(x==t){
				flow+=Augment();
				x=s;
			}
				bool ok=false;
				for(int i=cur[x];i!=-1;i=next[i]){
					Edge &e=edges[i];
					if(d[e.to]+1==d[x]&&e.cap>e.flow){
						cur[x]=i;
						p[e.to]=i;
						ok=1;
						x=e.to;
						break;
					}
				}
				if(!ok){
					int m=n-1;
					for(int i=first[x];i!=-1;i=next[i]){
						Edge e=edges[i];
						if(e.cap>e.flow&&d[e.to]<m) m=d[e.to];
					}
					if(--num[d[x]]==0) break;
					num[d[x]=m+1]++;
					cur[x]=0;
					if(x!=s) x=edges[p[x]].from;
				}
		}
		return flow;
	}
	
};
ISAP g;

int read(){
	char t;
	while((t=getchar())&&(t<'0'||t>'9')) ;
		int res=t-'0';
	while((t=getchar())&&(t>='0'&&t<='9')) res=res*10+t-'0';
	return res;
}

int main(){
	int a,b;
	p=read();c=read();n=read();
	int S=out(1),T=2*p+1;
	g.init(T+1);
	for(int i=1;i<=c;i++){
		a=read();b=read();
		g.add_edge(out(a),in(b),INF);
		g.add_edge(out(b),in(a),INF);
	}
	for(int i=1;i<=n;i++)
		scanf("%d",&a),nocut[a]=1,g.add_edge(in(a),T,INF);
	for(int i=2;i<=p;i++)
		if(!nocut[i])
		g.add_edge(in(i),out(i),1);
	printf("%d\n",g.maxflow(S,T));
	return 0;
}
