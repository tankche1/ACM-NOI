#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=50010;
int n,m;
int first[maxn],next[maxn<<2],u[maxn<<2],v[maxn<<2],edge=0;
int dis[maxn];

int dfn[maxn],low[maxn],dfs_clock=0;
int S[maxn<<2],top=-1;
int ans=0;
int C[maxn<<1],tot;
int q[maxn<<1],head,tail;

void add_edge(int a,int b){
	next[edge]=first[a];
	u[edge]=a;v[edge]=b;
	first[a]=edge++;
}

void dp(int t){
	q[head=tail=0]=1;
	for(int i=2;i<=tot;i++){
		while(i-q[head]>t) head++;
		ans=max(ans,dis[C[i]]+dis[C[q[head]]]+i-q[head]);
		while(head<=tail&&dis[C[q[tail]]]-q[tail]<=dis[C[i]]-i) tail--;
		q[++tail]=i;
	}
}

void dfs(int x,int fa){
	int l=0;
	dfn[x]=low[x]=++dfs_clock;dis[x]=0;
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa) continue;
		S[++top]=e;
		if(dfn[v[e]]) low[x]=min(low[x],dfn[v[e]]),top--;
		else{
			dfs(v[e],x),low[x]=min(low[x],low[v[e]]);
			if(low[v[e]]==dfn[v[e]]){//bridge
				if(dis[v[e]]+1>l){
					l=dis[v[e]]+1;if(l>dis[x]) swap(l,dis[x]);
				}
				top--;
			}
			else if(low[v[e]]==dfn[x]){//circle
				tot=0;int s,j=0;
				do{
					s=S[top--];
					C[++tot]=v[s];
				}while(u[s]!=x);
				//printf("tot:%d\n",tot);
				//for(int i=1;i<=tot;i++) printf("%d ",C[i]);puts("");
				for(int i=1;i<=tot;i++){
					C[tot+1+i]=C[i];
					j=max(j,min(i,tot+1-i)+dis[C[i]]);
				}
				C[++tot]=x;int t=tot>>1;tot=(tot<<1)-1;
				//printf("x:%d j:%d\n",x,j);
				dp(t);
				if(j>l){
					l=j;if(l>dis[x]) swap(l,dis[x]);
				}
			}
		}
	}
	ans=max(ans,l+dis[x]);
	//printf("dis[%d]:%d l:%d\n",x,dis[x],l);
}

int main(){
	int x,y;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));
	for(int i=1;i<=m;i++){
		scanf("%d",&x);
		int lasty=-1;
		while(x--){
			scanf("%d",&y);
			if(lasty!=-1) add_edge(y,lasty),add_edge(lasty,y);
			lasty=y;
		}
	}
	dfs(1,0);
	printf("%d\n",ans);
	return 0;
}
