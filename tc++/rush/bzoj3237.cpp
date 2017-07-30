#include<stdio.h>
#include<string.h>
# include<vector>
#include<algorithm>
using namespace std;
const int maxn=100010;
const int maxm=maxn<<1;
const int maxq=maxn;
bool mark[maxm];
int f[maxn],t[maxn];
bool vis[maxm];
int fwt[maxn];
bool ans[maxq];
//bool bh[maxn];
int ask_len[maxq];

int ask[maxq][4];

struct Edge{
	int u,v;
	inline Edge() {}
};
Edge edges[maxm];

inline int find(int a){
	if(a==f[a]) return a;return f[a]=find(f[a]);
}

inline void Join(int x,int y){
	int fx=find(x),fy=find(y);
	if(fx<fy) swap(fx,fy);
	f[fx]=fy;
}

int Remark(int l,int r,int n){
	int nn=n;
	for(int i=1;i<=n;i++)
		t[i]=find(i);
	sort(t+1,t+n+1);
	n=unique(t+1,t+n+1)-(t+1);
	for(int i=1;i<=n;i++) fwt[t[i]]=i;//,bh[i]=false;
	for(int i=1;i<=nn;i++)
		f[i]=fwt[f[i]];
	for(int i=l;i<=r;i++)
		for(int j=0;j<ask_len[i];j++)
			edges[ask[i][j]].u=f[edges[ask[i][j]].u],edges[ask[i][j]].v=f[edges[ask[i][j]].v];
	for(int i=1;i<=n;i++)
		f[i]=i;
	return n;
}

void solve(int l,int r,int n){
//	printf("n:%d\n",n);
	//printf("l:%d r:%d n:%d\n",l,r,n);
	//for(int i=1;i<=n;i++) printf("f[%d]:%d\n",i,f[i]);
	int i,j;
	if(l==r){
		ans[l]=n==1;return;
	}
	
	int *p=new int[n+10];int m=(l+r)>>1;
	Edge *e=new Edge[(r-m)*4+10];
	int num=0;
	for(i=1;i<=n;i++) p[i]=f[i];
		
	for(i=l;i<=m;i++)
		for( j=0;j<ask_len[i];j++) vis[ask[i][j]]=false,e[++num]=edges[ask[i][j]];
			
	for( i=l;i<=m;i++)
		for(j=0;j<ask_len[i];j++) vis[ask[i][j]]=1;
	
	for( i=m+1;i<=r;i++)
		for( j=0;j<ask_len[i];j++) if(!vis[ask[i][j]]) //printf("Join:%d\n",ask[i][j]),
			Join(edges[ask[i][j]].u,edges[ask[i][j]].v);
	
	solve(l,m,Remark(l,m,n));
	for( i=1;i<=n;i++) f[i]=p[i];//,printf("f[%d]:%d\n",i,f[i]);
	num=0;
	for(i=l;i<=r;i++)
		for( j=0;j<ask_len[i];j++) vis[ask[i][j]]=false;
			
	for( i=l;i<=m;i++)
		for(j=0;j<ask_len[i];j++)
			edges[ask[i][j]]=e[++num];
	
	for(i=m+1;i<=r;i++)			
		for(j=0;j<ask_len[i];j++) vis[ask[i][j]]=1;
	
	for(i=l;i<=m;i++)
		for(j=0;j<ask_len[i];j++) if(!vis[ask[i][j]]) //printf("Join:%d\n",ask[i][j]),
			Join(edges[ask[i][j]].u,edges[ask[i][j]].v);
	solve(m+1,r,Remark(m+1,r,n));
}

int n,m,q;
int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	for(int i=1;i<=m;i++)
		scanf("%d%d",&edges[i].u,&edges[i].v);
	scanf("%d",&q);
	for(int i=1;i<=q;i++){
		scanf("%d",&x);ask_len[i]=x;
		while(x--){
			scanf("%d",&y);ask[i][x]=y;mark[y]=1;
		}
	}
	for(int i=1;i<=n;i++) f[i]=i;
		
	for(int i=1;i<=m;i++)
		if(!mark[i]) Join(edges[i].u,edges[i].v);
	solve(1,q,Remark(1,q,n));
	for(int i=1;i<=q;i++) 
		if(ans[i]) puts("Connected");
			else puts("Disconnected");
	return 0;
}
