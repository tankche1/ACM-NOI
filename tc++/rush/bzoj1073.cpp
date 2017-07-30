# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=55;
const int maxk=2600;
const int INF=~0U>>1;
typedef int LL;

struct HeapNode{
	int d,u;
	bool operator < (HeapNode rhs)const{
		return d>rhs.d;
	}
	void g(int dd,int uu) {d=dd;u=uu;}
};
HeapNode node;

struct Dijkstra{
	int first[maxn],next[maxn*maxn],v[maxn*maxn],dist[maxn*maxn];
	int n,m,d[maxn];
	bool done[maxn];
	
	void init(int a){
		n=a;
		memset(first,-1,sizeof(first));
		m=0;
	}
	
	void add_edge(int from,int to,int dis){
		next[m]=first[from];
		first[from]=m;
		v[m]=to;
		dist[m++]=dis;
	}
	
	void dijkstra(int s){
		for(int i=0;i<n;i++) d[i]=INF;d[s]=0;
		memset(done,false,sizeof(done));
		priority_queue<HeapNode> Q;
		node.g(0,s);
		Q.push(node);
		while(!Q.empty()){
			int x=Q.top().u;Q.pop();
			if(done[x]) continue;
				done[x]=true;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]>d[x]+dist[e]){
					d[v[e]]=d[x]+dist[e];
					node.g(d[v[e]],v[e]);
					Q.push(node);
				}
			}
		}
	}
	
};
Dijkstra dij;

struct DFS{
	int G[maxn][maxn];
	int n,m,K;
	int Z,nextZ;
	int p[maxn];
	int S,T;
	bool vis[maxn];
	vector<int> ans[maxk];
	int ans_cnt;
	LL ans_length[maxk];
	
	void init(int a,int k){
		n=a;K=k;
		memset(G,-1,sizeof(G));
		ans_cnt=0;
	}
	
	void add_edge(int from,int to,int dist){
		G[from][to]=dist;
	}
	
	void prepare(int s,int t){
		for(int i=1;i<=ans_cnt;i++) ans[i].clear();
		ans_cnt=0;
		S=s;T=t;
		memset(vis,0,sizeof(vis));
		nextZ=INF;
		p[S]=S;
	}
	
	void Dfs(int x,int g){
				//printf("x:%d g:%d p:%d\n",x,g,p[x]);
		if(g+dij.d[x]>Z) {nextZ=min(nextZ,g+dij.d[x]);return;}
		//printf("x:%d g:%d p:%d\n",x,g,p[x]);
		vis[x]=true;
		if(x==T){
			ans_cnt++;
			int u=T;
			do{//printf("u:%d\n",u+1);
				ans[ans_cnt].push_back(u);
				u=p[u];
			}while(u!=S);
			//printf("u:%d\n",S+1);
			//printf("length:%d\n",g*1000+ans_cnt);
			ans[ans_cnt].push_back(u);
			ans_length[ans_cnt]=g*10000+ans_cnt;
			vis[x]=false;
			return;
		}
		for(int i=0;i<n;i++){
			if(G[x][i]!=-1&&!vis[i]){
				p[i]=x;
				Dfs(i,g+G[x][i]);
			}
		}
		vis[x]=false;
		return;
	}
	
};
DFS dfs;

int n,m,k,s,t;

bool cmp(int a,int b){
	return dfs.ans_length[a]<dfs.ans_length[b];
}

int rank[1000];

int main(){
	scanf("%d%d%d%d%d",&n,&m,&k,&s,&t);s--;t--;
	int from,to,dist;
	dij.init(n);
	dfs.init(n,k);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&from,&to,&dist);from--;to--;
		dfs.add_edge(from,to,dist);
		dij.add_edge(to,from,dist);
	}
	dij.dijkstra(t);
	dfs.Z=dij.d[s];
	while(1){
		dfs.prepare(s,t);
		dfs.Dfs(s,0);
	//	printf("Z:%d nextZ:%d\n",dfs.Z,dfs.nextZ);
		//printf("%d\n",dfs.ans_cnt);
		if(dfs.ans_cnt>=k) break;
		if(dfs.nextZ==INF) {dfs.Z=-1;break;}
		dfs.Z=dfs.nextZ;
	}
	if(dfs.Z==-1) puts("No");
	else{
		//printf("dfs.ans_cnt:%d Z:%d \n",dfs.ans_cnt,dfs.Z);
		for(int i=1;i<=dfs.ans_cnt;i++) rank[i]=i;
		sort(rank+1,rank+dfs.ans_cnt+1,cmp);
		//printf("fuck\n");
		//printf("%d\n",dfs.ans[rank[k]].size()-1);
		for(int i=dfs.ans[rank[k]].size()-1;i>=0;i--){
			if(i!=(dfs.ans[rank[k]].size()-1)) printf("-");
				printf("%d",dfs.ans[rank[k]][i]+1);
		}
		printf("\n");
	}
	return 0;
}
/*
4 6 5 1 4

2 4 2

1 3 2

1 2 1

1 4 3

2 3 1

3 4 1
*/
