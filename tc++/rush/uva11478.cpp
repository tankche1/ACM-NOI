# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int INF=10010;
const int maxn=510;
const int maxm=2710;

struct BellmanFord{
	int first[maxn],v[maxm],next[maxm],dist[maxm],edge;
	int n;
	int cnt[maxn],d[maxn];
	bool inq[maxn];
	
	void init(int nn){
		memset(first,-1,sizeof(first));edge=0;n=nn;
	}
	
	void add_edge(int from,int to,int dis){
		next[edge]=first[from];
		v[edge]=to;
		dist[edge]=dis;
		first[from]=edge++;
	}
	
	bool negativeCycle(){
		queue<int> q;
		for(int i=1;i<=n;i++){
			d[i]=0;cnt[i]=0;inq[i]=true;q.push(i);
		}
		while(!q.empty()){
			int x=q.front();q.pop();
			//printf("d[%d]:%d\n",x,d[x]);
			inq[x]=false;
			for(int e=first[x];e!=-1;e=next[e]){
				if(d[v[e]]>d[x]+dist[e]){
					d[v[e]]=d[x]+dist[e];
					if(!inq[v[e]]){
						inq[v[e]]=true;q.push(v[e]);
						if(++cnt[v[e]]>=n) return true;
					}
				}
			}
		}
		return false;
	}
	
};
BellmanFord Bellman;

bool test(int M){
	for(int i=0;i<Bellman.edge;i++){
		Bellman.dist[i]+=M;/*printf("%d\n",Bellman.dist[i]);*/}
	bool ans=Bellman.negativeCycle();//printf("ans:%d\n",ans);
	for(int i=0;i<Bellman.edge;i++)
		Bellman.dist[i]-=M;
	return (!ans); // 如果有负环，说明差分约束系统无解
}

int n,m;
int main(){
	int a,b,c;
	while(scanf("%d%d",&n,&m)!=EOF){
		int maxc=0;
		Bellman.init(n);
		for(int i=1;i<=m;i++){
			scanf("%d%d%d",&a,&b,&c);
			maxc=max(maxc,c);
			Bellman.add_edge(a,b,c);
		}
		if(!test(-1)) printf("No Solution\n");
		else if(test(-(maxc+1))) printf("Infinite\n");
		else{
		int L=1,R=maxc;
		while(L<=R){
			int M=(L+R)>>1;
			if(test(-M)) L=M+1;
				else R=M-1;
		}
		printf("%d\n",L-1);
	}
	}
	return 0;
}
