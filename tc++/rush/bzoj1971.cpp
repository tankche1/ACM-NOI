# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=100;
int first[maxn],next[maxn*maxn],v[maxn*maxn],w[maxn*maxn],edge,n,m;

void add_edge(int a,int b,int c){
	next[edge]=first[a];
	v[edge]=b;
	w[edge]=c;
	first[a]=edge++;
}

struct KTH{
	int n;
	int A[maxn];
	KTH() {n=0;}
	void add(int x){
		A[n++]=x;//printf("A[%d]:%d\n",n-1,x);
	}
	bool full(){
		return n==maxn;
	}
}kth[maxn][maxn];

struct HeapNode{
	int d,u;
	HeapNode(int d,int u):d(d),u(u) {}
	bool operator < (const HeapNode &rhs)const{
		return d>rhs.d;
	}
};
priority_queue<HeapNode> Q;

void dijkstra(int start){
	//printf("start:%d\n",start);
	Q.push(HeapNode(0,start));
	while(!Q.empty()){
		HeapNode now=Q.top();Q.pop();
		//printf("now.u:%d now.d:%d\n",now.u,now.d);
		if(!kth[start][now.u].full()) {if(now.d) kth[start][now.u].add(now.d);}
		else continue;
		for(int e=first[now.u];e!=-1;e=next[e])
			Q.push(HeapNode(now.d+w[e],v[e]));//,printf("shitnext:%d v:%d\n",now.d+w[e],v[e]);
	}
}

int main(){
	int a,b,c,q;
	memset(first,-1,sizeof(first));edge=0;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);a--;b--;
		add_edge(a,b,c);
	}
	for(int i=0;i<n;i++)
		dijkstra(i);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d%d%d",&a,&b,&c);a--;b--;
		if(kth[a][b].n<c) puts("-1");
		else printf("%d\n",kth[a][b].A[c-1]);
	}
	return 0;
}
