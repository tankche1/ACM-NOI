#include<stdio.h>
#include<string.h>
#include<algorithm>
using namespace std;
const int maxn=100010;
int n,m;
int first[maxn],next[maxn<<1],v[maxn<<1],edge,w[maxn<<1],son[maxn];
int S[maxn],top=-1;
bool vis[maxn];
int scc[50],scc_cnt=0,len[50];
bool on[maxn];
double down[maxn],up[maxn];
int du[maxn];
int dist[maxn];
int _next[maxn];


void add_edge(int a,int b,int c){
	//printf("a:%d b:%d\n",a,b);
	next[edge]=first[a];
	v[edge]=b;w[edge]=c;
	first[a]=edge++;
}

bool find_huan(int x,int fa){
	vis[x]=1;
	S[++top]=x;
	//printf("x:%d\n",x);
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa){
			if(!vis[v[e]]) {dist[top+1]=w[e];if(find_huan(v[e],x)) return true;}
			else{
				//printf("x:%d v[e]:%d\n",x,v[e]);
				int now;
				len[1]=w[e];
				do{
					now=S[top--];
					scc[++scc_cnt]=now;len[scc_cnt+1]=dist[top+1];
					on[now]=1;
				}while(now!=v[e]);
				return true;
			}
		}
	top--;
	return false;
}

void dfs_pre(int x,int fa){
	son[x]=0;
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa&&!on[v[e]]){
			son[x]++;
			dfs_pre(v[e],x);
		}
}

void dfs_down(int x,int fa){
	down[x]=0;
	//printf("x:%d \n",x);int dd;scanf("%d",&dd);
	for(int e=first[x];e!=-1;e=next[e]){
		if(v[e]==fa||on[v[e]]) continue;
			//printf("x:%d v[e]:%d\n",x,v[e]);
			dfs_down(v[e],x);
			down[x]+=down[v[e]]+w[e];
			//printf("down[%d]:%.3lf\n",x,down[x]);
	}
		if(son[x])
	down[x]=down[x]/(son[x]*1.0);
//	printf("down[%d]:%.3lf\n",x,down[x]);
}

void dfs_up(int x,int fa){
	for(int e=first[x];e!=-1;e=next[e])
		if(v[e]!=fa&&!on[v[e]]){
			if(du[x]>1) up[v[e]]=w[e]+(up[x]*(du[x]-son[x])+down[x]*son[x]-(down[v[e]]+w[e]))/((du[x]-1)*1.0);
				else up[v[e]]=w[e];
		//	printf("up[%d]:%.3lf\n",v[e],up[v[e]]);
			dfs_up(v[e],x);
		}
}

int main(){
	int a,b,c;
	scanf("%d%d",&n,&m);
	memset(first,-1,sizeof(first));edge=0;
	memset(du,0,sizeof(du));
	for(int i=1;i<=m;i++){
		scanf("%d%d%d",&a,&b,&c);
		add_edge(a,b,c);
		add_edge(b,a,c);
		du[a]++;du[b]++;
	}
	memset(vis,false,sizeof(vis));memset(on,0,sizeof(on));
	find_huan(1,0);//puts("fuck");
	if(scc_cnt==0) scc[++scc_cnt]=1,on[1]=1;
	//for(int i=1;i<=scc_cnt;i++) printf("scc[%d]:%d len:%d\n",i,scc[i],len[i]);
	for(int i=1;i<=scc_cnt;i++)
		dfs_pre(scc[i],0);
	//puts("shit");
	for(int i=1;i<=scc_cnt;i++){
		_next[i]=i+1;
		dfs_down(scc[i],0);
	}
	_next[scc_cnt]=1;
	
	for(int i=1;i<=scc_cnt;i++){
		up[scc[i]]=0;
		for(int j=1;j<=scc_cnt;j++){
			if(i==j) continue;
			double p=0.5,l=0;
			int k=i;
			do{
				k++;if(k>scc_cnt) k=1;
				l+=len[k];
				if(k!=j) p=p/((du[scc[k]]-1)*1.0);
			}while(k!=j);
			if(_next[j]!=i){
				p*=son[scc[j]]/((du[scc[j]]-1)*1.0);
			}
			l+=down[scc[j]];
			up[scc[i]]+=p*l;//printf("%.3lf\n",p*l);
			
			k=i;p=0.5;l=0;
			do{
				k--;if(k==0) k=scc_cnt;
				l+=k<scc_cnt?len[k+1]:len[1];
				if(k!=j) p=p/((du[scc[k]]-1)*1.0);
			}while(k!=j);
			if(_next[i]!=j){
				p*=son[scc[j]]/((du[scc[j]]-1)*1.0);
			}
			l+=down[scc[j]];
			up[scc[i]]+=p*l;//printf("%.3lf l:%.3lf\n",p*l,l);
			//printf("j:%d up[%d]:%.3lf\n",j,scc[i],up[scc[i]]);
		}
		//printf("up[%d]:%.3lf\n",scc[i],up[scc[i]]);
	}
	for(int i=1;i<=scc_cnt;i++)
		dfs_up(scc[i],0);
	double ans=0;
	for(int i=1;i<=n;i++)
		ans+=(down[i]*son[i]+up[i]*(du[i]-son[i]))/(du[i]*1.0);
	ans=ans/(n*1.0);
	printf("%.5lf\n",ans);
	return 0;
}
/*
5 5
1 2 3
2 3 3
3 4 4
4 5 5
5 3 2
*/
