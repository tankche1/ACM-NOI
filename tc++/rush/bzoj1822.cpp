# include<stdio.h>
# include<string.h>
# include<math.h>
# include<queue>
# include<algorithm>
using namespace std;
typedef pair<int,int> pi;
# define DIS(x,y) (x.first-y.first)*(x.first-y.first)+(x.second-y.second)*(x.second-y.second)
const int maxn=205;
const int INF=~0U>>1;
const int maxm=maxn*maxn*2;
const double eps=1e-8;
int dcmp(double x){
	if(fabs(x)<eps) return 0;
		return x<0?-1:1;
}
	
pi operator - (pi A,pi B) {return make_pair(A.first-B.first,A.second-B.second);}
double Dot(pi A,pi B) {return A.first*B.first+A.second*B.second;}
double Cross(pi A,pi B) {return A.first*B.second-A.second*B.first;}
double Length(pi A) {return sqrt(Dot(A,A));}

double DistanceToSegment(pi P,pi A,pi B){
	//printf("%d %d %d %d %d %d\n",P.first,P.second,A.first,A.second,B.first,B.second);
	if(A==B) return Length(P-A);
	if(dcmp(Dot(B-A,P-A))<0) return Length(P-A);
	else if(dcmp(Dot(B-A,P-B))>0) return Length(P-B);
	return fabs((double)Cross(B-A,P-A)/Length(B-A));
}

double DistanceToLine(pi P,pi A,pi B){
	//printf("%d %d %d %d %d %d %.2lf\n",P.first,P.second,A.first,A.second,B.first,B.second,fabs((double)Cross(B-A,P-A)/Length(B-A)));
	return fabs((double)Cross(B-A,P-A)/Length(B-A));
}

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn<<1],next[maxm],edge;
	Edge edges[maxm];
	int n,s,t;
	int cur[maxn*2],d[maxn*2];
	
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
};
Dinic g;
int n,m,k;
pi killer[maxn],people[maxn],wood[maxn];
int Ti[maxn],dist[maxn];
int wood_r[maxn];
bool vis[maxn];
int ans;
int main(){
	scanf("%d%d%d",&n,&m,&k);
	for(int i=1;i<=n;i++){
		scanf("%d%d%d%d",&killer[i].first,&killer[i].second,&dist[i],&Ti[i]);dist[i]*=dist[i];
	}
	for(int i=1;i<=m;i++)
		scanf("%d%d",&people[i].first,&people[i].second);
	for(int i=1;i<=k;i++)
		scanf("%d%d%d",&wood[i].first,&wood[i].second,&wood_r[i]);
	int S=0,T=n+m+1;
	g.init(T+1);
	memset(vis,false,sizeof(vis));ans=0;
	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			bool ok=true;int D;
			if(D=DIS(killer[i],people[j])>dist[i]) {//printf("shit%d %d\n",i,j);
				continue;}
			for(int w=1;w<=k;w++){
				if(dcmp(DistanceToSegment(wood[w],killer[i],people[j])-wood_r[w])<=0)
				{//printf("i:%d j:%d w:%d %.2lf\n",i,j,w,DistanceToLine(wood[w],killer[i],people[j]));
					ok=false;break;}
			}
			if(ok) {//printf("i:%d j:%d\n",i,j);
				g.add_edge(i,n+j,1);
				if(!vis[j]) {vis[j]=true;ans++;}
			}
		}
	}
	if(ans!=m) {puts("-1");return 0;}
	for(int i=1;i<=m;i++)
		g.add_edge(n+i,T,1);
	int start=g.edge;
	for(int i=1;i<=n;i++)
		g.add_edge(S,i,1);
	int end=g.edge;
	int L=0,R=20000*199;
	while(L<=R){
		int M=(L+R)>>1;
		//printf("%d\n",M);
		for(int e=start;e<end;e+=2)
			g.edges[e].cap=(M/Ti[g.edges[e].to])+1;
		for(int i=0;i<g.edge;i++) g.edges[i].flow=0;
		if(g.maxflow(S,T)==m) R=M-1;
			else L=M+1;
	}
	printf("%d\n",R+1);
	return 0;
}
