# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=1010;
const int maxm=100010;
const int INF=~0U>>1;

struct HeapNode1{
	int d,u;
	
	void n(int dd,int uu){d=dd;u=uu;}
	bool operator < (HeapNode1 rhs)const{
		return d>rhs.d;
	}
};HeapNode1 node;

struct Dijkstra{
	int first[maxn],next[maxm],v[maxm],dist[maxm],m;
	int d[maxn];
	bool done[maxn];
	int n;
	
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
		priority_queue<HeapNode1> q;
		node.n(0,s);
		q.push(node);
		for(int i=0;i<n;i++) d[i]=INF;d[s]=0;
		memset(done,false,sizeof(done));
		while(!q.empty()){
			int x=q.top().u;q.pop();
			if(done[x]) continue;
			done[x]=true;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]>d[x]+dist[e]){
					d[v[e]]=d[x]+dist[e];
					node.n(d[v[e]],v[e]);
					q.push(node);
				}
			}
		}
		//for(int i=0;i<n;i++) printf("d[%d]:%d\n",i,d[i]);
	}
};
Dijkstra dij;

struct HeapNode2{
	int g,h,u;
	
	void n(int uu,int gg,int hh) {u=uu;g=gg;h=hh;}
	
	bool operator < (HeapNode2 rhs)const{
		return (g+h)>(rhs.g+rhs.h);
	}
};HeapNode2 Node;

struct Astar{
	int first[maxn],next[maxm],v[maxm],dist[maxm],m;
	int cnt[maxn];
	int n;
	
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
	
	int astar(int s,int t,int K){
		if(dij.d[s]==INF) return -1;
		priority_queue<HeapNode2> q;
		Node.n(s,0,dij.d[s]);
		q.push(Node);
		memset(cnt,0,sizeof(cnt));
		while(!q.empty()){
			int x=q.top().u;
			HeapNode2 now=q.top();q.pop();
			//printf("x:%d g:%d h:%d\n",x,now.g,now.h);
			if(++cnt[x]>K) continue;
			if(cnt[t]==K) return now.g;
			for(int e=first[x];e!=-1;e=next[e]){
				HeapNode2 New;
				New.n(v[e],now.g+dist[e],dij.d[v[e]]);
				q.push(New);
			}
		}
		return -1;
	}
};
Astar A;

int n,m;
int from,to,dist;
int s,t,k;
int main(){
	scanf("%d%d",&n,&m);
	dij.init(n);
	A.init(n);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&from,&to,&dist);from--;to--;
		//dij1.add_edge(from,to,dist);
		dij.add_edge(to,from,dist);
		A.add_edge(from,to,dist);
	}
	scanf("%d%d%d",&s,&t,&k);s--;t--;
	if(s==t) k++;
	dij.dijkstra(t);
	printf("%d\n",A.astar(s,t,k));
	return 0;
}
