# include<stdio.h>
# include<string.h>
# include<queue>
# include<algorithm>
using namespace std;
const int maxn=155;
typedef long long LL;
int s1,t1,s2,t2;
int n,m;
int tp[maxn];
int out[maxn];
LL f[maxn][maxn];
bool used[maxn][maxn];
typedef pair<int,int> pi;
struct Graph{
int first[maxn],next[maxn*maxn/2],v[maxn*maxn/2],edge;
	
	void init(){
		memset(first,-1,sizeof(first));edge=0;
	}

void add_edge(int a,int b){
	next[edge]=first[a];
	v[edge]=b;
	first[a]=edge++;
}

};Graph G1,G2;

queue<int> Q;
void top_sorted(){
	for(int i=1;i<=n;i++)
		if(!out[i]) Q.push(i);
	int bh=n;
	while(!Q.empty()){
		int x=Q.front();Q.pop();
		tp[x]=bh--;
		for(int e=G2.first[x];e!=-1;e=G2.next[e])
			if(--out[G2.v[e]]==0) Q.push(G2.v[e]);
	}
}

queue<pi> q;

int main(){
	int a,b;
	scanf("%d%d",&n,&m);
	G1.init();G2.init();
	for(int i=1;i<=m;i++){
		scanf("%d%d",&a,&b);out[a]++;
		G1.add_edge(a,b);G2.add_edge(b,a);
	}
	scanf("%d%d%d%d",&s1,&t1,&s2,&t2);
	top_sorted();
	if(tp[s1]<tp[s2]) swap(s1,s2),swap(t1,t2);
	q.push(pi(s1,s2));memset(f,0,sizeof(f));f[s1][s2]=1;
	for(int i=1;i<=n;i++)
		printf("tp[%d]:%d\n",i,tp[i]);
	while(!q.empty()){
		int x=q.front().first,y=q.front().second;q.pop();
		if(used[x][y]) continue;
			printf("x:%d y:%d f:%d\n",x,y,f[x][y]); 
		used[x][y]=1;
		if(tp[x]>tp[y]||x==s1)
		for(int e=G1.first[y];e!=-1;e=G1.next[e])
			if(x==s1||tp[G1.v[e]]>tp[x])
				f[x][G1.v[e]]+=f[x][y],q.push(pi(x,G1.v[e])),printf("f[%d][%d]:%d\n",x,G1.v[e],f[x][G1.v[e]]);
		if(tp[x]<tp[y])
			for(int e=G1.first[x];e!=-1;e=G1.next[e])
				if(tp[G1.v[e]]>tp[y])
					f[G1.v[e]][y]+=f[x][y],q.push(pi(G1.v[e],y)),printf("f[%d][%d]:%d\n",G1.v[e],y,f[G1.v[e]][y]);
	}
	printf("%lld\n",f[t1][t2]);
	return 0;
}
