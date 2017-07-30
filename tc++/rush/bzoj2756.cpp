#include<stdio.h>
#include<string.h>
# include<queue>
#include<algorithm>
using namespace std;
typedef long long LL;
const int maxn=1610;
const int maxm=4*maxn*4;
const LL inf=(LL)1<<60;
const int INF=~0U>>1;
int dx[4]={-1,1,0,0},dy[4]={0,0,-1,1};

struct Edge{
	int from,to,flow,cap;
	Edge() {}
	Edge(int from,int to,int flow,int cap):from(from),to(to),flow(flow),cap(cap) {}
};

struct Dinic{
	int first[maxn],next[maxm],edge;
	Edge edges[maxm];
	int n,s,t;
	int cur[maxn],d[maxn];
	
	void init(int nn){
		n=nn;
		edge=0;
		memset(first,-1,sizeof(first));
	}
	
	void add_edge(int from,int to,int cap){
		if(cap==0) return;
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
	
	LL DFS(int x,int a){
		if(x==t||a==0) return a;
		LL flow=0,f;
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
		LL flow=0;
		while(BFS()){
			for(int i=0;i<n;i++) cur[i]=first[i];
			flow+=DFS(s,inf);
		}
		return flow;
	}
}dinic;
LL n,m;
int S,T;
LL sum=0;
int A[45][45];

bool check(LL val){
	S=0,T=n*m+1;dinic.init(T+1);
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if((i+j)%2==0)
				dinic.add_edge(S,(i-1)*m+j,val-A[i][j]);
			else dinic.add_edge((i-1)*m+j,T,val-A[i][j]);
			for(int k=0;k<4;k++){
				int x=i+dx[k],y=j+dy[k];
				if(x>=1&&x<=n&&y>=1&&y<=m){
					dinic.add_edge((i-1)*m+j,(x-1)*m+y,INF);
				}
			}
		}
	return dinic.maxflow(S,T)*2==((val*n*m-sum));
}

int main(){
	////freopen("input.txt","r",stdin);
	//freopen("output.txt","w",stdout);
	int tcase;
	LL num1,num2,sum1,sum2;
	scanf("%d",&tcase);
	while(tcase--){
		scanf("%lld%lld",&n,&m);
		int mh=0;
		sum1=0;sum2=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				scanf("%d",&A[i][j]);
				if(!((i+j)&1)) sum1+=A[i][j];
				else sum2+=A[i][j];
				mh=max(mh,A[i][j]);
			}
		if((n*m)&1) num1=n*m/2+1,num2=n*m/2;
		else num1=n*m/2,num2=n*m/2;
		//printf("num1:%d num2:%d sum1:%d sum2:%d\n",num1,num2,sum1,sum2);
		sum=sum1+sum2;
		if(num1==num2){
			if(sum1!=sum2) puts("-1");
			else{
				int L=mh,R=2000000000;
				while(L<=R){
					int M=(L+R)>>1;
					if(check(M)) R=M-1;
					else L=M+1;
				}
				printf("%lld\n",((LL)(R+1)*n*m-sum)/2);
			}
		}
		else{
			int x=(sum1-sum2)/(num1-num2);
			if(x<mh) puts("-1");
			else{
				if(check(x)) printf("%lld\n",((LL)x*n*m-sum)/2);
				else puts("-1");
			}
		}
	}
	return 0;
}
