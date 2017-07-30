# include<stdio.h>
# include<string.h>
# include<queue>
# include<vector>
# include<algorithm>
using namespace std;
const int maxn=310;
const int maxm=14010<<1;
const int INF=~0U>>1;
int st,ed,n,m;
int col[maxn];
int start[maxn],regu[maxn][2],sum[maxn];
int first[maxn],next[maxm],v[maxm],w[maxm],edge=0;
int last[maxn];

void add_edge(int a,int b,int c){
	next[edge]=first[a];v[edge]=b;w[edge]=c;
	first[a]=edge++;
}

struct HeapNode{
	int d,u;
	HeapNode() {}
	HeapNode(int d,int u) :d(d),u(u) {}
	bool operator < (const HeapNode &rhs)const{
		return d>rhs.d;
	}
};

int dist[maxn];
bool used[maxn];
typedef pair<int,int> pi;
pi calnow(int x,int t){
	if(t<start[x]) return pi(col[x],start[x]-t);
	t-=start[x];
	t-=(t/sum[x])*sum[x];
	if(t<regu[x][!col[x]]) return pi(!col[x],regu[x][!col[x]]-t);
	return pi(col[x],sum[x]-t);
}

void dijkstra(){
	for(int i=1;i<=n;i++) dist[i]=INF,used[i]=false;
	dist[st]=0;
	priority_queue<HeapNode> q;
	q.push(HeapNode(0,st));
	while(!q.empty()){
		int x=q.top().u;int now=dist[x];q.pop();
		//printf("x:%d now:%d\n",x,now);
		if(used[x]) continue;
		used[x]=true;
		pi nowcol=calnow(x,now);
		for(int e=first[x];e!=-1;e=next[e]){
			pi nowc=nowcol;
			pi vcol=calnow(v[e],now);
			
			int cnt=0,t=now;
			while(nowc.first!=vcol.first&&cnt<8){
				cnt++;
				t+=min(nowc.second,vcol.second);
				nowc=calnow(x,t),vcol=calnow(v[e],t);
			}
			if(cnt>=4) continue;
			if(t+w[e]<dist[v[e]]){//printf("v[e]:%d\n",v[e]);
				dist[v[e]]=t+w[e];last[v[e]]=x;
				q.push(HeapNode(dist[v[e]],v[e]));
			}
		}
	}
}
vector<int> ans;

int main(){
	char t;
	int a,b,c;
	scanf("%d%d%d%d",&st,&ed,&n,&m);
	for(int i=1;i<=n;i++){
		while((t=getchar())&&t!='B'&&t!='P');
		col[i]=t=='B'?0:1;
		scanf("%d%d%d",&start[i],&regu[i][0],&regu[i][1]);sum[i]=regu[i][0]+regu[i][1];
	}
	memset(first,-1,sizeof(first));edge=0;
	for(int i=1;i<=m;i++)
		scanf("%d%d%d",&a,&b,&c),add_edge(a,b,c),add_edge(b,a,c);
	dijkstra();
	printf("%d\n",dist[ed]==INF?0:dist[ed]);
	if(dist[ed]!=INF){
	int now=ed;
	ans.push_back(now);
	while(now!=st){
		ans.push_back(last[now]);now=last[now];
	}
	for(int i=ans.size()-1;i>0;i--)
		printf("%d ",ans[i]);
	printf("%d\n",ans[0]);
}
	return 0;
}
