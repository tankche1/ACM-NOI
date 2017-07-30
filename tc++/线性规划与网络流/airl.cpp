#include<stdio.h>
#include<string.h>
# include<iostream>
# include<string>
# include<queue>
# include<vector>
# include<map>
#include<algorithm>
using namespace std;
const int INF=~0U>>1;
const int maxn=110;
const int maxm=maxn*maxn;
map<string,int> name;
int n,m;
string s1,s2,s[maxn];
vector<int> ans;

struct MCMF{
	struct Edge{
		int from,to,cap,flow,cost;
		Edge() {}
		Edge(int from,int to,int cap,int flow,int cost):from(from),to(to),cap(cap),flow(flow),cost(cost) {}
	}edges[maxm];
	int first[maxn],next[maxm],edge,n;
	int d[maxn],p[maxn],a[maxn];
	bool inq[maxn];
	
	void init(int nn){
		n=nn;
		memset(first,-1,sizeof(first));edge=0;
	}
	
	void add_edge(int from,int to,int cap,int cost){
		//printf("from:%d to:%d cap:%d cost:%d\n",from,to,cap,cost);
		next[edge]=first[from];
		edges[edge]=Edge(from,to,cap,0,cost);
		first[from]=edge++;
		next[edge]=first[to];
		edges[edge]=Edge(to,from,0,0,-cost);
		first[to]=edge++;
	}
	
	bool BellmanFord(int S,int T,int &flow,int &cost){
		for(int i=0;i<n;i++) d[i]=INF;d[S]=0;a[S]=INF;
			memset(inq,false,sizeof(inq));
		queue<int> Q;
		Q.push(S);
		while(!Q.empty()){
			int x=Q.front();Q.pop();inq[x]=0;//printf("x:%d d:%d\n",x,d[x]);int dd;scanf("%d",&dd);
			for(int e=first[x];e!=-1;e=next[e]){
				if(edges[e].flow<edges[e].cap&&d[edges[e].to]>d[x]+edges[e].cost){
					d[edges[e].to]=d[x]+edges[e].cost;
					a[edges[e].to]=min(a[x],edges[e].cap-edges[e].flow),p[edges[e].to]=e;
					if(!inq[edges[e].to]) {Q.push(edges[e].to),inq[edges[e].to]=1;}
				}
			}
		}
		if(d[T]==INF) return false;
		int now=T;
		flow+=a[T];
		cost+=d[T]*a[T];
		//printf("flow:%d cost:%d\n",flow,cost);
		while(now!=S){
			edges[p[now]].flow+=a[T];
			edges[p[now]^1].flow-=a[T];
			now=edges[p[now]].from;
		}
		return true;
	}
	
	void MinCost(int S,int T,int &flow,int &cost){
		flow=0,cost=0;
		while(BellmanFord(S,T,flow,cost));
		
	}
};
MCMF g;
int main(){
	//freopen("airl.in","r",stdin);
	//freopen("airl.out","w",stdout);
	int a,b;
	;s1.resize(100),s2.resize(100);
	scanf("%d %d\n",&n,&m);
	int S=0,T=2*n+1;
	g.init(T+1);
	for(int i=1;i<=n;i++){
		s[i].resize(100);
		//scanf("%s",&s[i][0]);puts(s[i].c_str());
		cin>>s[i];
		name[s[i]]=i;
	}
	for(int i=1;i<=m;i++){
		//scanf("%s",&s1[0]);scanf("%s",&s2[0]);
		cin>>s1,cin>>s2;
		a=name[s1],b=name[s2];//puts(s1.c_str());puts(s2.c_str());
		//printf("a:%d b:%d \n",a,b);
		g.add_edge(n+a,b,2,0);
		//g.add_edge(
	}
	g.add_edge(S,1,2,0);g.add_edge(2*n,T,2,0);
	g.add_edge(1,n+1,2,-1);
	g.add_edge(n,2*n,2,-1);
	for(int i=2;i<n;i++)
		g.add_edge(i,n+i,1,-1);
	int flow=0,cost=0;
	g.MinCost(S,T,flow,cost);
	if(flow<2) puts("No Solution!");
		else{
			printf("%d\n",-cost-2);
			puts(s[1].c_str());
			int now=1;
			do{
				now=n+now;
				for(int e=g.first[now];e!=-1;e=g.next[e])
					if(g.edges[e].cap>0&&g.edges[e].flow>0){
						now=g.edges[e].to;
						g.edges[e].flow--;
						puts(s[now].c_str());break;
					}
			}while(now!=n);
			ans.clear();
			now=1;
			while(now!=n){
				now=n+now;//printf("no:%d",now);
				for(int e=g.first[now];e!=-1;e=g.next[e])
					if(g.edges[e].cap>0&&g.edges[e].flow>0){
						now=g.edges[e].to;
						g.edges[e].flow--;
						ans.push_back(now);//printf("now:%d",ans[ans.size()-1]);
						break;
					}
			}
			for(int i=ans.size()-2;i>=0;i--)
				puts(s[ans[i]].c_str());
			puts(s[1].c_str());
		}
	return 0;
}
