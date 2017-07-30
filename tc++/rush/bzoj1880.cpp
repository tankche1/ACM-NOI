# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=1505;
const int INF=100000000;
int first[maxn],next[maxn*maxn],v[maxn*maxn],dist[maxn*maxn],edge,u[maxn*maxn];
int st1,st2,ed1,ed2;
int n,m;
int in[maxn];
int dp[maxn];
vector<int> G[maxn];

void add_edge(int a,int b,int c){
	u[edge]=a;
	next[edge]=first[a];
	v[edge]=b;
	dist[edge]=c;
	first[a]=edge++;
}
bool used[maxn];

struct HeapNode{
	int d,u;
	HeapNode() {}
	HeapNode(int d,int u):d(d),u(u) {}
	bool operator < (const HeapNode &rhs)const{
		return d>rhs.d;
	}
};
struct Dijkstar{
	int d[maxn];
	
	void dijkstar(int s){
		priority_queue<HeapNode> q;
		q.push(HeapNode(0,s));
		memset(used,false,sizeof(used));
		for(int i=1;i<=n;i++) d[i]=INF;d[s]=0;
		while(!q.empty()){
			int x=q.top().u;q.pop();
			if(used[x]) continue;
				used[x]=1;
			for(int e=first[x];e!=-1;e=next[e])
				if(d[v[e]]>d[x]+dist[e]){
					d[v[e]]=d[x]+dist[e];
					q.push(HeapNode(d[v[e]],v[e]));
				}
		}
	}
};
Dijkstar start1,end1,start2,end2;
int main(){
	int a,b,c;
	scanf("%d%d",&n,&m);
	scanf("%d%d%d%d",&st1,&ed1,&st2,&ed2);
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
	}
	start1.dijkstar(st1);
	end1.dijkstar(ed1);
	start2.dijkstar(st2);
	end2.dijkstar(ed2);
	int ans1=start1.d[ed1],ans2=start2.d[ed2];
	memset(in,0,sizeof(in));
	//printf("ans1:%d ans2:%d\n",ans1,ans2);
	for(int i=0;i<edge;i++){
		//printf("st1_u:%d v-ed1:%d st2_u:%d v-ed2:%d %d %d\n",start1.d[u[i]],end1.d[v[i]],start2.d[u[i]],end2.d[v[i]],start1.d[u[i]]+dist[i]+end1.d[v[i]],start2.d[u[i]]+dist[i]+end2.d[v[i]]);
		if(start1.d[u[i]]+dist[i]+end1.d[v[i]]==ans1&&(start2.d[u[i]]+dist[i]+end2.d[v[i]]==ans2||start2.d[v[i]]+dist[i]+end2.d[u[i]]==ans2)){
			G[u[i]].push_back(i);//printf("%d\n",i);
			in[v[i]]++;
		}
	}
	queue<int> q;
	for(int i=1;i<=n;i++)
		if(G[i].size()&&(!in[i])) q.push(i);
	memset(dp,0,sizeof(dp));int ans=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=0;i<G[x].size();i++){
			int to=v[G[x][i]],from=u[G[x][i]];
			if(dp[to]<dp[from]+dist[G[x][i]])
				dp[to]=dp[from]+dist[G[x][i]],ans=max(ans,dp[to]);
			if(--in[to]==0){
				q.push(to);
			}
		}
	}
	printf("%d\n",ans);
	return 0;
}
